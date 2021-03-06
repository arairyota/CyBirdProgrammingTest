
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

//現金を出す関数
Cash* Human::CashTake(int num)
{
	Cash* cash = _wallet->GetCash(num);
	if (cash == nullptr) {
		switch (num)
		{
		case 0:
			std::cout << "あ！10円玉が無い！\n" << std::endl;
			break;

		case 1:
			std::cout << "あ！50円玉が無い！\n" << std::endl;
			break;

		case 2:
			std::cout << "あ！100円玉が無い！\n" << std::endl;
			break;

		case 3:
			std::cout << "あ！500円玉が無い！\n" << std::endl;
			break;

		case 4:
			std::cout << "あ！10000円玉が無い！\n" << std::endl;
			break;

		case 5:
			std::cout << "あ！5000円玉が無い！\n" << std::endl;
			break;

		case 6:
			std::cout << "あ！10000円玉が無い！\n" << std::endl;
			break;

		default:
			std::cout << "それ以外の現金は持たない主義でね\n" << std::endl;
			return nullptr;
		}
	}

	return cash;
}

//財布の中確認
void Human::CheckWallet()
{
	int sum = 0; //合計

	std::cout << "財布の中を確認した\n" << std::endl;
	std::cout << "10円玉が" << CashSort<Cash10En>(_wallet).size() << "枚\n" << std::endl;
	std::cout << "50円玉が" << CashSort<Cash50En>(_wallet).size() << "枚\n" << std::endl;
	std::cout << "100円玉が" << CashSort<Cash100En>(_wallet).size() << "枚\n" << std::endl;
	std::cout << "500円玉が" << CashSort<Cash500En>(_wallet).size() << "枚\n" << std::endl;
	std::cout << "1000円玉が" << CashSort<Cash1000En>(_wallet).size() << "枚\n" << std::endl;
	std::cout << "5000円玉が" << CashSort<Cash5000En>(_wallet).size() << "枚\n" << std::endl;
	std::cout << "10000円玉が" << CashSort<Cash10000En>(_wallet).size() << "枚\n" << std::endl;

	for (auto it : _wallet->GetCashList()) {
		sum += it->GetValue();
	}

	std::cout << "合計で" << sum << "円入っていた\n" << std::endl;
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