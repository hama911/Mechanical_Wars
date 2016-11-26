#include"Bullet.h"
#include"Unit.h"
#include"Motion.h"
#include"Graphics.h"

extern Array<Unit> units;
extern Array<Motion> motions;

void Bullet::update()
{
	if (Enabled)
	{
		++Count;
		Position.moveBy(Angle*SpeedPerformance);
		if (Random(Count) > 100)
		{
			Enabled = false;
			motions.push_back(Motion(this));
		}

		if (hitCheck())
		{
			Enabled = false;
			motions.push_back(Motion(this));
		}

	}
}

Unit* Bullet::hitCheck()
{
	Unit* target = NULL;
	for (auto& unit : units)
	{
		if (unit.getEnabled() && IFF != unit.getIFF() && Position.distanceFrom(unit.getPosition()) < 5)
		{
			target = &unit;
			switch (Type)
			{
			case 0:
				unit.addDamege(0.1);
				break;
			case 1:
				unit.addDamege(0.5);
				break;
			default:
				break;
			}
		}
	}
	return target;
}

void Bullet::draw() const
{
	if (Enabled)
	{
		switch (Type)
		{
		case 0:
			Circle(ConvertVec2ToVec2(Position), 2 * getZoom()).draw(HSV(IFF, 1, 1));
			break;
		case 1:
			Circle(ConvertVec2ToVec2(Position), 5 * getZoom()).draw(HSV(IFF, 1, 1));
			break;
		default:
			break;
		}
	}
}


Bullet::Bullet(Turret* turret)
{
	Count = 0;
	Enabled = true;
	IFF = turret->getBaseUnit()->getIFF();
	Position = turret->getRealPosition();
	Angle = turret->getTargetAngle();
	Type = turret->getType();
	SpeedPerformance = 5.0;

	//追跡システム
	//serchEnemyUnit();

}
Vec2 Bullet::getPosition() const
{
	return Position;
}

int Bullet::getType() const
{
	return Type;
}

bool Bullet::getEnabled() const
{
	return Enabled;
}

Unit* Bullet::serchEnemyUnit()
{

	double length = 300.0;	//索敵可能距離
	Unit* target = NULL;	//ターゲット
	for (auto& unit : units)
	{
		if (unit.getEnabled() && IFF != unit.getIFF() && Position.distanceFrom(unit.getPosition()) < length)
		{
			length = Position.distanceFrom(unit.getPosition());
			target = &unit;
		}
	}
	if (target != NULL)
	{
		Angle = (target->getPosition() + target->getAngle()*target->getSpeedPerformance()*((target->getPosition().distanceFrom(Position) / (Angle*SpeedPerformance - target->getAngle()*target->getSpeedPerformance()).length())) - Position).normalized();

	}
	return target;
}

Bullet::~Bullet()
{
}