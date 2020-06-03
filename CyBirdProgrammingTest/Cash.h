#pragma once

#include "Money.h"

//現金継承元クラス
class Cash : public Money
{
public:
	//int _value; //自分自身の値段

	int GetValue() override { 
		if (this == nullptr) return 0;

		return _value; 
	}
};

class Cash10En : public Cash
{
public:
	Cash10En() { _value = 10; }

	//int GetValue() override { return _value; };

};

class Cash50En : public Cash
{
public:
	Cash50En() { _value = 50; }

	//int GetValue() override { return _value; };

};

class Cash100En : public Cash
{
public:
	Cash100En() { _value = 100; }

	//int GetValue() override { return _value; };

};

class Cash500En : public Cash
{
public:
	Cash500En() { _value = 500; }

	//int GetValue() override { return _value; };

};

class Cash1000En : public Cash
{
public:
	Cash1000En() { _value = 1000; }

	//int GetValue() override { return _value; };

};

class Cash5000En : public Cash
{
public:
	Cash5000En() { _value = 5000; }

	//int GetValue() override { return _value; };

};

class Cash10000En : public Cash
{
public:
	Cash10000En() { _value = 10000; }

	//int GetValue() override { return _value; };

};