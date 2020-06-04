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
		Draw("Ç¢ÇÁÇ¡ÇµÇ·Ç¢Ç‹Çπ\n");
		
	} while (guest == nullptr);

	_guest = guest;
}

void TicketMachine::SelectMode()
{
	_mode = 0;

	while (!(_mode >= CASH && _mode <= ELECT_CASH)) {
		_mode = 0;
		std::cout << "åªã‡Ç≈ÇÃçwì¸ÇÃèÍçáÇÕ1\nìdéqÉ}ÉlÅ[Ç≈ÇÃçwì¸ÇÃèÍçáÇÕ2Çì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢\n";
		scanf("%d", &_mode);

	}  //1Ç©2Ç™ëIëÇ≥ÇÍÇÈÇ‹Ç≈åJÇËï‘Ç∑
}

//ã‡ëKóvãÅ
void TicketMachine::MonetaryDemand()
{
	int sum = 0; //ìäì¸Ç≥ÇÍÇΩçáåvã‡äz

	Draw("Ç®ã‡Çìäì¸ÇµÇƒÇ≠ÇæÇ≥Ç¢\n");

	//ëIëÉ}ÉiÅ[ï•Ç¢Ç™ëIëÇ≥ÇÍÇΩÇÁ
	if (_mode == CASH) {
		do {
			std::cout << "åªç›ÇÃìäì¸ã‡äzÇÕ" << sum << "â~Ç≈Ç∑\n" << std::endl;
			Draw("10â~ã Çì¸ÇÍÇÈèÍçáÇÕ0\n");
			Draw("50â~ã Çì¸ÇÍÇÈèÍçáÇÕ1\n");
			Draw("100â~ã Çì¸ÇÍÇÈèÍçáÇÕ2\n");
			Draw("500â~ã Çì¸ÇÍÇÈèÍçáÇÕ3\n");
			Draw("1000â~ã Çì¸ÇÍÇÈèÍçáÇÕ4\n");
			Draw("5000â~ã Çì¸ÇÍÇÈèÍçáÇÕ5\n");
			Draw("10000â~ã Çì¸ÇÍÇÈèÍçáÇÕ6\n");
			int inputNumber; //ã‡éÌëIëópïœêî
			scanf("%d", &inputNumber);

			Cash* cash = _guest->CashTake(inputNumber);
			if (cash != nullptr) _cashList[inputNumber].push_back(cash); //ëIëÇµÇΩåªã‡Ç™0Ç≈ÇÕÇ»Ç©Ç¡ÇΩèÍçáé¿çs
			
			sum += cash->GetValue();

		} while (!(_cashPrice <= sum)); //É`ÉPÉbÉgÇÃã‡äzÇ…ñûÇΩÇπÇΩÇÁ
	}

	//ìdéqÉ}ÉlÅ[ï•Ç¢Ç™ëIëÇ≥ÇÍÇΩÇÁ
	if (_mode == ELECT_CASH) {
		if (_electronicPrice < _guest->GetElectronicMoney()->GetValue()) {
			//ServerÇ…ÉAÉNÉZÉXÇµÇƒê¨å˜ÇµÇΩÇÁå∏éZ é∏îsÇ»ÇÁç≈èâÇ©ÇÁÇ‚ÇËíºÇµ
			if (_server->Subtraction(_guest->GetElectronicMoney(), _electronicPrice)) {
				std::cout << "ÉTÅ[ÉoÅ[Ç∆ÇÃí êMÇ™ê¨å˜ÇµÇ‹ÇµÇΩ\n" << std::endl;
				std::cout << "ìdéqÉ}ÉlÅ[Ç©ÇÁ" << _electronicPrice << "â~à¯Ç´Ç‹ÇµÇΩ\n" << std::endl;
			}
			else
			{
				std::cout << "ÉTÅ[ÉoÅ[Ç∆ÇÃí êMÇ™é∏îsÇµÇ‹ÇµÇΩ\n" << std::endl;
			}

			
			sum = _electronicPrice;
		}
		else {
			std::cout << "ìdéqÉ}ÉlÅ[écçÇÇ™ë´ÇËÇ‹ÇπÇÒ\n" << std::endl;
		}
	}

	std::cout <<  sum << "â~ìäì¸Ç≥ÇÍÇΩÇÃÇ≈éÊà¯Çé¿çsÇµÇ‹Ç∑\n" << std::endl;

}

void TicketMachine::Draw(std::string letter)
{
	std::cout << letter << std::endl;
}

//çáåvä÷êî
//à¯êî(çáåvÇèoÇµÇΩÇ¢CashÉNÉâÉXÇÃÉäÉXÉgÇÃÉAÉhÉåÉX)
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
	int change = 0; //Ç®Ç¬ÇËçáåv
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
	int remain = change;	//Ç†Ç‹ÇË
	int changeSum = 0;		//Ç®Ç¬ÇËÇÃçáåv
	
	
	int numCoins = remain / 10000 ; //çdâ›ÇÃêî
	for (int i = 0; i < numCoins; i++) _changList[6].push_back(new Cash10000En);
	remain %= 10000;
	
	numCoins = remain / 5000; //çdâ›ÇÃêî
	for (int i = 0; i < numCoins; i++) _changList[5].push_back(new Cash5000En);
	remain %= 5000;
	
	numCoins = remain / 1000; //çdâ›ÇÃêî
	for (int i = 0; i < numCoins; i++) _changList[4].push_back(new Cash1000En);
	remain %= 1000;
	
	numCoins = remain / 500; //çdâ›ÇÃêî
	for (int i = 0; i < numCoins; i++) _changList[3].push_back(new Cash500En);
	remain %= 500;
	
	numCoins = remain / 100; //çdâ›ÇÃêî
	for (int i = 0; i < numCoins; i++) _changList[2].push_back(new Cash100En);
	remain %= 100;
	
	numCoins = remain / 50; //çdâ›ÇÃêî
	for (int i = 0; i < numCoins; i++) _changList[1].push_back(new Cash50En);
	remain %= 50;
	
	numCoins = remain / 10; //çdâ›ÇÃêî
	for (int i = 0; i < numCoins; i++) _changList[0].push_back(new Cash10En);
	remain %= 10;
	
	for (int i = 0; i < 6; i++) {
		 changeSum += Total(&_changList[i]);
	}

	std::cout << "Ç®Ç¬ÇËÇÃã‡éÌÇ∆ÇªÇÃêîÇÕ\n" << std::endl;
	std::cout << "10000â~Ç™" << _changList[6].size() << "ñá\n" << std::endl;
	std::cout << "5000â~Ç™" << _changList[5].size() << "ñá\n" << std::endl;
	std::cout << "1000â~Ç™" << _changList[4].size() << "ñá\n" << std::endl;
	std::cout << "500â~Ç™" << _changList[3].size() << "ñá\n" << std::endl;
	std::cout << "100â~Ç™" << _changList[2].size() << "ñá\n" << std::endl;
	std::cout << "50â~Ç™" << _changList[1].size() << "ñá\n" << std::endl;
	std::cout << "10â~Ç™" << _changList[0].size() << "ñá\n" << std::endl;


	std::cout << "Ç®Ç¬ÇËÇÃçáåvã‡äzÇÕ" << changeSum << "â~Ç≈Ç∑\n" << std::endl;
}

void TicketMachine::Check()
{
	int sum = 0;

	if (_mode == 1) {

		std::cout << "ìäì¸Ç≥ÇÍÇΩã‡éÌÇ∆ÇªÇÃêîÇÕ\n" << std::endl;
		std::cout << "10â~ã Ç™" << _cashList[0].size() << "ñá\n" << std::endl;
		std::cout << "50â~ã Ç™" << _cashList[1].size() << "ñá\n" << std::endl;
		std::cout << "100â~ã Ç™" << _cashList[2].size() << "ñá\n" << std::endl;
		std::cout << "500â~ã Ç™" << _cashList[3].size() << "ñá\n" << std::endl;
		std::cout << "1000â~ã Ç™" << _cashList[4].size() << "ñá\n" << std::endl;
		std::cout << "5000â~ã Ç™" << _cashList[5].size() << "ñá\n" << std::endl;
		std::cout << "10000â~ã Ç™" << _cashList[6].size() << "ñá\n" << std::endl;

		for (int i = 0; i < 6; i++)
			for (auto it : _cashList[i])
				sum += it->GetValue();

		std::cout << "ìäì¸Ç≥ÇÍÇΩã‡äzÇÃçáåvÇÕ" << sum << "â~Ç≈Ç∑\n" << std::endl;
	}

	if (_mode == 2) {
		_server->Check(_guest->GetElectronicMoney());
	}
}
