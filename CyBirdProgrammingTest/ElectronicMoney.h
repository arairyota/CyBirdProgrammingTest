#pragma once

#include "Money.h"

class ElectronicMoney : public Money
{
public:
	ElectronicMoney() { _value = 1000; }

	int GetValue()override {
		return _value;
	}

	//�����̒l����_value������
	void Subtraction(int value);

};

