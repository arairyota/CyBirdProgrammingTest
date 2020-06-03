#pragma once

#include <list>
#include <string>

//‘O•ûéŒ¾
class Money;
class Human;
class Cash;
class Server;

enum PAY_MODE {
	INIT = 0,
	CASH,
	ELECT_CASH,
} ;

class TicketMachine
{
public:
	void Init();

	void StandbyMode(Human* guest);

	void SelectMode();

	void MonetaryDemand();	//‹à‘K—v‹

	void Draw( std::string letter ); //ˆø”‚É“ü‚ê‚½“à—e‚ğ•`‰æ

	int Total(std::list<Cash*>* list);

	void Buy();

	void Change(int change); //‚¨‚Â‚èŒvZˆ—

	void Check();

private:
	const int _cashPrice = 130;			//Œ»‹à‚Å‚Ìw“ü‰¿Ši
	const int _electronicPrice = 124;	//“dqƒ}ƒl[‚Ìw“ü‰¿Ši

	Human* _guest;	//‹q
	Server* _server;

	int _mode =0;

	std::list<Cash*> _cashList[7];
	std::list<Cash*> _changList[7]; //‚¨‚Â‚èƒŠƒXƒg
};

