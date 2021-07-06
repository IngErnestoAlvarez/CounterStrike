#ifndef COMMAND_H
#define COMMAND_H

#include <unordered_map>

#include "protocolo.h"
#include "types.h"

class Command {
private:
	Comando code;
	int peer_id;
	std::unordered_map<std::string, uint16_t> args;

public:
	Command(Comando code, int peer_id);
	Command(const Command& other);
	Command(Command&& other);
	Command& operator=(Command&& other);
	Comando getCode() const;
	int getPeerID() const;
	void setArg(const std::string& key, uint16_t value);
	uint16_t getArg(const std::string& key);
};

#endif
