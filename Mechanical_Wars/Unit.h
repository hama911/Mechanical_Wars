#pragma once

# include <Siv3D.hpp>
#include"Turret.h"

#define MAX_TURRET 10

class Platoon;

class Unit : public Calculation
{
public:
	Unit() { Enabled = false; }


	void update();	//ϊ»
	void draw() const;	//`ζ

	void addDamege(double value);

	//ϊ»
	void mountTurret();

	void updatePlatoon();

	bool setUnit(int IFF_p, int type, Vec2 position = Vec2(Random(1024), Random(1024)));
	void reset();


	bool hitCheck(Vec2 pos);


public:	//ΰf[^ΙANZX
	int getMotionType() const;

	Vec2 getSpeedVec2() const;	//»έΜXs[hπVec2^ΕΤ·
	double getSpeedDouble() const;	//»έΜXs[hπdouble^ΕΤ·

public:
	//ΒΚf[^
	void updateUnit();
	void setUnitData();
	void drawUnit() const;



	//ρ]n
	void turnUpdate();	//px

	//Un
	void shot();

	//§ΐ
	void limitMoving();

public:
	//Ο
	bool Enabled;
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetPosition;
	int IFF;	//―ΚR[h
	double Health;	//Οv
	Unit* Target;	
	Platoon* MyPlatoon;

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
