#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"

extern Array<Bullet> bullets;
extern Array<Unit> units;

void Unit::update()
{
	if (Enabled)
	{
		for (auto& turret : turrets)
			turret.setBaseUnit(this);

		moveForward(SpeedPerformance);

		if (RandomBool(0.01)) TargetAngle.rotate(Random(TwoPi));

		turnUpdate();

		limitMoving();

		if (Health < 0) Enabled = false;

		//ターレット制御
		for (auto& turret : turrets)
			turret.update();

	}
}

void Unit::draw() const
{
	if (Enabled)
	{

		//本体
		switch (Type)
		{
		case 0:
			Rect(ConvertVec2ToPoint(Position - Vec2(15.0, 7.5)), Point(30 * getZoom(), 15 * getZoom())).rotated(Circular3(Angle).theta).draw(HSV(IFF));
			break;
		case 1:
			Rect(ConvertVec2ToPoint(Position - Vec2(30.0, 15)), Point(60 * getZoom(), 30 * getZoom())).rotated(Circular3(Angle).theta).draw(HSV(IFF, 1, 0.9));
			Rect(ConvertVec2ToPoint(Position - Vec2(20.0, 10)), Point(40 * getZoom(), 20 * getZoom())).rotated(Circular3(Angle).theta).draw(HSV(IFF));
			break;
		default:
			break;
		}
		//耐久ゲージ
		Line(ConvertVec2ToVec2(Position - Vec2(10, 20)), ConvertVec2ToVec2(Position - Vec2(-10, 20))).draw(3 * getZoom(), Palette::Red);
		Line(ConvertVec2ToVec2(Position - Vec2(10, 20)), ConvertVec2ToVec2(Position - Vec2(10 - Health, 20))).draw(3 * getZoom(), Palette::Green);

		//ターレット描画
		for (auto& turret : turrets)
			turret.draw();
	}
}

void Unit::addDamege(double value)
{
	Health -= value;
}

Vec2 Unit::getPosition() const
{
	return Position;
}

Vec2 Unit::getAngle() const
{
	return Angle;
}

int Unit::getIFF() const
{
	return IFF;
}

bool Unit::getEnabled() const
{
	return Enabled;
}

double Unit::getSpeedPerformance() const
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
	{
		Angle.rotate(-TurningPerformance);
		for (auto& turret : turrets) turret.addRotate(-TurningPerformance);
	}
	else
	{
		Angle.rotate(TurningPerformance);
		for (auto& turret : turrets) turret.addRotate(TurningPerformance);
	}
}

void Unit::shot()
{
}

Unit::Unit(int IFF_p, int type)	//ランダムに位置を設定
{
	Enabled = true;
	IFF = IFF_p;
	Heat = Random(20);
	Position.x = Random(0.0, 640.0);
	Position.y = Random(0.0, 480.0);
	Angle = { 1.0,0.0 };
	TargetAngle = { 1.0,0.0 };
	Angle.rotate(Random(TwoPi));
	Health = 20.0;
	Type = type;


	switch (type)
	{
	case 0:
		SpeedPerformance = 2;
		TurningPerformance = 0.03;
		//砲塔設定
		turrets[0].setEnable(true);
		turrets[0].setAngle(Angle);
		break;
	case 1:
		SpeedPerformance = 0.5;
		TurningPerformance = 0.01;
		//砲塔設定
		turrets[0].setEnable(true);
		turrets[0].setAngle(Angle);
		turrets[0].setLocalPosition(Vec2(0, 0));
		turrets[0].setType(1);
		turrets[1].setEnable(true);
		turrets[1].setAngle(Angle);
		turrets[1].setLocalPosition(Vec2(16, 8));
		turrets[2].setEnable(true);
		turrets[2].setAngle(Angle);
		turrets[2].setLocalPosition(Vec2(-16, -8));
		turrets[3].setEnable(true);
		turrets[3].setAngle(Angle);
		turrets[3].setLocalPosition(Vec2(-16, 8));
		turrets[4].setEnable(true);
		turrets[4].setAngle(Angle);
		turrets[4].setLocalPosition(Vec2(16, -8));
		break;
	default:
		break;
	}
}

Unit::~Unit()
{
}
