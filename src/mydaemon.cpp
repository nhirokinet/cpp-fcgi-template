#include <fcgio.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <thread>
#include <vector>

#include "Handler.h"
#include "KVSHandler.h"

#define THREAD_NUMBER 4

namespace {
	void errorHandle(FCGX_Request &request) {
		// I guess there 3 variables must be constructed and destroyed to complete HTTP request. If not please tell me
		fcgi_streambuf cin_fcgi_streambuf(request.in);
		fcgi_streambuf cout_fcgi_streambuf(request.out);
		fcgi_streambuf cerr_fcgi_streambuf(request.err);

		std::iostream outstream(&cout_fcgi_streambuf);
		outstream << "Status: 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found\r\n";
	}

	void run(std::unordered_map <std::string, Handler*> handlers) {
		FCGX_Request request;
		FCGX_InitRequest(&request, 0, 0);

		while(FCGX_Accept_r(&request) == 0) {
			const std::string filename(FCGX_GetParam("DOCUMENT_URI", request.envp));

			if (handlers.count(filename)) {
				handlers[filename]->handleHTTP(request);
			} else {
				errorHandle(request);
			}
		}
	}
}

int main() {
	std::unordered_map <std::string, Handler*> handlers;

	FCGX_Init();

	// Handler Registration
	KVSHandler kvshandler;
	kvshandler.open("/var/mykvs.data");
	handlers["/myapi/kvs"] = &kvshandler;

	// Main processing
	std::vector <std::thread> threads;
	for (size_t i = 0; i < THREAD_NUMBER; ++i) {
		threads.push_back(std::thread(&run, handlers));
	}

	// Ensure all local variables here will no longer be used
	for (auto &thread : threads) {
		thread.join();
	}
	return 0;
}
