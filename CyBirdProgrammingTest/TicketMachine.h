#pragma once

#include <list>
#include <string>

//前方宣言
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

	void MonetaryDemand();	//金銭要求

	void Draw( std::string letter ); //引数に入れた内容を描画

	int Total(std::list<Cash*>* list);

	void Buy(); //購入処理

	void Change(int change); //おつり計算処理

	void Check();

private:
	const int _cashPrice = 130;			//現金での購入価格
	const int _electronicPrice = 124;	//電子マネーの購入価格

	Human* _guest;	//客
	Server* _server;

	int _mode =0;

	std::list<Cash*> _cashList[7];
	std::list<Cash*> _changList[7]; //おつりリスト
};

