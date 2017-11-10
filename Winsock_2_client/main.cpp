#include <iostream>
#include "WSASession.h"
#include "UDPSocket.h"
#include <vector>

struct pakiet {
private:
	unsigned short operacja;
	unsigned short odpowiedz;
	unsigned short id;
	unsigned short ack;
public:
	pakiet(unsigned int opr, unsigned short ret, short id, short ack) {
		this->operacja = opr;
		this->odpowiedz = ret;
		this->id = id;
		this->ack = ack;
	}

	pakiet(char rawData[], unsigned short size) {
		if (size > 2) throw std::exception("To large buffor!!!");
		
		unsigned short buff = rawData[0];
		operacja = 0 | ((buff >> 4) & 0x0F);
		odpowiedz = 0 | ((buff >> 1) & 0x07);
		id = 0 | ((buff & 0x01) << 3);

		buff = rawData[1];
		id |= ((buff >> 5) & 0x07);
		ack = 0 | ((buff >> 4) & 0x01);
	}

	std::string convertToSend() {
		std::string rt;
		char buff = 0;

		buff |= (operacja << 4);
		buff |= (odpowiedz << 1);
		buff |= (id >> 3);
		rt.push_back(buff);

		buff = 0;
		buff |= (id << 5);
		buff |= (ack << 4);
		buff |= (0x0F);
		rt.push_back(buff);

		return rt;
	}

	unsigned short getOperation() const {
		return operacja;
	}

	unsigned short getResponse() const
	{
		return odpowiedz;
	}

	unsigned short getAckFlag() const
	{
		return ack;
	}

	unsigned short getId() const
	{
		return id;
	}
};

int main() {

	try {
		WSASession Session;
		UDPSocket Socket;
		pakiet data(1, 1, 5, 1);

		char buffer[3];
		std::string p = data.convertToSend();

		Socket.SendTo("127.0.0.1", 100, p.c_str(), p.size());
		Socket.RecvFrom(buffer, 2);
		pakiet rt(buffer, 2);
		std::cout << rt.getOperation() << " " << rt.getResponse() << " " << rt.getId() << " " << rt.getAckFlag() << std::endl;
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}

	char c;
	std::cin >> c;

	return 0;
}
