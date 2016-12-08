#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

class Division;

void updateMissions();

class Mission : public Calculation
{
public:
	Mission() { Enabled = false; }


	bool set(Vec2 position, int iff);
	void update();
	void draw() const;
	void setBAL();

	Vec2 getAngle() const;

public:

	int BAL;		//�퓬�n�惌�x��
	bool Enabled;
	Vec2 Position;	//�~�b�V�����̈ʒu
	int IFF;		//�������Ă���IFF(-�Ŗ�����������)
	Mission* Connects[10];	//�ڑ����Ă���~�b�V����(10�܂Ŏw��\)
	Division* ActiveDivision;
private:

};