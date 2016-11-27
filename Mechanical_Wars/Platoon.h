#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

class Unit;

class Platoon : public Calculation
{
public:

	void update();
	void draw() const;
	int getRank(Unit* unit);
	Vec2 getPosition(Unit* leader);
	bool joinPlatoon(Unit* member);
	Unit* getLeaderInfo();
	Vec2 getAngle();
	int getIFF();
	void setLeaderUnit(Unit* leader);


	Platoon();
	~Platoon();

private:
	bool Enabled;
	Unit* MemberUnits[5];
	Unit* LeaderUnit;

};