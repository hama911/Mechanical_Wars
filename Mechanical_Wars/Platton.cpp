#include"Platoon.h"
#include"Graphics.h"
#include"Unit.h"

void Platoon::setFromUnit(Unit* leader)
{
	LeaderUnit = leader;
	MemberUnits[0] = leader;
	leader->setPlatoon(this);
	Enabled = true;
	TargetAngle.rotate(Random(TwoPi));
	TargetPosition = Vec2(Random(1024), Random(1024));
}

Platoon::Platoon()
{
	reset();
}

Unit* Platoon::getLeaderInfo()
{
	return LeaderUnit;
}

Vec2 Platoon::getAngle()
{
	return LeaderUnit->getAngle();
}

int Platoon::getIFF()
{
	if (LeaderUnit == NULL) return -1;
	return LeaderUnit->getIFF();
}

int Platoon::getRank(Unit* unit)
{
	if (unit == LeaderUnit) return 1;
	return 0;
}
int Platoon::getTotalMember()
{
	int count = 0;
	for (auto& unit : MemberUnits)
		if (unit != NULL) ++count;
	return count;
}
bool Platoon::joinPlatoon(Unit* member)
{
	if (LeaderUnit != NULL && (member->getIFF() != LeaderUnit->getIFF() || member->getPosition().distanceFrom(LeaderUnit->getPosition()) > 256)) return false;
	if (!Enabled)
	{
		setFromUnit(member);
		return true;
	}
	else {
		for (auto& unit : MemberUnits)
		{
			if (unit == NULL)
			{
				member->setPlatoon(this);
				unit = member;
				return true;
			}
		}
	}
	return false;
}

void Platoon::reset()
{
	Enabled = false;
	for (auto& unit : MemberUnits)
		unit = NULL;
	LeaderUnit = NULL;
	TargetPosition = Vec2(0, 0);
	TargetAngle = Vec2(1, 0);
}

Platoon::~Platoon()
{
}

void Platoon::update()
{
	if (!Enabled) return;
	for (auto& unit1 : MemberUnits)
	{
		if (unit1 != NULL && (unit1->getPlatoon() != this || !unit1->getEnabled()))
		{
			if (unit1 == LeaderUnit)
			{
				unit1 = NULL;
				for (auto& unit2 : MemberUnits)
				{
					if (unit2 != NULL)
					{
						LeaderUnit = unit2;
						break;
					}
				}
				if (LeaderUnit->getPlatoon() != this)
				{
					reset();
					return;
				}
			}
			else
			{
				unit1 = NULL;
			}
			relocation();
		}
	}
}
void Platoon::relocation()
{
	Unit* NewUnits[MAX_MEMBER];
	for (auto& unit1 : NewUnits)
		unit1 = NULL;
	for (auto& unit1 : MemberUnits)
	{
		if (unit1 != NULL)
		{
			for (auto& unit2 : NewUnits)
			{
				if (unit2 == NULL)
				{
					unit2 = unit1;
					break;
				}
			}
		}
	}
	for (int i = 0; i < MAX_MEMBER; i++)
		MemberUnits[i] = NewUnits[i];
}
double Platoon::getUnitSpeed(Unit* unit)
{
	if (abs(getUnitTargetAngle(unit).cross(unit->getAngle())) < 0.8 && getUnitTargetAngle(unit).dot(unit->getAngle()) > 0)
	{
		if ((getUnitTargetPosition(unit) - unit->getPosition()).length() < 1)
		{
			return 0;
		}
		if ((getUnitTargetPosition(unit) - unit->getPosition()).length() < 5)
		{
			return unit->getSpeedPerformance() / 4;
		}
		if (unit == LeaderUnit) return unit->getSpeedPerformance() / 2;
		return unit->getSpeedPerformance();
	}
	else
	{
		return 0;
	}
}
Vec2 Platoon::getUnitTargetPosition(Unit* unit)
{
	Vec2 local;
	int count = 1;
	if (unit == LeaderUnit)
	{
		return TargetPosition;
	}
	else
	{
		for (auto& member : MemberUnits)
		{
			if (member == LeaderUnit) continue;
			if (count % 2 == 1)
			{
				local = Vec2(-count * 5 - 5, count * 15 + 15);

			}
			else
			{
				local = Vec2(-count * 5, -count * 15);
			}
			if (member == unit) break;
			++count;
		}
	}

	if ((TargetPosition - LeaderUnit->getPosition()).length() < 1)
		return  LeaderUnit->getPosition() + local.rotated(Vec2ToRadian(TargetAngle));
	else
		return  LeaderUnit->getPosition() + local.rotated(Vec2ToRadian(LeaderUnit->getAngle()));
}
Vec2 Platoon::getUnitTargetAngle(Unit* unit)
{
	if ((getUnitTargetPosition(unit) - unit->getPosition()).length() < 1)
		return TargetAngle;
	else
		return (getUnitTargetPosition(unit) - unit->getPosition()).normalized();
}

void Platoon::draw() const
{
	if (!Enabled) return;
	if (LeaderUnit == NULL) return;
	Circle(ConvertVec2ToVec2(LeaderUnit->getPosition()), 16 * getZoom()).draw(Color(HSV(LeaderUnit->getIFF()), 64));
	Circle(ConvertVec2ToVec2(LeaderUnit->getPosition()), 256 * getZoom()).draw(Color(HSV(LeaderUnit->getIFF()), 8));
	Line(ConvertVec2ToVec2(LeaderUnit->getPosition()), ConvertVec2ToVec2(TargetPosition)).draw(10 * getZoom(), Color(HSV(LeaderUnit->getIFF()), 128));
	for (auto& unit : MemberUnits)
	{
		if (unit == NULL) continue;
		Line(ConvertVec2ToVec2(LeaderUnit->getPosition()), ConvertVec2ToVec2(unit->getPosition())).draw(Color(HSV(LeaderUnit->getIFF()), 64));
	}
}