#include "command.h"

Command::Command(Comando code, int peer_id)
	: code(code), peer_id(peer_id) {}

Command::Command(const Command& other) {
	this->code = other.code;
	this->peer_id = other.peer_id;
	this->args = other.args;
}

Command::Command(Command&& other) {
	this->code = other.code;
	this->peer_id = other.peer_id;
	this->args = other.args;
}

Command& Command::operator=(Command&& other) {
	this->code = other.code;
	this->peer_id = other.peer_id;
	this->args = other.args;
	return *this;
}

Comando Command::getCode() const {
	return this->code;
}

int Command::getPeerID() const {
	return this->peer_id;
}

void Command::setArg(const std::string& key, uint16_t value) {
	this->args[key] = value;
}

uint16_t Command::getArg(const std::string& key) {
	return this->args[key];
}
