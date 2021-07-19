#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

#include "my_thread.h"
#include "protocolo.h"
#include "socket.h"
#include <string>

class LoginQueue;
class socket_t;

class LoginHandler : public Thread {
private:
	LoginQueue& login_queue;
	Protocolo protocol;
	socket_t socket;

public:
	LoginHandler(const std::string& config_filepath, LoginQueue& login_queue);
	void run() override;
	void stop();
};

#endif
