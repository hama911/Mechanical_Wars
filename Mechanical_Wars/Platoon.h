#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

class Unit;

#define MAX_MEMBER 5

class Platoon : public Calculation
{
public:

	void update();
	void draw() const;


	int getRank(Unit* unit);
	Vec2 getUnitTargetAngle(Unit* unit);
	Vec2 getUnitTargetPosition(Unit* unit);
	double getUnitSpeed(Unit* unit);
	Unit* getLeaderInfo();
	Vec2 getAngle();
	int getTotalMember();
	int getIFF();
	void setTargetPosition(Vec2 position) { TargetPosition = position; }

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

	Vec2 TargetPosition;	//目標地点
	Vec2 TargetAngle;		//目標方向

};