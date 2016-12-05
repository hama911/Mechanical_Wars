#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

/*
�����ɑ΂��C�����w�肷��

*/

class Platoon;

class Mission : public Calculation
{
public:
	Mission() { Enabled = false; }


	bool set(Vec2 position, int iff, Platoon* platoon = NULL, int priority = 1);
	void update();
	void draw() const;
	bool getBattleFlag();	//�퓬����
	void setBAL();

public:

	int BAL;		//�퓬�n�惌�x��
	bool Enabled;
	Vec2 Position;	//�~�b�V�����̈ʒu
	Vec2 Angle;		//�~�b�V�����̌�������
	int IFF;		//�������Ă���IFF(-�Ŗ�����������)
	Mission* Connects[10];	//�ڑ����Ă���~�b�V����(10�܂Ŏw��\)
	Platoon* Prosecutor;	//�C���𐿂���������
	int Priority;	//�D��x
private:

};