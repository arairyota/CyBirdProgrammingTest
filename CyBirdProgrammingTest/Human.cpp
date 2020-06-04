
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

//Œ»‹à‚ðo‚·ŠÖ”
Cash* Human::CashTake(int num)
{
	Cash* cash = _wallet->GetCash(num);
	if (cash == nullptr) {
		switch (num)
		{
		case 0:
			std::cout << "‚ I10‰~‹Ê‚ª–³‚¢I\n" << std::endl;
			break;

		case 1:
			std::cout << "‚ I50‰~‹Ê‚ª–³‚¢I\n" << std::endl;
			break;

		case 2:
			std::cout << "‚ I100‰~‹Ê‚ª–³‚¢I\n" << std::endl;
			break;

		case 3:
			std::cout << "‚ I500‰~‹Ê‚ª–³‚¢I\n" << std::endl;
			break;

		case 4:
			std::cout << "‚ I10000‰~‹Ê‚ª–³‚¢I\n" << std::endl;
			break;

		case 5:
			std::cout << "‚ I5000‰~‹Ê‚ª–³‚¢I\n" << std::endl;
			break;

		case 6:
			std::cout << "‚ I10000‰~‹Ê‚ª–³‚¢I\n" << std::endl;
			break;

		default:
			std::cout << "‚»‚êˆÈŠO‚ÌŒ»‹à‚ÍŽ‚½‚È‚¢Žå‹`‚Å‚Ë\n" << std::endl;
			return nullptr;
		}
	}

	return cash;
}

//à•z‚Ì’†Šm”F
void Human::CheckWallet()
{
	int sum = 0; //‡Œv

	std::cout << "à•z‚Ì’†‚ðŠm”F‚µ‚½\n" << std::endl;
	std::cout << "10‰~‹Ê‚ª" << CashSort<Cash10En>(_wallet).size() << "–‡\n" << std::endl;
	std::cout << "50‰~‹Ê‚ª" << CashSort<Cash50En>(_wallet).size() << "–‡\n" << std::endl;
	std::cout << "100‰~‹Ê‚ª" << CashSort<Cash100En>(_wallet).size() << "–‡\n" << std::endl;
	std::cout << "500‰~‹Ê‚ª" << CashSort<Cash500En>(_wallet).size() << "–‡\n" << std::endl;
	std::cout << "1000‰~‹Ê‚ª" << CashSort<Cash1000En>(_wallet).size() << "–‡\n" << std::endl;
	std::cout << "5000‰~‹Ê‚ª" << CashSort<Cash5000En>(_wallet).size() << "–‡\n" << std::endl;
	std::cout << "10000‰~‹Ê‚ª" << CashSort<Cash10000En>(_wallet).size() << "–‡\n" << std::endl;

	for (auto it : _wallet->GetCashList()) {
		sum += it->GetValue();
	}

	std::cout << "‡Œv‚Å" << sum << "‰~“ü‚Á‚Ä‚¢‚½\n" << std::endl;
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