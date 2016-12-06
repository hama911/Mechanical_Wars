#include"Bullet.h"
#include"Unit.h"
#include"Motion.h"
#include"Graphics.h"

extern Array<Unit> units;
extern Array<Motion> motions;

void Bullet::update()
{
	if (!Enabled) return;
	--Count;
	for (auto& motion : motions)
		if (motion.setFromBulletLine(Position, Position + Angle*(SpeedPerformance - 1), Type)) break;
	Position.moveBy(Angle*SpeedPerformance);
	if (Count < 0)
	{
		for (auto& motion : motions)
			if (motion.setFromBullet(this)) break;
		reset();
	}
	if(Target!=NULL)
	{
		if (Target->hitCheck(Position))
		{
			Target->addDamege(this);
			for (auto& motion : motions)
				if (motion.setFromBullet(this)) break;
			reset();
		}
	}
	else
	{
		if (hitCheck())
		{
			for (auto& motion : motions)
				if (motion.setFromBullet(this)) break;
			reset();
		}
	}
}

Unit* Bullet::hitCheck()
{
	Unit* target = NULL;
	for (auto& unit : units)
	{
		if (unit.Enabled && IFF != unit.IFF && unit.hitCheck(Position))
		{
			target = &unit;
			unit.addDamege(this);
		}
	}
	return target;
}

void Bullet::draw() const
{
	if (!Enabled) return;
	drawBullet();
}

void Bullet::reset()
{
	Enabled = false;
	IFF = 0;
	Position = Vec2(0, 0);
	Angle = Vec2(0, 0);
	Count = 0;
	Type = 0;
	SpeedPerformance = 0;
}

bool Bullet::set(Turret* turret, Unit* target = NULL)
{
	if (Enabled) return false;
	Enabled = true;
	Count = int(turret->Count)*1.1;
	IFF = turret->BaseUnit->IFF;
	Position = turret->getRealPosition();
	Angle = turret->TargetAngle;
	Type = turret->Type;
	Target = target;
	setBulletData();
	//�ǐՃV�X�e��
	//serchEnemyUnit();
	return true;
}

Unit* Bullet::serchEnemyUnit()
{

	double length = 300.0;	//���G�\����
	Unit* target = NULL;	//�^�[�Q�b�g
	for (auto& unit : units)
	{
		if (unit.Enabled && IFF != unit.IFF && Position.distanceFrom(unit.Position) < length)
		{
			length = Position.distanceFrom(unit.Position);
			target = &unit;
		}
	}
	if (target != NULL)
	{
		Angle = (target->Position + target->Angle*target->getSpeedVec2()*((target->Position.distanceFrom(Position) / (Angle*SpeedPerformance - target->Angle*target->getSpeedVec2()).length())) - Position).normalized();

	}
	return target;
}
