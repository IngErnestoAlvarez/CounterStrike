#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "acceptor.h"

class Server {
private:
	Acceptor acceptor;

public:
	Server(const std::string& config_filepath);
	~Server();

	void run();
};

#endif
