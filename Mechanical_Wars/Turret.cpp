#include"Turret.h"
#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"

extern Array<Unit> units;
extern Array<Bullet> bullets;

void Turret::update()
{
	if (Enabled)
	{
		if (Status == 1)
			updateAngle();
		shot();
	}
}

void Turret::draw() const
{

	if (Enabled)
	{
		switch (Type)
		{
		case 0:
			Circle(ConvertVec2ToVec2(getRealPosition()), 5 * getZoom()).draw(HSV(BaseUnit->getIFF(), 1, 0.5));
			Line(ConvertVec2ToVec2(getRealPosition()), ConvertVec2ToVec2(getRealPosition()) + GlobalAngle * 10 * getZoom()).draw(2 * getZoom(), HSV(BaseUnit->getIFF(), 1, 0.5));
			break;
		case 1:
			Circle(ConvertVec2ToVec2(getRealPosition()), 10 * getZoom()).draw(HSV(BaseUnit->getIFF(), 1, 0.5));
			Line(ConvertVec2ToVec2(getRealPosition()), ConvertVec2ToVec2(getRealPosition()) + GlobalAngle * 20 * getZoom()).draw(5 * getZoom(), HSV(BaseUnit->getIFF(), 1, 0.5));
			break;
		default:
			break;
		}
	}
}
Turret::Turret()
{
	Enabled = false;
	LocalPosition = Vec2(0, 0);
	GlobalAngle = Vec2(1, 0);
	TargetAngle = Vec2(1, 0);
	Range = 300.0;
	ReloadCount = 0;
	ReloadTime = 10;
	TurningPerformance = 0.2;
	BaseUnit = NULL;
	Type = 0;
}

Turret::~Turret()
{
}

Vec2 Turret::getTargetAngle() const
{
	return TargetAngle;
}


int Turret::getType() const
{
	return Type;
}

Unit* Turret::getBaseUnit() const
{
	return BaseUnit;
}

Vec2 Turret::getRealPosition() const
{
	return BaseUnit->getPosition() + LocalPosition.rotated(Circular3(BaseUnit->getAngle()).theta);
}

void Turret::setBaseUnit(Unit *unit)
{
	BaseUnit = unit;
}

void Turret::setRange(double range)
{
	Range = range;
}

void Turret::setAngle(Vec2 angle)
{
	GlobalAngle = angle;
}

void Turret::setEnable(bool flag)
{
	Enabled = flag;
}

void Turret::setLocalPosition(Vec2 position)
{
	LocalPosition = position;
}

void Turret::setType(int type)
{
	Type = type;
}

void Turret::addRotate(double angle)
{
	if (Enabled)
		GlobalAngle.rotate(angle);
}

void Turret::updateAngle()
{
	if (abs(TargetAngle.cross(GlobalAngle)) < Sin(TurningPerformance))
		GlobalAngle = TargetAngle;
	else
	{
		if (TargetAngle.cross(GlobalAngle) > 0)
			GlobalAngle.rotate(-TurningPerformance);
		else
			GlobalAngle.rotate(TurningPerformance);
	}
}

void Turret::shot()
{
	--ReloadCount;
	if (ReloadCount < 0)
	{
		Unit* target = searchEnemyUnit();
		if (target != NULL)
		{
			TargetAngle = (target->getPosition() - getRealPosition()).normalized();	//�ˌ��p���Z�b�g
			if (abs(TargetAngle.cross(GlobalAngle)) < 0.1)
			{
				bullets.push_back(this);
				ReloadCount = ReloadTime;
			}
		}
	}
}

Unit* Turret::searchEnemyUnit()
{
	Unit* target = NULL;
	double distance = Range;
	Vec2 realPosition = getRealPosition();
	for (auto& unit : units)
	{
		if (unit.getEnabled() && BaseUnit->getIFF() != unit.getIFF() && realPosition.distanceFrom(unit.getPosition()) < distance)
		{
			distance = realPosition.distanceFrom(unit.getPosition());
			target = &unit;
		}
	}
	if (target == NULL)
		Status = 0;
	else
		Status = 1;
	return target;
}