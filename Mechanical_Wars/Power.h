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
	void FindNeedUnits();
public:
	bool FreeMission;
	int NeedUnits[3];
	int IFF;
	bool Enabled = true;
};