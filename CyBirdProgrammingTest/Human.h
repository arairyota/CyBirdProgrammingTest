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

	void CheckWallet(); //���z�̒��g������

	//�w�肵��������ނ̃��X�g���o��
	template <typename T>
	std::list<T*> CashSort(Wallet* wallet);

	
private:
	Wallet* _wallet;		//���z
	ElectronicMoney* _electronicManey;	//�d�q�}�l�[

};


