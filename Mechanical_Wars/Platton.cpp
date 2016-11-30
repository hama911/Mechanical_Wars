#include"Platoon.h"
#include"Graphics.h"
#include"Unit.h"

extern Platoon* SelectedPlatoon;
void Platoon::setFromUnit(Unit* leader)
{
	for (auto& unit : MemberUnits)
		unit = NULL;
	LeaderUnit = leader;
	MemberUnits[0] = leader;
	leader->setPlatoon(this);
	Enabled = true;
	TargetAngle = Vec2(1, 0);
	TargetPosition = leader->getPosition();
	SupplyUnit = NULL;
}

Platoon::Platoon()
{
	reset();
}

Unit* Platoon::getLeaderInfo()
{
	return LeaderUnit;
}

double Platoon::getJoinDistance(Unit* unit)
{
	if (!Enabled || getTotalMember() == MAX_MEMBER || LeaderUnit == NULL || LeaderUnit == SupplyUnit || unit->getIFF() != LeaderUnit->getIFF()) return 10000;
	if (unit->getType() == 2)
	{
		if (SupplyUnit != NULL) return 10000;
	}
	else
	{
		if (getTotalMember() == 4 && SupplyUnit == NULL) return 10000;
	}
	return unit->getPosition().distanceFrom(LeaderUnit->getPosition());
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
	if (LeaderUnit != NULL && member->getIFF() != LeaderUnit->getIFF()) return false;
	if (!Enabled)
	{
		setFromUnit(member);
		if (member->getType() == 2)
		{
			SupplyUnit = member;
		}
		return true;
	}
	else
	{
		if (member->getType() == 2)
		{
			if (SupplyUnit != NULL) return false;
		}
		else
		{
			if (getTotalMember() == 4 && SupplyUnit == NULL) return false;
		}
		for (auto& unit : MemberUnits)
		{
			if (unit == NULL)
			{
				member->setPlatoon(this);
				unit = member;
				if (LeaderUnit == SupplyUnit&&member->getType() != 2) LeaderUnit = member;
				if (member->getType() == 2) SupplyUnit = member;
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
	SupplyUnit = NULL;
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
			if (unit1 == SupplyUnit) SupplyUnit = NULL;
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
			//relocation();	//çƒîzíu
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
	int count = 0;
	if (unit == LeaderUnit) return TargetPosition;
	for (auto& member : MemberUnits)
	{

		if (member != LeaderUnit && member != SupplyUnit) ++count;
		if (member != unit) continue;
		if (count % 2 == 1)
		{
			local = Vec2(-count * 5 - 5, count * 15 + 15);

		}
		else
		{
			local = Vec2(-count * 5, -count * 15);
		}
		break;
	}

	if (unit == SupplyUnit) local = Vec2(-30, 0);


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
	if (this == SelectedPlatoon) Circle(ConvertVec2ToVec2(LeaderUnit->getPosition()), 20 * getZoom()).draw(Palette::Yellow);

	Line(ConvertVec2ToVec2(TargetPosition), ConvertVec2ToVec2(TargetPosition + TargetAngle * 40)).drawArrow(10 * getZoom(), Vec2(20, 20)*getZoom(), Color(HSV(LeaderUnit->getIFF()), 128));
	Circle(ConvertVec2ToVec2(LeaderUnit->getPosition()), 16 * getZoom()).draw(Color(HSV(LeaderUnit->getIFF()), 64));
	Circle(ConvertVec2ToVec2(LeaderUnit->getPosition()), 256 * getZoom()).draw(Color(HSV(LeaderUnit->getIFF()), 8));
	Line(ConvertVec2ToVec2(LeaderUnit->getPosition()), ConvertVec2ToVec2(TargetPosition)).draw(10 * getZoom(), Color(HSV(LeaderUnit->getIFF()), 128));
	for (auto& unit : MemberUnits)
	{
		if (unit == NULL) continue;
		Line(ConvertVec2ToVec2(LeaderUnit->getPosition()), ConvertVec2ToVec2(unit->getPosition())).draw(Color(HSV(LeaderUnit->getIFF()), 64));
	}
}