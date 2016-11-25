#pragma once

#include<Siv3D.hpp>

class Turret
{
public:

	bool update();
	void draw() const;

	Turret();
	~Turret();

	//内部データにアクセス
	Vec2 getPosition();

private:



	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetAngle;
	double Range;

	int ReloadCount;
	int ReloadTime;
};
