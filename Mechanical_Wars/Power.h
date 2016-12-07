#pragma once
#include<Siv3D.hpp>


//�p���[���Ǘ�����V�X�e���B
//�P��IFF�ɑ΂��P�̃p���[���p�ӂ����
class Power
{
public:
	Power(int iff) { IFF = iff; Enabled = false; }
	void update();
	void draw() const;
	void FindFreeMission();
	void FindNeedUnits();
public:
	bool FreeMission;
	int NumberOfBAL[5];
	int NumberOfPlatoonBAL[5];
	int NeedUnits[3];
	int IFF;
	bool Enabled = true;
};