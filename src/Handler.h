/*
 * Handler.h
 *
 *  Created on: Oct 15, 2017
 *      Author: nhirokinet
 */

#ifndef SRC_HANDLER_H_
#define SRC_HANDLER_H_

#include <fcgio.h>
#include <queue>
#include <shared_mutex>
#include <string>
#include <vector>

class Handler {
public:
	Handler();
	virtual ~Handler();

	void open(const std::string &filename);
	void handleHTTP(FCGX_Request &request);

protected:
	virtual std::string read(const std::vector <std::string> & data) const = 0;
	virtual void write(const std::vector <std::string> & data) = 0;

private:
	static void _writeToDiskFromQueue(Handler *handler);

	std::queue <std::string> _queue;
	std::shared_timed_mutex _queue_mutex;
	std::shared_timed_mutex _mutex;
	int _fd;
};

#endif /* SRC_HANDLER_H_ */
