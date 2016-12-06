#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

class Unit;
class Mission;

#define MAX_MEMBER 6

/*
�K��
LeaderUnit��0�ԂɊ��蓖��
SupplyUnit��1�ԂɊ��蓖��
�g�p���ɂ�reset()�������Ă���g������
�������reset()�������邱��

*/

class Platoon : public Calculation
{
public:

	void update();
	void draw() const;

	double getJoinDistance(Unit* unit);	//�����擾�ł��Ȃ��󋵂̏ꍇ��10000��Ԃ�
	Vec2 getUnitTargetPosition(Unit* unit);
	int getTotalMember();

	void setFromUnit(Unit* leader);
	void reset();
	bool joinPlatoon(Unit* member);
	void searchNewMission(void);

	Platoon() { reset(); }

public:
	Mission* RunningMission;
	bool Enabled;
	Unit* MemberUnits[MAX_MEMBER];
	Unit* LeaderUnit;
	Unit* SupplyUnit;
	Vec2 TargetPosition;	//�ڕW�n�_
	Vec2 TargetAngle;		//�ڕW����

};