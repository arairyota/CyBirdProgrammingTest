
#include <iostream>

#include "Human.h"

#include "Wallet.h"

#include "ElectronicMoney.h"

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

void Human::Init()
{
	_wallet = new Wallet;
	_electronicManey = new ElectronicMoney;

	_wallet->Deposit();
}

//�������o���֐�
Cash* Human::CashTake(int num)
{
	Cash* cash = _wallet->GetCash(num);
	if (cash == nullptr) {
		switch (num)
		{
		case 0:
			std::cout << "���I10�~�ʂ������I\n" << std::endl;
			break;

		case 1:
			std::cout << "���I50�~�ʂ������I\n" << std::endl;
			break;

		case 2:
			std::cout << "���I100�~�ʂ������I\n" << std::endl;
			break;

		case 3:
			std::cout << "���I500�~�ʂ������I\n" << std::endl;
			break;

		case 4:
			std::cout << "���I10000�~�ʂ������I\n" << std::endl;
			break;

		case 5:
			std::cout << "���I5000�~�ʂ������I\n" << std::endl;
			break;

		case 6:
			std::cout << "���I10000�~�ʂ������I\n" << std::endl;
			break;

		default:
			std::cout << "����ȊO�̌����͎����Ȃ���`�ł�\n" << std::endl;
			return nullptr;
		}
	}

	return cash;
}

//���z�̒��m�F
void Human::CheckWallet()
{
	int sum = 0; //���v

	std::cout << "���z�̒����m�F����\n" << std::endl;
	std::cout << "10�~�ʂ�" << CashSort<Cash10En>(_wallet).size() << "��\n" << std::endl;
	std::cout << "50�~�ʂ�" << CashSort<Cash50En>(_wallet).size() << "��\n" << std::endl;
	std::cout << "100�~�ʂ�" << CashSort<Cash100En>(_wallet).size() << "��\n" << std::endl;
	std::cout << "500�~�ʂ�" << CashSort<Cash500En>(_wallet).size() << "��\n" << std::endl;
	std::cout << "1000�~�ʂ�" << CashSort<Cash1000En>(_wallet).size() << "��\n" << std::endl;
	std::cout << "5000�~�ʂ�" << CashSort<Cash5000En>(_wallet).size() << "��\n" << std::endl;
	std::cout << "10000�~�ʂ�" << CashSort<Cash10000En>(_wallet).size() << "��\n" << std::endl;

	for (auto it : _wallet->GetCashList()) {
		sum += it->GetValue();
	}

	std::cout << "���v��" << sum << "�~�����Ă���\n" << std::endl;
}

template<typename T>
inline std::list<T*> Human::CashSort(Wallet* wallet)
{
	std::list<T*> cashList;
	for (auto it : wallet->GetCashList()) {
		if (typeid(*it) == typeid(T)) {
			cashList.push_back((T*)it);
		}
	}

	return cashList;
}