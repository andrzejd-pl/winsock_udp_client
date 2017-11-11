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
	unsigned short ack;
	unsigned short error;
	unsigned short overflow;
	unsigned short bad_response;
	unsigned short bad_client;


	Packet(const unsigned short operation, const unsigned short response, const unsigned short id, const unsigned short ack, const unsigned short error, const unsigned short overflow, const unsigned short bad_respone, const unsigned short bad_client)
		: operation(operation),
		response(response),
		id(id),
		ack(ack),
		error(error),
		overflow(overflow),
		bad_response(bad_respone),
		bad_client(bad_client) {}

	Packet() : operation(0), response(0), id(0), ack(0), error(0), overflow(0), bad_response(0), bad_client(0) {}

public:
	Packet(const char* rawData, const unsigned short size);

	std::string convertToSend() const;

	unsigned short getOperation() const;
	unsigned short getResponse() const;
	unsigned short getId() const;
	unsigned short getAck() const;
	unsigned short getError() const;
	unsigned short getOverflow() const;
	unsigned short getBadResponse() const;
	unsigned short getBadClient() const;

	class PacketBuilder {
	private:
		unsigned short operation;
		unsigned short response;
		unsigned short id;
		unsigned short ack;
		unsigned short error;
		unsigned short overflow;
		unsigned short bad_response;
		unsigned short bad_client;
	public:

		PacketBuilder set_operation(const unsigned short operation);
		PacketBuilder set_response(const unsigned short response);
		PacketBuilder set_id(const unsigned short id);
		PacketBuilder set_ack(const unsigned short ack);
		PacketBuilder set_error(const unsigned short error);
		PacketBuilder set_overflow(const unsigned short overflow);
		PacketBuilder set_bad_response(const unsigned short bad_respone);
		PacketBuilder set_bad_client(const unsigned short bad_client);

		Packet build();
	};
};

