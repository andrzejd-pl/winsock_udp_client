#include <iostream>
#include "WSASession.h"
#include "UDPSocket.h"
#include <vector>
#include "Packet.h"
#include <WS2tcpip.h>

int main() {

	try {
		WSASession Session;
		UDPSocket Socket;
		Packet data = Packet::PacketBuilder()
			.set_operation(0)
			.set_response(0)
			.set_ack(0)
			.set_bad_client(0)
			.set_bad_response(0)
			.set_error(0)
			.set_id(0)
			.set_overflow(0)
			.build();

		char buffer[3];
		std::string p = data.convertToSend();

		Socket.SendTo("127.0.0.1", 100, p.c_str(), p.size());
		Socket.RecvFrom(buffer, 2);

		Packet packet = Packet(buffer, 2);

		std::cout << "Packet response contains fields: \n\t" << "operation - " << packet.getOperation() <<
			"\n\t" << "response - " << packet.getResponse() <<
			"\n\t" << "id - " << packet.getId() <<
			"\n\t" << "ack - " << packet.getAck() <<
			"\n\t" << "overflow - " << packet.getOverflow() <<
			"\n\t" << "bad response - " << packet.getBadResponse() <<
			"\n\t" << "bad client - " << packet.getBadClient() <<
			std::endl;

	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}

	char c;
	std::cin >> c;

	return 0;
}
