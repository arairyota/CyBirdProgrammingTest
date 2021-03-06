#include "TicketMachine.h"
#include "Human.h"
#include "Wallet.h"
#include "ElectronicMoney.h"
#include "Server.h"

#include <iostream>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

void TicketMachine::Init()
{
	_guest = nullptr;

	_server = new Server;

	_mode = 0;

	for (int i = 0; i < 6; i++) {
		_cashList[i].clear();
	}
	

	for(int i =0; i < 6; i++) _changList[i].clear();
}

void TicketMachine::StandbyMode(Human* guest)
{
	do {
		Draw("いらっしゃいませ\n");
		
	} while (guest == nullptr);

	_guest = guest;
}

void TicketMachine::SelectMode()
{
	_mode = 0;

	while (!(_mode >= CASH && _mode <= ELECT_CASH)) {
		_mode = 0;
		std::cout << "現金での購入の場合は1\n電子マネーでの購入の場合は2を入力してください\n";
		scanf("%d", &_mode);

	}  //1か2が選択されるまで繰り返す
}

//金銭要求
void TicketMachine::MonetaryDemand()
{
	int sum = 0; //投入された合計金額

	Draw("お金を投入してください\n");

	//選択マナー払いが選択されたら
	if (_mode == CASH) {
		do {
			std::cout << "現在の投入金額は" << sum << "円です\n" << std::endl;
			Draw("10円玉を入れる場合は0\n");
			Draw("50円玉を入れる場合は1\n");
			Draw("100円玉を入れる場合は2\n");
			Draw("500円玉を入れる場合は3\n");
			Draw("1000円玉を入れる場合は4\n");
			Draw("5000円玉を入れる場合は5\n");
			Draw("10000円玉を入れる場合は6\n");
			int inputNumber; //金種選択用変数
			scanf("%d", &inputNumber);

			Cash* cash = _guest->CashTake(inputNumber);
			if (cash != nullptr) _cashList[inputNumber].push_back(cash); //選択した現金が0ではなかった場合実行
			
			sum += cash->GetValue();

		} while (!(_cashPrice <= sum)); //チケットの金額に満たせたら
	}

	//電子マネー払いが選択されたら
	if (_mode == ELECT_CASH) {
		if (_electronicPrice < _guest->GetElectronicMoney()->GetValue()) {
			//Serverにアクセスして成功したら減算 失敗なら最初からやり直し
			if (_server->Subtraction(_guest->GetElectronicMoney(), _electronicPrice)) {
				std::cout << "サーバーとの通信が成功しました\n" << std::endl;
				std::cout << "電子マネーから" << _electronicPrice << "円引きました\n" << std::endl;
			}
			else
			{
				std::cout << "サーバーとの通信が失敗しました\n" << std::endl;
			}

			
			sum = _electronicPrice;
		}
		else {
			std::cout << "電子マネー残高が足りません\n" << std::endl;
		}
	}

	std::cout <<  sum << "円投入されたので取引を実行します\n" << std::endl;

}

void TicketMachine::Draw(std::string letter)
{
	std::cout << letter << std::endl;
}

//合計関数
//引数(合計を出したいCashクラスのリストのアドレス)
int TicketMachine::Total(std::list<Cash*>* list)
{
	int sum = 0;

	for (auto it : *list) {
		sum += it->GetValue();
	}

	return sum;
}


void TicketMachine::Buy()
{
	int change = 0; //おつり合計
	int sum = 0;
	if (CASH == _mode) {
		for (int i = 0; i < 6; i++) {
			sum += Total(&_cashList[i]);
		}
		change = sum - _cashPrice;
		Change(change);
	}

	if (ELECT_CASH == _mode) {

	}

	
}

void TicketMachine::Change(int change)
{
	int remain = change;	//あまり
	int changeSum = 0;		//おつりの合計
	
	
	int numCoins = remain / 10000 ; //硬貨の数
	for (int i = 0; i < numCoins; i++) _changList[6].push_back(new Cash10000En);
	remain %= 10000;
	
	numCoins = remain / 5000; //硬貨の数
	for (int i = 0; i < numCoins; i++) _changList[5].push_back(new Cash5000En);
	remain %= 5000;
	
	numCoins = remain / 1000; //硬貨の数
	for (int i = 0; i < numCoins; i++) _changList[4].push_back(new Cash1000En);
	remain %= 1000;
	
	numCoins = remain / 500; //硬貨の数
	for (int i = 0; i < numCoins; i++) _changList[3].push_back(new Cash500En);
	remain %= 500;
	
	numCoins = remain / 100; //硬貨の数
	for (int i = 0; i < numCoins; i++) _changList[2].push_back(new Cash100En);
	remain %= 100;
	
	numCoins = remain / 50; //硬貨の数
	for (int i = 0; i < numCoins; i++) _changList[1].push_back(new Cash50En);
	remain %= 50;
	
	numCoins = remain / 10; //硬貨の数
	for (int i = 0; i < numCoins; i++) _changList[0].push_back(new Cash10En);
	remain %= 10;
	
	for (int i = 0; i < 6; i++) {
		 changeSum += Total(&_changList[i]);
	}

	std::cout << "おつりの金種とその数は\n" << std::endl;
	std::cout << "10000円が" << _changList[6].size() << "枚\n" << std::endl;
	std::cout << "5000円が" << _changList[5].size() << "枚\n" << std::endl;
	std::cout << "1000円が" << _changList[4].size() << "枚\n" << std::endl;
	std::cout << "500円が" << _changList[3].size() << "枚\n" << std::endl;
	std::cout << "100円が" << _changList[2].size() << "枚\n" << std::endl;
	std::cout << "50円が" << _changList[1].size() << "枚\n" << std::endl;
	std::cout << "10円が" << _changList[0].size() << "枚\n" << std::endl;


	std::cout << "おつりの合計金額は" << changeSum << "円です\n" << std::endl;
}

void TicketMachine::Check()
{
	int sum = 0;

	if (_mode == 1) {

		std::cout << "投入された金種とその数は\n" << std::endl;
		std::cout << "10円玉が" << _cashList[0].size() << "枚\n" << std::endl;
		std::cout << "50円玉が" << _cashList[1].size() << "枚\n" << std::endl;
		std::cout << "100円玉が" << _cashList[2].size() << "枚\n" << std::endl;
		std::cout << "500円玉が" << _cashList[3].size() << "枚\n" << std::endl;
		std::cout << "1000円玉が" << _cashList[4].size() << "枚\n" << std::endl;
		std::cout << "5000円玉が" << _cashList[5].size() << "枚\n" << std::endl;
		std::cout << "10000円玉が" << _cashList[6].size() << "枚\n" << std::endl;

		for (int i = 0; i < 6; i++)
			for (auto it : _cashList[i])
				sum += it->GetValue();

		std::cout << "投入された金額の合計は" << sum << "円です\n" << std::endl;
	}

	if (_mode == 2) {
		_server->Check(_guest->GetElectronicMoney());
	}
}
