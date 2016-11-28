#pragma once

#include<Siv3D.hpp>
#include"Calculation.h"

class Unit;

class Turret : public Calculation
{
public:

	void update();
	void draw() const;

	Turret() { Enabled = false; }

	void addRotate(double angle);
	void reset();
	void set(int type,double x,double y);

public:	//内部データにアクセス
	void setBaseUnit(Unit *unit) { BaseUnit = unit; }
	void setRange(double range) { Range = range; }
	void setAngle(Vec2 angle) { GlobalAngle = angle; }
	void setEnable(bool enabled) { Enabled = enabled; }

	void setLocalPosition(Vec2 position);

	
	Vec2 getTargetAngle() const { return TargetAngle; }
	int getType() const { return Type; }
	int getCount() const { return Count; }
	Unit* getBaseUnit() const { return BaseUnit; }

	Vec2 getRealPosition() const;


private:
	//個別データ
	void setTurretData();
	void drawTurret() const;

	void updateAngle();
	void shot();
	Unit* searchEnemyUnit();

	bool Enabled;
	Vec2 LocalPosition;
	Vec2 GlobalAngle;
	Vec2 TargetAngle;
	int ReloadCount;
	int Status;
	int Count;

	double BulletSpeed;
	double TurningPerformance;
	double Range;
	int ReloadTime;
	Unit* BaseUnit;
	int Type;
};
