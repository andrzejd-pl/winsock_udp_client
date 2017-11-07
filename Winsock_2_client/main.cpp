#include <iostream>
#include "WSASession.h"
#include "UDPSocket.h"

int main() {

	try {
		WSASession Session;
		UDPSocket Socket;
		std::string data = "hello world";
		char buffer[100];

		Socket.SendTo("127.0.0.1", 100, data.c_str(), data.size());
		Socket.RecvFrom(buffer, 100);
		std::cout << buffer;
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}

	char c;
	std::cin >> c;

	return 0;
}