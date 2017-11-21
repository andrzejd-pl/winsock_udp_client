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


	Packet(const unsigned short operation, const unsigned short response, const unsigned short id)
		: operation(operation),
		response(response),
		id(id) {}

	Packet() : operation(0), response(0), id(0) {}

public:
	Packet(const char* rawData, const unsigned short size);

	std::string convertToSend() const;

	unsigned short getOperation() const;
	unsigned short getResponse() const;
	unsigned short getId() const;

	class PacketBuilder {
	private:
		unsigned short operation;
		unsigned short response;
		unsigned short id;
	public:

		PacketBuilder set_operation(const unsigned short operation);
		PacketBuilder set_response(const unsigned short response);
		PacketBuilder set_id(const unsigned short id);

		Packet build();
	};
};

