#pragma once
#include<Siv3D.hpp>
class Unit;
class Mission;

#define ERROR
#define DIVISION_MAX_MEMBER 12

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

	void leaveDivision(Unit* unit);

	void rushEnemyMission();

	Mission* getFriendlyMission(bool Right) const;

	void receiveSupply(Unit* unit);

	double getUnitInterval() const;


	bool set(int iff);

	int getNumSupplyUnit() const;
	int getNumMemberUnit() const;
	void relocate();

	void update();
	void draw() const;

	void reset();

protected:
	Vec2 getPosition() const;

public:
	bool Enabled;
	Mission* TargetMission = NULL;
	Unit* MemberUnits[DIVISION_MAX_MEMBER];
	Mission* InProcessMission;
	int IFF;
};