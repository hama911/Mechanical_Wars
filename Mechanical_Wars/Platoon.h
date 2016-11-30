#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

class Unit;

#define MAX_MEMBER 6

class Platoon : public Calculation
{
public:

	void update();
	void draw() const;

	double getJoinDistance(Unit* unit);	//�����擾�ł��Ȃ��󋵂̏ꍇ��10000��Ԃ�
	int getRank(Unit* unit);
	Vec2 getUnitTargetAngle(Unit* unit);
	Vec2 getUnitTargetPosition(Unit* unit);
	double getUnitSpeed(Unit* unit);
	Unit* getLeaderInfo();
	Vec2 getAngle();
	int getTotalMember();
	int getIFF();
	void setTargetPosition(Vec2 position) { TargetPosition = position; }
	void setTargetAngle(Vec2 angle) { TargetAngle = angle; }
	Vec2 getTargetPosition() const { return TargetPosition; }

	bool getEnabled() const { return Enabled; }

	void setFromUnit(Unit* leader);


	void relocation();
	void reset();
	bool joinPlatoon(Unit* member);

	Platoon();
	~Platoon();

private:
	bool Enabled;
	Unit* MemberUnits[MAX_MEMBER];
	Unit* LeaderUnit;
	Unit* SupplyUnit;
	Vec2 TargetPosition;	//�ڕW�n�_
	Vec2 TargetAngle;		//�ڕW����

};