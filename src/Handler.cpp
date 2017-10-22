/*
 * Handler.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: nhirokinet
 */

#include "Handler.h"

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <thread>
#include <unistd.h>
#include <vector>

Handler::Handler() : _fd(0) {
}

Handler::~Handler() {
	if (_fd) {
		::close(_fd);
		_fd = 0;
	}
}

namespace {

inline int hex2dec(const char in) {
	if (in >= 'a' && in <= 'f') {
		return (in - 'a' + 10);
	}
	if (in >= 'A' && in <= 'F') {
		return (in - 'A' + 10);
	}
	if (in >= '0' && in <= '9') {
		return (in - '0');
	}

	return 0;
}

std::string urldecode(const std::string &input) {
	std::string ret;

	for (size_t i = 0; i < input.length(); ++i) {
		if (input[i] =='%' && i + 2 < input.length()){
			ret += (unsigned char) ((hex2dec(input[i+1]) << 4) + hex2dec(input[i+2]));
			i += 2;
		} else {
			ret += input[i];
		}
	}

	return ret;
}

void decodeString(const std::string &input, std::vector <std::string> *output) {
	output->clear();

	size_t curpos = 0;

	while (curpos < input.length()) {
		size_t next = input.find('&', curpos);

		if (next == std::string::npos) {
			output->push_back(urldecode(input.substr(curpos)));
			break;
		} else {
			output->push_back(urldecode(input.substr(curpos, next - curpos)));
			curpos = next + 1;

			if (curpos == input.length() - 1) {
				output->push_back("");
				break;
			}
		}
	}
}
}

void Handler::open(const std::string& filename) {
	_fd = ::open(filename.c_str(), O_RDWR | O_CREAT, 0666);

	int tmpsize;

	while (::read(_fd, &tmpsize, sizeof(int))) {
		char * buff = (char *) malloc(tmpsize);
		::read(_fd, buff, tmpsize);

		std::vector <std::string> decodedInput;
		decodeString(std::string(buff, tmpsize), &decodedInput);

		write(decodedInput);
	}
	std::thread th(&_writeToDiskFromQueue, this);
	th.detach();
}

void Handler::handleHTTP(FCGX_Request& request) {
	fcgi_streambuf cin_fcgi_streambuf(request.in);
	fcgi_streambuf cout_fcgi_streambuf(request.out);
	fcgi_streambuf cerr_fcgi_streambuf(request.err);

	std::iostream instream(&cin_fcgi_streambuf);
	std::iostream outstream(&cout_fcgi_streambuf);
	std::iostream errstream(&cerr_fcgi_streambuf);

	const std::string query_string(FCGX_GetParam("QUERY_STRING", request.envp));

	if (query_string.length() == 0) {
		outstream << "Status: 404 Not Found\r\n";
		outstream << "Content-Type: text/plain\r\n\r\n";
		outstream << "Error";
		return;
	}

	if (query_string[0] == 'R') {
		std::string ret;
		std::vector <std::string> decodedInput;
		decodeString(query_string.substr(1), &decodedInput);

		{
			std::shared_lock <std::shared_timed_mutex> lock(_mutex);
			ret = read(decodedInput);
		}
		outstream << "Content-Type: text/plain\r\n\r\n";
		outstream << ret;
		return;
	}

	if (query_string[0] == 'W') {
		std::vector <std::string> decodedInput;
		decodeString(query_string.substr(1), &decodedInput);

		{
			// Guarantee write order
			std::unique_lock <std::shared_timed_mutex> lock_queue(_queue_mutex);
			{
				std::unique_lock <std::shared_timed_mutex> lock_all(_mutex);
				write(decodedInput);
			}

			_queue.push(query_string.substr(1));
		}
		outstream << "Content-Type: text/plain\r\n\r\nOK";
		return;
	}

	outstream << "Status: 404 Not Found\r\n";
	outstream << "Content-Type: text/plain\r\n\r\n";
	outstream << "Error";
}

void Handler::_writeToDiskFromQueue(Handler *handler) {
	while (true) {
		sleep(1);

		while (true) {
			{
				std::shared_lock <std::shared_timed_mutex> lock(handler->_queue_mutex);
				if (handler->_queue.empty()) {
					break;
				}
			}
			std::string data;
			{
				std::unique_lock <std::shared_timed_mutex> lock_queue(handler->_queue_mutex);
				data = handler->_queue.front();
				handler->_queue.pop();
			}
			const int len = data.length();
			char * buf = (char *) malloc(sizeof(int) + len);

			* (int *) buf = len;
			::memcpy(buf + sizeof(int), data.c_str(), len);

			// write atomically
			::write(handler->_fd, buf, len + sizeof(int));

			free(buf);
		}
	}
}
