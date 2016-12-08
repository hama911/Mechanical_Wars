#pragma once
#include<Siv3D.hpp>

class Unit;
class Mission;

#define ERROR
#define DIVISION_MAX_MEMBER 10

class Division
{
public:
	Division() { Enabled = false; }

	//NULL‚ÅŽt’cŽ©‘Ì‚Ì‚à‚Ì‚ð•\‚·

	Vec2 getTargetPosition(Unit* unit = NULL) const;
	Vec2 getTargetAngle() const;
	Unit* getLeader() const;

	void findMission();
	
	double getJoinPriority(Unit* unit) const;
	void JoinDivision(Unit* unit);
	bool canJoinDivision(Unit* unit) const;

	double getUnitInterval() const;
	

	bool set(int iff);

	int getNumSupplyUnit() const;
	int getNumMemberUnit() const;
	void relocate();

	void update();
	void draw() const;

protected:
	Vec2 getPosition() const;

public:
	bool Enabled;
	Unit* MemberUnits[DIVISION_MAX_MEMBER];
	Mission* InProcessMission;
	int IFF;
};