#pragma once

#include<Siv3D.hpp>
#include"Calculation.h"

class Unit;

class Turret : public Calculation
{
public:

	void update();
	void draw() const;

	Turret();
	~Turret();

	//内部データにアクセス
	Vec2 getGlobalPosition() const;
	Vec2 getTargetAngle() const;
	int getType() const;
	Unit* getBaseUnit() const;
	Vec2 getRealPosition() const;

	void setBaseUnit(Unit *unit);
	void setRange(double range);
	void setAngle(Vec2 angle);
	void setEnable(bool flag);
	void setLocalPosition(Vec2 position);
	void setType(int type);
	void addRotate(double angle);

private:

	void updateAngle();
	void shot();
	Unit* searchEnemyUnit();

	bool Enabled;
	Vec2 LocalPosition;
	Vec2 GlobalAngle;
	Vec2 TargetAngle;
	int ReloadCount;
	int Status;

	double TurningPerformance;
	double Range;
	int ReloadTime;
	Unit* BaseUnit;
	int Type;
};
