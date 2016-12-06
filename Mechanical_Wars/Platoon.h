#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

class Unit;
class Mission;

#define MAX_MEMBER 6

/*
規則
LeaderUnitは0番に割り当て
SupplyUnitは1番に割り当て
使用時にはreset()をかけてから使うこと
解放時はreset()をかけること

*/

class Platoon : public Calculation
{
public:

	void update();
	void draw() const;

	double getJoinDistance(Unit* unit);	//もし取得できない状況の場合は10000を返す
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
	Vec2 TargetPosition;	//目標地点
	Vec2 TargetAngle;		//目標方向

};