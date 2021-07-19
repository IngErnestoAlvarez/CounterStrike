#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "login_queue.h"
#include "login_handler.h"
#include "acceptor.h"

class Server {
private:
	LoginQueue login_queue;
	LoginHandler login_handler;
	Acceptor acceptor;

public:
	Server(const std::string& config_filepath);
	~Server();

	void run();
};

#endif
