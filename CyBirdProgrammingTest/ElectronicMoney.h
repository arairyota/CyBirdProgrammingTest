#pragma once

#include "Money.h"

class ElectronicMoney : public Money
{
public:
	ElectronicMoney() { _value = 1000; }

	int GetValue()override {
		return _value;
	}

	//引数の値だけ_valueを引く
	void Subtraction(int value);

};

