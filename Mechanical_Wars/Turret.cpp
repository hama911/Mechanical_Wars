#include"Turret.h"
#include"Bullet.h"
#include"Graphics.h"

extern Array<Unit> units;
extern Array<Bullet> bullets;

bool Turret::update()
{
	bool flag = false;


	return flag;
}

void Turret::draw() const
{
}


Turret::Turret()
{
	Position = Vec2(0, 0);
	Angle = Vec2(1, 0);
	TargetAngle = Vec2(1, 0);
	Range = 100.0;
	ReloadCount = 0;
	ReloadTime = 10;
}

Turret::~Turret()
{
}
