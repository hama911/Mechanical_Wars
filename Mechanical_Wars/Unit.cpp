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
			motions.push_back(this);
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
	for (auto& turret : turrets)
		turret.setEnable(false);
}
void Unit::updatePlatoon()
{
	if (MyPlatoon == NULL)
	{

		moveForward(SpeedPerformance);
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
					moveForward(SpeedPerformance);
				}
			}
		}
		else
		{
			moveForward(SpeedPerformance / 2);
			if (RandomBool(0.001)) TargetAngle.rotate(Random(TwoPi));
		}
		//より多いところに加入
		if (MyPlatoon->getTotalMember() <= 2)
		{
			for (auto& platoon : platoons)
			{
				if (&platoon!=MyPlatoon&&platoon.getIFF() == IFF && platoon.getTotalMember() + MyPlatoon->getTotalMember() <= 5&& platoon.getTotalMember() >= MyPlatoon->getTotalMember())
				{
						platoon.joinPlatoon(this);
				}
			}
		}
	}

}
Platoon* Unit::getPlatoon()
{
	return MyPlatoon;
}

void Unit::setPlatoon(Platoon* platoon)
{
	MyPlatoon = platoon;
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

Unit::Unit(int IFF_p, int type, Vec2 position)	//ランダムに位置を設定
{

	IFF = IFF_p;
	Type = type;
	Position = position;
	MyPlatoon = NULL;
	setUnitData();
}
void Unit::setEnabled(bool enabled)
{
	Enabled = enabled;
}
void Unit::resetUnit(int IFF_p, int type, Vec2 position)	//ランダムに位置を設定
{
	IFF = IFF_p;
	Type = type;
	Position = position;
	MyPlatoon = NULL;
	setUnitData();
}

Unit::~Unit()
{
}

int Unit::getMotionType() const
{
	int return_ = 0;
	switch (Type)
	{
	case 0:
		return_ = 3;
		break;
	case 1:
		return_ = 4;
		break;
	default:
		break;
	}
	return return_;
}