#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"

extern Array<Bullet> bullets;
extern Array<Unit> units;

bool Unit::update()
{
	bool flag = false;
	moveForward(SpeedPerformance);

	if (RandomBool(0.01)) TargetAngle.rotate(Random(TwoPi));

	turnUpdate();

	limitMoving();

	if (Health < 0) flag = 1;
	return flag;
}

void Unit::draw() const
{
	//本体
	Rect(ConvertVec2ToPoint(Position - Vec2(15.0, 7.5)), Point(30 * getZoom(), 15 * getZoom())).rotated(Atan2(Angle.y, Angle.x)).draw(HSV(IFF));

	//耐久ゲージ
	Line(ConvertVec2ToVec2(Position - Vec2(10, 20)), ConvertVec2ToVec2(Position - Vec2(-10, 20))).draw(3 * getZoom(), Palette::Red);
	Line(ConvertVec2ToVec2(Position - Vec2(10, 20)), ConvertVec2ToVec2(Position - Vec2(10 - Health, 20))).draw(3 * getZoom(), Palette::Green);

}

void Unit::addDamege(double value)
{
	Health -= value;
}

Vec2 Unit::getPosition()
{
	return Position;
}

Vec2 Unit::getAngle()
{
	return Angle;
}

int Unit::getIFF()
{
	return IFF;
}

double Unit::getSpeedPerformance()
{
	return SpeedPerformance;
}

void Unit::limitMoving()
{
	if (Position.x < 0) Position.x = 0;
	if (Position.y < 0) Position.y = 0;
	if (Position.x > 1024) Position.x = 1024;
	if (Position.y > 1024) Position.y = 1024;
}

void Unit::mountTurret()
{
}

void Unit::moveForward(double length)
{
	Position.moveBy(Angle*length);
}
void Unit::moveBack(double length)
{
	Position.moveBy(-Angle*length);
}

void Unit::turnUpdate()
{
	if (TargetAngle.cross(Angle) > 0)
		Angle.rotate(-0.01);
	else
		Angle.rotate(0.01);
}

void Unit::shot()
{
}

Unit::Unit()	//ランダムに位置を設定
{
	IFF = Random(360);
	Heat = Random(20);
	SpeedPerformance = Random(1.0) + 0.5;
	Position.x = Random(0.0, 640.0);
	Position.y = Random(0.0, 480.0);
	Angle = { 1.0,0.0 };
	TargetAngle = { 1.0,0.0 };
	Angle.rotate(Random(TwoPi));
	Health = 20.0;
}
Unit::Unit(int IFF_p)	//ランダムに位置を設定
{
	IFF = IFF_p;
	Heat = Random(20);
	SpeedPerformance = Random(1.0) + 0.5;
	Position.x = Random(0.0, 640.0);
	Position.y = Random(0.0, 480.0);
	Angle = { 1.0,0.0 };
	TargetAngle = { 1.0,0.0 };
	Angle.rotate(Random(TwoPi));
	Health = 20.0;
}

Unit::~Unit()
{
}
