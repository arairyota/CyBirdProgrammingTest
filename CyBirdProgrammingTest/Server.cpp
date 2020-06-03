#include <iostream>

#include "ElectronicMoney.h"

#include "Server.h"

bool Server::Subtraction(ElectronicMoney* money, int price)
{
	if (money == nullptr) {

		std::cout << "電子マネーが読み取れませんでした\n" << std::endl;
		return false;
	}
	else {
		money->Subtraction(price);
		_price = price;
		return true;
	}

	return false;
}

void Server::Check(ElectronicMoney* money)
{
	std::cout << "この電子マネーの残高は" << money->GetValue() << "円です\n" << std::endl;
	std::cout << "今回の取引で" <<_price << "円引きました\n" << std::endl;
}
