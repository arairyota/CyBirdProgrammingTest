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
		Draw("��������Ⴂ�܂�\n");
		
	} while (guest == nullptr);

	_guest = guest;
}

void TicketMachine::SelectMode()
{
	_mode = 0;
	while (!(_mode >= CASH && _mode <= ELECT_CASH)) {
		_mode = 0;
		std::cout << "�����ł̍w���̏ꍇ��1\n�d�q�}�l�[�ł̍w���̏ꍇ��2����͂��Ă�������\n";
		scanf("%d", &_mode);

	}  //1��2���I�������܂ŌJ��Ԃ�


	
}

//���K�v��
void TicketMachine::MonetaryDemand()
{
	int sum = 0; //�������ꂽ���v���z
	int total = 0;
	bool isMoneyInput = false;

	Draw("�����𓊓����Ă�������\n");

	if (_mode == CASH) {
		do {
			std::cout << "���݂̓������z��" << sum << "�~�ł�\n" << std::endl;
			Draw("10�~�ʂ�����ꍇ��0\n");
			Draw("50�~�ʂ�����ꍇ��1\n");
			Draw("100�~�ʂ�����ꍇ��2\n");
			Draw("500�~�ʂ�����ꍇ��3\n");
			Draw("1000�~�ʂ�����ꍇ��4\n");
			Draw("5000�~�ʂ�����ꍇ��5\n");
			Draw("10000�~�ʂ�����ꍇ��6\n");
			int inputNumber;
			scanf("%d", &inputNumber);

			Cash* cash = _guest->CashTake(inputNumber);
			if (cash != nullptr) _cashList[inputNumber].push_back(cash); //�I������������0�ł͂Ȃ������ꍇ���s
			
			sum += cash->GetValue();
			
			if (_cashPrice <= sum) isMoneyInput = true;
		} while (!isMoneyInput);
	}

	if (_mode == ELECT_CASH) {
		if (_electronicPrice < _guest->GetElectronicMoney()->GetValue()) {
			//Server�ɃA�N�Z�X���Đ��������猸�Z ���s�Ȃ�ŏ������蒼��
			if (_server->Subtraction(_guest->GetElectronicMoney(), _electronicPrice)) {
				std::cout << "�T�[�o�[�Ƃ̒ʐM���������܂���\n" << std::endl;
				std::cout << "�d�q�}�l�[����" << _electronicPrice << "�~�����܂���\n" << std::endl;
			}
			else
			{
				std::cout << "�T�[�o�[�Ƃ̒ʐM�����s���܂���\n" << std::endl;
			}

			
			sum = _electronicPrice;
		}
		else {
			std::cout << "�d�q�}�l�[�c��������܂���\n" << std::endl;
		}
	}

	std::cout <<  sum << "�~�������ꂽ�̂Ŏ�������s���܂�\n" << std::endl;

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
	int change = 0; //���荇�v
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
	int remain = change;	//���܂�
	int changeSum = 0;		//����̍��v
	
	
	int numCoins = remain / 10000 ; //�d�݂̐�
	for (int i = 0; i < numCoins; i++) _changList[6].push_back(new Cash10000En);
	remain %= 10000;
	
	numCoins = remain / 5000; //�d�݂̐�
	for (int i = 0; i < numCoins; i++) _changList[5].push_back(new Cash5000En);
	remain %= 5000;
	
	numCoins = remain / 1000; //�d�݂̐�
	for (int i = 0; i < numCoins; i++) _changList[4].push_back(new Cash1000En);
	remain %= 1000;
	
	numCoins = remain / 500; //�d�݂̐�
	for (int i = 0; i < numCoins; i++) _changList[3].push_back(new Cash500En);
	remain %= 500;
	
	numCoins = remain / 100; //�d�݂̐�
	for (int i = 0; i < numCoins; i++) _changList[2].push_back(new Cash100En);
	remain %= 100;
	
	numCoins = remain / 50; //�d�݂̐�
	for (int i = 0; i < numCoins; i++) _changList[1].push_back(new Cash50En);
	remain %= 50;
	
	numCoins = remain / 10; //�d�݂̐�
	for (int i = 0; i < numCoins; i++) _changList[0].push_back(new Cash10En);
	remain %= 10;
	
	for (int i = 0; i < 6; i++) {
		 changeSum += Total(&_changList[i]);
	}

	std::cout << "����̋���Ƃ��̐���\n" << std::endl;
	std::cout << "10000�~��" << _changList[6].size() << "��\n" << std::endl;
	std::cout << "5000�~��" << _changList[5].size() << "��\n" << std::endl;
	std::cout << "1000�~��" << _changList[4].size() << "��\n" << std::endl;
	std::cout << "500�~��" << _changList[3].size() << "��\n" << std::endl;
	std::cout << "100�~��" << _changList[2].size() << "��\n" << std::endl;
	std::cout << "50�~��" << _changList[1].size() << "��\n" << std::endl;
	std::cout << "10�~��" << _changList[0].size() << "��\n" << std::endl;


	std::cout << "����̍��v���z��" << changeSum << "�~�ł�\n" << std::endl;
}

void TicketMachine::Check()
{
	int sum = 0;

	if (_mode == 1) {

		std::cout << "�������ꂽ����Ƃ��̐���\n" << std::endl;
		std::cout << "10�~�ʂ�" << _cashList[0].size() << "��\n" << std::endl;
		std::cout << "50�~�ʂ�" << _cashList[1].size() << "��\n" << std::endl;
		std::cout << "100�~�ʂ�" << _cashList[2].size() << "��\n" << std::endl;
		std::cout << "500�~�ʂ�" << _cashList[3].size() << "��\n" << std::endl;
		std::cout << "1000�~�ʂ�" << _cashList[4].size() << "��\n" << std::endl;
		std::cout << "5000�~�ʂ�" << _cashList[5].size() << "��\n" << std::endl;
		std::cout << "10000�~�ʂ�" << _cashList[6].size() << "��\n" << std::endl;

		for (int i = 0; i < 6; i++)
			for (auto it : _cashList[i])
				sum += it->GetValue();

		std::cout << "�������ꂽ���z�̍��v��" << sum << "�~�ł�\n" << std::endl;
	}

	if (_mode == 2) {
		_server->Check(_guest->GetElectronicMoney());
	}
}
