#pragma once
#include <list>

#include "Cash.h"

class Wallet
{
public:
	void Deposit(); //“ü‹à‚·‚é

	int Total();	//‡Œv
	
	void Check();	//’†g‚ğ•\¦

	Cash* GetCash(int num);

	std::list<Cash*> GetCashList() { return _cashList; }

private:
	std::list<Cash*> _cashList;

	//std::list<Cash10En*> _cash10List;
	//std::list<Cash50En*> _cash50List;
	//std::list<Cash100En*> _cash100List;
	//std::list<Cash500En*> _cash500List;
	//std::list<Cash1000En*> _cash1000List;
	//std::list<Cash5000En*> _cash5000List;
	//std::list<Cash10000En*> _cash10000List;

	int _totalMoney = 0;
};

