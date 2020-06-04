#pragma once

#include <list>
#include <string>

//�O���錾
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

	void MonetaryDemand();	//���K�v��

	void Draw( std::string letter ); //�����ɓ��ꂽ���e��`��

	int Total(std::list<Cash*>* list);

	void Buy(); //�w������

	void Change(int change); //����v�Z����

	void Check();

private:
	const int _cashPrice = 130;			//�����ł̍w�����i
	const int _electronicPrice = 124;	//�d�q�}�l�[�̍w�����i

	Human* _guest;	//�q
	Server* _server;

	int _mode =0;

	std::list<Cash*> _cashList[7];
	std::list<Cash*> _changList[7]; //���胊�X�g
};

