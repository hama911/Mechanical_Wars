#include"Platoon.h"
#include"Graphics.h"
#include"Unit.h"

void Platoon::setLeaderUnit(Unit* leader)
{
	LeaderUnit = leader;
}

Platoon::Platoon()
{
	Enabled = true;
	for (auto& unit : MemberUnits)
		unit = NULL;
	LeaderUnit = NULL;
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
	if (!Enabled) return false;
	if (LeaderUnit != NULL && (member->getIFF() != LeaderUnit->getIFF() || member->getPosition().distanceFrom(LeaderUnit->getPosition()) > 256)) return false;
	bool flag = false;
	for (auto& unit : MemberUnits)
	{
		if (unit == NULL)
		{
			if (LeaderUnit == NULL) LeaderUnit = member;
			flag = true;
			member->setPlatoon(this);
			unit = member;
			break;
		}
	}
	return flag;
}

Platoon::~Platoon()
{
}

void Platoon::update()
{
	if (!Enabled) return;
	for (auto& unit : MemberUnits)
	{
		if (unit != NULL && unit->getPlatoon() != this)
		{
			if (unit == LeaderUnit)
			{
				unit = NULL;
				for (auto& unit : MemberUnits)
				{
					if (unit != NULL) LeaderUnit = unit;
				}
				if (LeaderUnit->getPlatoon() != this) LeaderUnit = NULL;
			}
			else
			{
				unit = NULL;
			}
		}
	}
}

Vec2 Platoon::getPosition(Unit* unit)
{
	//return Vec2(0, 0);
	//if (LeaderUnit == NULL) return Vec2(0, 0);
	Vec2 local;
	int count = 2;
	for (auto& member : MemberUnits)
	{
		if (member == LeaderUnit) continue;
		if (count % 2 == 1)
		{
			local = Vec2(-count * 5, count * 15);

		}
		else
		{
			local = Vec2(-count * 5, -count * 15);
		}
		if (member == unit) break;
		++count;
	}

	return  LeaderUnit->getPosition() + local.rotated(Vec2ToRadian(LeaderUnit->getAngle()));
}

void Platoon::draw() const
{
	if (!Enabled) return;
	if (LeaderUnit == NULL) return;
	Circle(ConvertVec2ToVec2(LeaderUnit->getPosition()), 16 * getZoom()).draw(Color(HSV(LeaderUnit->getIFF()), 64));
	Circle(ConvertVec2ToVec2(LeaderUnit->getPosition()), 256 * getZoom()).draw(Color(HSV(LeaderUnit->getIFF()), 8));
	for (auto& unit : MemberUnits)
	{
		if (unit == NULL) continue;
		Line(ConvertVec2ToVec2(LeaderUnit->getPosition()), ConvertVec2ToVec2(unit->getPosition())).draw(Color(HSV(LeaderUnit->getIFF()), 64));
	}
}