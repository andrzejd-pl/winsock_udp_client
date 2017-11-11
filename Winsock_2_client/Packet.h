#pragma once
#include <string>

/*
	TODO:
	1) walidowaæ pola struktury
	2) ...
*/

struct Packet {
private:
	unsigned short operation;
	unsigned short response;
	unsigned short id;
public:
	Packet(const unsigned short opr, const unsigned short ret, const unsigned short id);
	Packet(const char* rawData, const unsigned short size);

	std::string convertToSend() const;

	unsigned short getOperation() const;

	unsigned short getResponse() const;

	unsigned short getId() const;
};


