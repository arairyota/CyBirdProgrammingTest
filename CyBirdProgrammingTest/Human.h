#pragma once
#include <typeinfo>
#include <list>

class Wallet;

class Cash;

class ElectronicMoney;

class Human
{
public:
	void Init();

	Cash* CashTake(int num);

	Wallet* GetWallet() { return _wallet; }
	ElectronicMoney* GetElectronicMoney() { return _electronicManey; }

	void CheckWallet(); //財布の中身を見る

	//指定した現金種類のリストを出す
	template <typename T>
	std::list<T*> CashSort(Wallet* wallet);

	
private:
	Wallet* _wallet;		//財布
	ElectronicMoney* _electronicManey;	//電子マネー

};


