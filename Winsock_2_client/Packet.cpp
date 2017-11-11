#include "Packet.h"

Packet::Packet(const char* rawData, const unsigned short size) {
	if (size > 2) throw std::exception("To large buffor!!!");

	unsigned short buff = rawData[0];
	operation = 0 | ((buff >> 4) & 0x0F);
	response = 0 | ((buff >> 1) & 0x07);
	id = 0 | ((buff & 0x01) << 3);

	buff = rawData[1];
	id |= ((buff >> 5) & 0x07);
	ack = 0 | ((buff >> 4) & 0x01);
	overflow = 0 | ((buff >> 3) & 0x01);
	bad_response = 0 | ((buff >> 2) & 0x01);
	bad_client = 0 | ((buff >> 1) & 0x01);
}

std::string Packet::convertToSend() const {
	std::string rt;
	char buff = 0;

	buff |= (operation << 4);
	buff |= (response << 1);
	buff |= (id >> 3);
	rt.push_back(buff);

	buff = 0;
	buff |= (id << 5);
	buff |= (ack << 4);
	buff |= (overflow << 3);
	buff |= (error << 2);
	buff |= (bad_response << 1);
	buff |= (bad_client);
	rt.push_back(buff);

	return rt;
}

unsigned short Packet::getOperation() const {
	return operation;
}

unsigned short Packet::getResponse() const {
	return response;
}

unsigned short Packet::getId() const {
	return id;
}

unsigned short Packet::getAck() const {
	return ack;
}

unsigned short Packet::getError() const {
	return error;
}

unsigned short Packet::getOverflow() const {
	return overflow;
}

unsigned short Packet::getBadResponse() const {
	return bad_response;
}

unsigned short Packet::getBadClient() const {
	return bad_client;
}

Packet::PacketBuilder Packet::PacketBuilder::set_operation(const unsigned short operation) {
	this->operation = operation;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_response(const unsigned short response) {
	this->response = response;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_id(const unsigned short id) {
	this->id = id;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_ack(const unsigned short ack) {
	this->ack = ack;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_error(const unsigned short error) {
	this->error = error;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_overflow(const unsigned short overflow) {
	this->overflow = overflow;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_bad_response(const unsigned short bad_respone) {
	this->bad_response = bad_respone;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_bad_client(const unsigned short bad_client) {
	this->bad_client = bad_client;
	return *this;
}

Packet Packet::PacketBuilder::build() {
	return Packet(operation, response, id, ack, error, overflow, response, bad_client);

}