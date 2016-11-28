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
	Vec2 getPosition(Unit* leader);
	Unit* getLeaderInfo();
	Vec2 getAngle();
	int getTotalMember();
	int getIFF();

	void setLeaderUnit(Unit* leader);

	void relocation();
	void reset();
	bool joinPlatoon(Unit* member);

	Platoon();
	~Platoon();

private:
	bool Enabled;
	Unit* MemberUnits[MAX_MEMBER];
	Unit* LeaderUnit;

};