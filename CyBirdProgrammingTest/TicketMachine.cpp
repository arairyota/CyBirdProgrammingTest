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
		Draw("‚¢‚ç‚Á‚µ‚á‚¢‚Ü‚¹\n");
		
	} while (guest == nullptr);

	_guest = guest;
}

void TicketMachine::SelectMode()
{
	_mode = 0;
	do {
		std::cout << "Œ»‹à‚Å‚Ìw“ü‚Ìê‡‚Í1\n“dqƒ}ƒl[‚Å‚Ìw“ü‚Ìê‡‚Í2‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n";
		scanf("%d", &_mode);

	} while (_mode == INIT || _mode > ELECT_CASH); //1‚©2‚ª‘I‘ğ‚³‚ê‚é‚Ü‚ÅŒJ‚è•Ô‚·


	
}

//‹à‘K—v‹
void TicketMachine::MonetaryDemand()
{
	int sum = 0; //“Š“ü‚³‚ê‚½‡Œv‹àŠz
	int total = 0;
	bool isMoneyInput = false;

	Draw("‚¨‹à‚ğ“Š“ü‚µ‚Ä‚­‚¾‚³‚¢\n");

	if (_mode == CASH) {
		do {
			std::cout << "Œ»İ‚Ì“Š“ü‹àŠz‚Í" << sum << "‰~‚Å‚·\n" << std::endl;
			//printf("Œ»İ‚Ì“Š“ü‹àŠz‚Í%d‰~‚Å‚·\n", sum);
			Draw("10‰~‹Ê‚ğ“ü‚ê‚éê‡‚Í0\n");
			Draw("50‰~‹Ê‚ğ“ü‚ê‚éê‡‚Í1\n");
			Draw("100‰~‹Ê‚ğ“ü‚ê‚éê‡‚Í2\n");
			Draw("500‰~‹Ê‚ğ“ü‚ê‚éê‡‚Í3\n");
			Draw("1000‰~‹Ê‚ğ“ü‚ê‚éê‡‚Í4\n");
			Draw("5000‰~‹Ê‚ğ“ü‚ê‚éê‡‚Í5\n");
			Draw("10000‰~‹Ê‚ğ“ü‚ê‚éê‡‚Í6\n");
			int inputNumber;
			scanf("%d", &inputNumber);

			Cash* cash = _guest->CashTake(inputNumber);
			if (cash != nullptr) _cashList[inputNumber].push_back(cash); //‘I‘ğ‚µ‚½Œ»‹à‚ª0‚Å‚Í‚È‚©‚Á‚½ê‡Às
			
			sum += cash->GetValue();
			
			if (_cashPrice <= sum) isMoneyInput = true;
		} while (!isMoneyInput);
	}

	if (_mode == ELECT_CASH) {
		if (_electronicPrice < _guest->GetElectronicMoney()->GetValue()) {
			//Server‚ÉƒAƒNƒZƒX‚µ‚Ä¬Œ÷‚µ‚½‚çŒ¸Z ¸”s‚È‚çÅ‰‚©‚ç‚â‚è’¼‚µ
			if (_server->Subtraction(_guest->GetElectronicMoney(), _electronicPrice)) {
				std::cout << "ƒT[ƒo[‚Æ‚Ì’ÊM‚ª¬Œ÷‚µ‚Ü‚µ‚½\n" << std::endl;
				std::cout << "“dqƒ}ƒl[‚©‚ç" << _electronicPrice << "‰~ˆø‚«‚Ü‚µ‚½\n" << std::endl;
			}
			else
			{
				std::cout << "ƒT[ƒo[‚Æ‚Ì’ÊM‚ª¸”s‚µ‚Ü‚µ‚½\n" << std::endl;
			}

			
			sum = _electronicPrice;
		}
		else {
			std::cout << "“dqƒ}ƒl[c‚‚ª‘«‚è‚Ü‚¹‚ñ\n" << std::endl;
		}
	}

	std::cout <<  sum << "‰~“Š“ü‚³‚ê‚½‚Ì‚Åæˆø‚ğÀs‚µ‚Ü‚·\n" << std::endl;

}

void TicketMachine::Draw(std::string letter)
{
	std::cout << letter << std::endl;
}

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
	int change = 0; //‚¨‚Â‚è‡Œv
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
	int remain = change;	//‚ ‚Ü‚è
	int changeSum = 0;		//‚¨‚Â‚è‚Ì‡Œv
	
	
	int numCoins = remain / 10000 ; //d‰İ‚Ì”
	for (int i = 0; i < numCoins; i++) _changList[6].push_back(new Cash10000En);
	remain %= 10000;
	
	numCoins = remain / 5000; //d‰İ‚Ì”
	for (int i = 0; i < numCoins; i++) _changList[5].push_back(new Cash5000En);
	remain %= 5000;
	
	numCoins = remain / 1000; //d‰İ‚Ì”
	for (int i = 0; i < numCoins; i++) _changList[4].push_back(new Cash1000En);
	remain %= 1000;
	
	numCoins = remain / 500; //d‰İ‚Ì”
	for (int i = 0; i < numCoins; i++) _changList[3].push_back(new Cash500En);
	remain %= 500;
	
	numCoins = remain / 100; //d‰İ‚Ì”
	for (int i = 0; i < numCoins; i++) _changList[2].push_back(new Cash100En);
	remain %= 100;
	
	numCoins = remain / 50; //d‰İ‚Ì”
	for (int i = 0; i < numCoins; i++) _changList[1].push_back(new Cash50En);
	remain %= 50;
	
	numCoins = remain / 10; //d‰İ‚Ì”
	for (int i = 0; i < numCoins; i++) _changList[0].push_back(new Cash10En);
	remain %= 10;
	
	for (int i = 0; i < 6; i++) {
		 changeSum += Total(&_changList[i]);
	}

	std::cout << "‚¨‚Â‚è‚Ì‹àí‚Æ‚»‚Ì”‚Í\n" << std::endl;
	std::cout << "10000‰~‚ª" << _changList[6].size() << "–‡\n" << std::endl;
	std::cout << "5000‰~‚ª" << _changList[5].size() << "–‡\n" << std::endl;
	std::cout << "1000‰~‚ª" << _changList[4].size() << "–‡\n" << std::endl;
	std::cout << "500‰~‚ª" << _changList[3].size() << "–‡\n" << std::endl;
	std::cout << "100‰~‚ª" << _changList[2].size() << "–‡\n" << std::endl;
	std::cout << "50‰~‚ª" << _changList[1].size() << "–‡\n" << std::endl;
	std::cout << "10‰~‚ª" << _changList[0].size() << "–‡\n" << std::endl;


	std::cout << "‚¨‚Â‚è‚Ì‡Œv‹àŠz‚Í" << changeSum << "‰~‚Å‚·\n" << std::endl;
}

void TicketMachine::Check()
{
	int sum = 0;

	if (_mode == 1) {

		std::cout << "“Š“ü‚³‚ê‚½‹àí‚Æ‚»‚Ì”‚Í\n" << std::endl;
		std::cout << "10‰~‹Ê‚ª" << _cashList[0].size() << "–‡\n" << std::endl;
		std::cout << "50‰~‹Ê‚ª" << _cashList[1].size() << "–‡\n" << std::endl;
		std::cout << "100‰~‹Ê‚ª" << _cashList[2].size() << "–‡\n" << std::endl;
		std::cout << "500‰~‹Ê‚ª" << _cashList[3].size() << "–‡\n" << std::endl;
		std::cout << "1000‰~‹Ê‚ª" << _cashList[4].size() << "–‡\n" << std::endl;
		std::cout << "5000‰~‹Ê‚ª" << _cashList[5].size() << "–‡\n" << std::endl;
		std::cout << "10000‰~‹Ê‚ª" << _cashList[6].size() << "–‡\n" << std::endl;

		for (int i = 0; i < 6; i++)
			for (auto it : _cashList[i])
				sum += it->GetValue();

		std::cout << "“Š“ü‚³‚ê‚½‹àŠz‚Ì‡Œv‚Í" << sum << "‰~‚Å‚·\n" << std::endl;
	}

	if (_mode == 2) {
		_server->Check(_guest->GetElectronicMoney());
	}
}
