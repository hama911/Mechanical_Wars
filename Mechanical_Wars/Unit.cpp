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
		drawUnit();

		//ターレット描画
		for (auto& turret : turrets)
			turret.draw();

		//耐久ゲージ
		Line(ConvertVec2ToVec2(Position - Vec2(HealthPerformance / 2, 20)), ConvertVec2ToVec2(Position - Vec2(-HealthPerformance / 2, 20))).draw(3 * getZoom(), Palette::Red);
		Line(ConvertVec2ToVec2(Position - Vec2(HealthPerformance / 2, 20)), ConvertVec2ToVec2(Position - Vec2(HealthPerformance / 2 - Health, 20))).draw(3 * getZoom(), Palette::Green);

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
	if (abs(TargetAngle.cross(Angle)) < Sin(TurningPerformance) && TargetAngle.dot(Angle) > 0)
		Angle = TargetAngle;
	else
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
}

void Unit::shot()
{
}

Unit::Unit(int IFF_p, int type)	//ランダムに位置を設定
{
	IFF = IFF_p;
	Type = type;
	setUnitData();
}

Unit::~Unit()
{
}
