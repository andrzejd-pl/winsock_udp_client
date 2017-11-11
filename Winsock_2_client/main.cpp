#include <iostream>
#include "WSASession.h"
#include "UDPSocket.h"
#include <vector>
#include "Packet.h"

int main() {

	try {
		WSASession Session;
		UDPSocket Socket;
		Packet data(1, 1, 5);

		char buffer[3];
		std::string p = data.convertToSend();

		Socket.SendTo("127.0.0.1", 100, p.c_str(), p.size());
		Socket.RecvFrom(buffer, 2);
		Packet rt(buffer, 2);
		std::cout << rt.getOperation() << " " << rt.getResponse() << " " << rt.getId() << std::endl;
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}

	char c;
	std::cin >> c;

	return 0;
}
