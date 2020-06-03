#pragma once

class ElectronicMoney;

class Server
{
public:
	bool Subtraction(ElectronicMoney* money, int price);
	void Check(ElectronicMoney* money);

private:
	int _price = 0;
};

