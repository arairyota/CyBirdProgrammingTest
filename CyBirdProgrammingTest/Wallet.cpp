#include <iostream>

#include "Cash.h"

#include "Wallet.h"

//入金する
void Wallet::Deposit()
{
	for (int i = 0; i < 15; i++) {
		_cashList.push_back(new Cash10En);
	}

	for (int i = 0; i < 3; i++) {
		_cashList.push_back(new Cash50En);
	}

	for (int i = 0; i < 2; i++) {
		_cashList.push_back(new Cash100En);
	}

	_cashList.push_back(new Cash500En);
	_cashList.push_back(new Cash1000En);
	_cashList.push_back(new Cash5000En);
	_cashList.push_back(new Cash10000En);

	Total();
}

//合計を出す
int Wallet::Total()
{
	_totalMoney = 0;

	for (auto i : _cashList) {
		_totalMoney += i->GetValue();
	}

	return _totalMoney;
}

void Wallet::Check()
{
	std::cout << "現在の財布の中身は";
	std::cout << Total();
	std::cout << "円です";




}

Cash* Wallet::GetCash(int num)
{
	Cash* returnCash = nullptr;

	switch (num)
	{
	case 0:
		for (auto it = _cashList.begin(); it != _cashList.end();) {
			auto pCash = *it;
			if (typeid(*pCash) == typeid(Cash10En)) {
				returnCash = pCash;
				it = _cashList.erase(it);
				break;
			} 
			else {
				++it;
			}
		}

		break;

	case 1:
		for (auto it = _cashList.begin(); it != _cashList.end();) {
			auto pCash = *it;
			if (typeid(*pCash) == typeid(Cash50En)) {
				returnCash = pCash;
				it = _cashList.erase(it);
				break;
			}
			else {
				++it;
			}
		}
		break;

	case 2:
		for (auto it = _cashList.begin(); it != _cashList.end();) {
			auto pCash = *it;
			if (typeid(*pCash) == typeid(Cash100En)) {
				returnCash = pCash;
				it = _cashList.erase(it);
				break;
			}
			else {
				++it;
			}
		}
		break;

	case 3:
		for (auto it = _cashList.begin(); it != _cashList.end();) {
			auto pCash = *it;
			if (typeid(*pCash) == typeid(Cash500En)) {
				returnCash = pCash;
				it = _cashList.erase(it);
				break;
			}
			else {
				++it;
			}
		}
		break;

	case 4:
		for (auto it = _cashList.begin(); it != _cashList.end();) {
			auto pCash = *it;
			if (typeid(*pCash) == typeid(Cash1000En)) {
				returnCash = pCash;
				it = _cashList.erase(it);
				break;
			}
			else {
				++it;
			}
		}
		break;

	case 5:
		for (auto it = _cashList.begin(); it != _cashList.end();) {
			auto pCash = *it;
			if (typeid(*pCash) == typeid(Cash5000En)) {
				returnCash = pCash;
				it = _cashList.erase(it);
				break;
			}
			else {
				++it;
			}
		}
		break;

	case 6:
		for (auto it = _cashList.begin(); it != _cashList.end();) {
			auto pCash = *it;
			if (typeid(*pCash) == typeid(Cash10000En)) {
				returnCash = pCash;
				it = _cashList.erase(it);
				break;
			}
			else {
				++it;
			}
		}
		break;


	default:
		break;
	}

	if (returnCash == nullptr) {
		
	}
	
	return returnCash;
}
