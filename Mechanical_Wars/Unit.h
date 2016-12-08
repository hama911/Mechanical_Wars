#pragma once

# include <Siv3D.hpp>
#include"Turret.h"

#define MAX_TURRET 10

class Bullet;
class Division;

class Unit : public Calculation
{
public:
	Unit() { Enabled = false; }


	void update();	//ϊ»
	void draw() const;	//`ζ
	void addDamege(Bullet* bullet);
	void mountTurret();
	bool setUnit(int IFF_p, int type, Vec2 position = Vec2(Random(1024), Random(1024)));
	void reset();
	bool hitCheck(Vec2 pos);
	Vec2 getSpeedVec2();	//»έΜXs[hπVec2^ΕΤ·
	double getSpeedDouble();	//»έΜXs[hπdouble^ΕΤ·
	void setUnitData();
	void drawUnit() const;
	void turnUpdate();	//px
	void shot();
	void limitMoving();
	bool isSupplyUnit();

public:
	//Ο
	Division* AssignedDivision = NULL;
	bool Enabled;
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetPosition;
	int IFF;	//―ΚR[h
	double Health;	//Οv
	Unit* Target;
	//Εθl
	double SpeedPerformance;	//¬x«\
	double TurningPerformance;	//ωρ«\
	double HealthPerformance;	//Οv«\
	int Type;

	//β
	double Supply;	//βΚ
	double Fuel;	//RΏ
	double SupplyMax;
	double FuelMax;

	Turret turrets[MAX_TURRET];

};
