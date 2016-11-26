#pragma once

#include<Siv3D.hpp>

class Unit;

class Turret
{
public:

	void update(Vec2 position, Vec2 angle);
	void draw(Vec2 position, Vec2 angle) const;

	Turret();
	~Turret();

	//内部データにアクセス
	Vec2 getGlobalPosition();
	Vec2 getTargetAngle();
	int getIFF();
	int getType();
	Vec2 getRealPosition();

	void setIFF(int value);
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
	Vec2 GlobalPosition;
	Vec2 BodyAngle;
	Vec2 GlobalAngle;
	Vec2 TargetAngle;
	int ReloadCount;
	int Status;

	double TurningPerformance;
	double Range;
	int ReloadTime;
	int IFF;
	int Type;
};
