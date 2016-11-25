#pragma once

#include<Siv3D.hpp>

class Turret
{
public:

	bool update();
	void draw() const;

	Turret();
	~Turret();

	//�����f�[�^�ɃA�N�Z�X
	Vec2 getPosition();

private:



	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetAngle;
	double Range;

	int ReloadCount;
	int ReloadTime;
};
