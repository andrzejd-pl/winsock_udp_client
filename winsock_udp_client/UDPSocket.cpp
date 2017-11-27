#include "UDPSocket.h"
#include <system_error>
#include <WS2tcpip.h>


UDPSocket::UDPSocket() {
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Error opening socket");
}


UDPSocket::~UDPSocket() {
	closesocket(sock);
}

void UDPSocket::SendTo(const std::string& address, unsigned short port, const char* buffer, int len, int flags) {
	sockaddr_in add;
	add.sin_family = AF_INET;
	/*add.sin_addr.s_addr = */
	InetPton(AF_INET, address.c_str(), &add.sin_addr.s_addr);
	add.sin_port = htons(port);
	int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
}

void UDPSocket::SendTo(sockaddr_in& address, const char* buffer, int len, int flags) {
	int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR *>(&address), sizeof(address));
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
}

// buffer musi byc o 1 wiekszy, bo to co ta funkcja zwraca w argumencie buff modyfikuje pole len+1
sockaddr_in UDPSocket::RecvFrom(char* buff, int len, int flags) {
	sockaddr_in from;
	int size = sizeof(from);
	int ret = recvfrom(sock, buff, len, flags, reinterpret_cast<SOCKADDR *>(&from), &size);
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "recvfrom failed");

	//make the buff zero terminated

	//  ret = maksymalnie len+1
	buff[ret] = 0;
	return from;
}

void UDPSocket::Bind(unsigned short port) {
	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = htonl(INADDR_ANY);
	add.sin_port = htons(port);

	int ret = bind(sock, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Bind failed");
}
