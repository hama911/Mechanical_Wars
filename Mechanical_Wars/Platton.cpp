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
	leader->MyPlatoon = this;
	Enabled = true;
	TargetAngle = Vec2(1, 0);
	TargetPosition = leader->Position;
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
	if (!Enabled || getTotalMember() == MAX_MEMBER || LeaderUnit == NULL || LeaderUnit == SupplyUnit || unit->IFF != LeaderUnit->IFF) return 10000;
	if (unit->Type == 2)
	{
		if (SupplyUnit != NULL) return 10000;
	}
	else
	{
		if (getTotalMember() == 4 && SupplyUnit == NULL) return 10000;
	}
	return unit->Position.distanceFrom(LeaderUnit->Position);
}

Vec2 Platoon::getAngle()
{
	return LeaderUnit->Angle;
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
	if (LeaderUnit != NULL && member->IFF != LeaderUnit->IFF) return false;
	if (!Enabled)
	{
		setFromUnit(member);
		if (member->Type == 2)
		{
			SupplyUnit = member;
		}
		return true;
	}
	else
	{
		if (member->Type == 2)
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
				member->MyPlatoon = this;
				unit = member;
				if (LeaderUnit == SupplyUnit&&member->Type != 2) LeaderUnit = member;
				if (member->Type == 2) SupplyUnit = member;
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
		if (unit1 != NULL && (unit1->MyPlatoon != this || !unit1->Enabled))
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
				if (LeaderUnit->MyPlatoon != this)
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
	if (abs(getUnitTargetAngle(unit).cross(unit->Angle)) < 0.8 && getUnitTargetAngle(unit).dot(unit->Angle) > 0)
	{
		if ((getUnitTargetPosition(unit) - unit->Position).length() < 1)
		{
			return 0;
		}
		if ((getUnitTargetPosition(unit) - unit->Position).length() < 5)
		{
			return unit->SpeedPerformance / 4;
		}
		if (unit == LeaderUnit) return unit->SpeedPerformance / 2;
		return unit->SpeedPerformance;
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


	if ((TargetPosition - LeaderUnit->Position).length() < 1)
		return  LeaderUnit->Position + local.rotated(Vec2ToRadian(TargetAngle));
	else
		return  LeaderUnit->Position + local.rotated(Vec2ToRadian(LeaderUnit->Angle));
}
Vec2 Platoon::getUnitTargetAngle(Unit* unit)
{
	if ((getUnitTargetPosition(unit) - unit->Position).length() < 1)
		return TargetAngle;
	else
		return (getUnitTargetPosition(unit) - unit->Position).normalized();
}

void Platoon::draw() const
{
	if (!Enabled) return;
	if (LeaderUnit == NULL) return;
	if (this == SelectedPlatoon) Circle(ConvertVec2ToVec2(LeaderUnit->Position), 20 * getZoom()).draw(Palette::Yellow);

	Line(ConvertVec2ToVec2(TargetPosition), ConvertVec2ToVec2(TargetPosition + TargetAngle * 40)).drawArrow(10 * getZoom(), Vec2(20, 20)*getZoom(), Color(HSV(LeaderUnit->IFF), 128));
	Circle(ConvertVec2ToVec2(LeaderUnit->Position), 16 * getZoom()).draw(Color(HSV(LeaderUnit->IFF), 64));
	Circle(ConvertVec2ToVec2(LeaderUnit->Position), 256 * getZoom()).draw(Color(HSV(LeaderUnit->IFF), 8));
	Line(ConvertVec2ToVec2(LeaderUnit->Position), ConvertVec2ToVec2(TargetPosition)).draw(10 * getZoom(), Color(HSV(LeaderUnit->IFF), 128));
	for (auto& unit : MemberUnits)
	{
		if (unit == NULL) continue;
		Line(ConvertVec2ToVec2(LeaderUnit->Position), ConvertVec2ToVec2(unit->Position)).draw(Color(HSV(LeaderUnit->IFF), 64));
	}
}