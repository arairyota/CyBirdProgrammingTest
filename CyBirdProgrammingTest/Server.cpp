#include <iostream>

#include "ElectronicMoney.h"

#include "Server.h"

bool Server::Subtraction(ElectronicMoney* money, int price)
{
	if (money == nullptr) {

		std::cout << "�d�q�}�l�[���ǂݎ��܂���ł���\n" << std::endl;
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
	std::cout << "���̓d�q�}�l�[�̎c����" << money->GetValue() << "�~�ł�\n" << std::endl;
	std::cout << "����̎����" <<_price << "�~�����܂���\n" << std::endl;
}
