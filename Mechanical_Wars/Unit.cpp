#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"
#include"Motion.h"
#include"Platoon.h"

extern Array<Bullet> bullets;
extern Array<Unit> units;
extern Array<Motion> motions;
extern Array<Platoon> platoons;

void Unit::update()
{
	if (Enabled)
	{
		updatePlatoon();
		for (auto& turret : turrets)
			turret.setBaseUnit(this);

		turnUpdate();

		limitMoving();

		if (Health < 0)
		{
			for (auto& motion : motions)
				if (motion.setFromUnit(this)) break;
			reset();
		}
		//ターレット制御
		for (auto& turret : turrets)
			turret.update();

	}
}
void Unit::reset()
{
	Enabled = false;
	Position = Vec2(0.0, 0.0);
	Angle = Vec2(1, 0);
	TargetAngle = Vec2(1.0, 0.0);
	IFF = 0;
	Health = 0.0;
	MyPlatoon = NULL;
	SpeedPerformance = 0.0;
	TurningPerformance = 0.0;
	HealthPerformance = 0.0;
	Type = 0;
	Speed = 0;
	for (auto& turret : turrets)
		turret.setEnable(false);
}
void Unit::updatePlatoon()
{
	Speed = 0;
	if (MyPlatoon == NULL)
	{

		Speed = SpeedPerformance;
		if (RandomBool(0.001)) TargetAngle.rotate(Random(TwoPi));

		for (auto& platoon : platoons)
		{
			if (platoon.joinPlatoon(this)) {
				break;
			}
		}
	}
	else
	{
		//ターゲットアングルの変更
		if (MyPlatoon->getRank(this) == 0)
		{
			TargetAngle = (MyPlatoon->getPosition(this) - Position).normalized();
			if (abs(TargetAngle.cross(Angle)) < 0.8 && TargetAngle.dot(Angle) > 0)
			{
				if ((MyPlatoon->getPosition(this) - Position).length() > 10)
				{
					Speed = SpeedPerformance;
				}
				else
				{
					Speed = SpeedPerformance / 2;
				}
			}
		}
		else
		{
			Speed = SpeedPerformance / 2;
			if (RandomBool(0.001)) TargetAngle.rotate(Random(TwoPi));
		}
		//より多いところに加入
		if (MyPlatoon->getTotalMember() <= 2)
		{
			for (auto& platoon : platoons)
			{
				if (&platoon != MyPlatoon&&platoon.getIFF() == IFF && platoon.getTotalMember() + MyPlatoon->getTotalMember() <= 5 && platoon.getTotalMember() >= MyPlatoon->getTotalMember())
				{
					platoon.joinPlatoon(this);
				}
			}
		}
	}
	moveForward(Speed);

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

void Unit::setUnit(int IFF_p, int type, Vec2 position)
{
	IFF = IFF_p;
	Type = type;
	Position = position;
	MyPlatoon = NULL;
	Speed = 0;
	setUnitData();
}

int Unit::getMotionType() const
{
	switch (Type)
	{
	case 0:
		return 2;
		break;
	case 1:
		return 3;
		break;
	default:
		break;
	}
	return 0;
}