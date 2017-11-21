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
			.set_id(0)
			.build();

		char buffer[3];
		std::string p = data.convertToSend();

		Socket.SendTo("127.0.0.1", 100, p.c_str(), p.size());
		while (true) {
			Socket.RecvFrom(buffer, 2);

			Packet packet = Packet(buffer, 2);

			std::cout << "Packet response contains fields: \n\t" << "operation - " << packet.getOperation() <<
				"\n\t" << "response - " << packet.getResponse() <<
				"\n\t" << "id - " << packet.getId() <<
				std::endl;
		}
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}

	char c;
	std::cin >> c;

	return 0;
}
