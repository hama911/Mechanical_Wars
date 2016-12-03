#include"Platoon.h"
#include"Graphics.h"
#include"Unit.h"
#include"Mission.h"
#include"Power.h"
extern Array<Power> powers;
extern Array<Mission> missions;
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
	RunningMission = NULL;
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
	if (!Enabled) return 10000;
	if (!Enabled || getTotalMember() == MAX_MEMBER || LeaderUnit == NULL || LeaderUnit == SupplyUnit || unit->IFF != LeaderUnit->IFF) return 20000;
	if (unit->Type == 2)
	{
		if (SupplyUnit != NULL) return 10000;
	}
	else
	{
		if (getTotalMember() == MAX_MEMBER - 1 && SupplyUnit == NULL) return 20000;
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
		if (powers[member->IFF].FreeMission)
		{
			setFromUnit(member);
			if (member->Type == 2)
			{
				SupplyUnit = member;
			}
		}
		return powers[member->IFF].FreeMission;
	}
	else
	{
		if (member->Type == 2)
		{
			if (SupplyUnit != NULL) return false;
		}
		else
		{
			if (getTotalMember() == MAX_MEMBER - 1 && SupplyUnit == NULL) return false;
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


	//メンバーの欠損に対する対処
	for (auto& unit1 : MemberUnits)
	{
		if (unit1 != NULL && (unit1->MyPlatoon != this || !unit1->Enabled))
		{
			if (unit1 == SupplyUnit) SupplyUnit = NULL;
			if (unit1 == LeaderUnit)
			{
				unit1 = NULL;
				double distance = 10000;
				for (auto& unit2 : MemberUnits)
				{
					if (unit2 != NULL && unit2->Enabled && unit2->Position.distanceFrom(TargetPosition) < distance)
					{
						distance = unit2->Position.distanceFrom(TargetPosition);
						LeaderUnit = unit2;
					}
				}
				if (!LeaderUnit->Enabled)
				{
					reset();
					return;
				}
			}
			else
			{
				unit1 = NULL;
			}
			//relocation();	//再配置
		}
	}


	//リーダーを先頭に
	Unit* frontUnit = MemberUnits[0];
	for (auto& unit : MemberUnits)
		if (unit == LeaderUnit) unit = frontUnit;
	MemberUnits[0] = LeaderUnit;

	//ミッションの確認
	if (RunningMission != NULL && RunningMission->Prosecutor != this) RunningMission = NULL;
	if (RunningMission == NULL || !RunningMission->Enabled)
	{
		double distance = 10000;
		bool cz_flag = false;
		Mission *mission2 = NULL;
		for (auto& mission : missions)
		{
			if (mission.Enabled && mission.IFF == LeaderUnit->IFF && mission.Prosecutor == NULL)
			{
				bool flag = false;
				for (auto & connect : mission.Connects)
					if (connect != NULL && connect->IFF != mission.IFF) flag = true;
				if (flag >= cz_flag && mission.Position.distanceFrom(LeaderUnit->Position) < distance)
				{
					distance = mission.Position.distanceFrom(LeaderUnit->Position);
					cz_flag = flag;
					RunningMission = &mission;
					mission2 = &mission;
				}
			}
		}
		if (mission2 != NULL) mission2->Prosecutor = this;
	}
	else
	{
		double distance = 10000;
		bool cz_flag = false;
		for (auto & connect : RunningMission->Connects)
			if (connect != NULL && connect->IFF != RunningMission->IFF) cz_flag = true;
		Mission *mission2 = NULL;
		for (auto& mission : missions)
		{
			if (mission.Enabled && mission.IFF == LeaderUnit->IFF && (mission.Prosecutor == NULL || mission.Prosecutor == this))
			{
				bool flag = false;
				for (auto & connect : mission.Connects)
					if (connect != NULL && connect->IFF != mission.IFF) flag = true;
				if (flag > cz_flag || (flag == cz_flag && mission.Position.distanceFrom(LeaderUnit->Position) < distance))
				{
					distance = mission.Position.distanceFrom(LeaderUnit->Position);
					cz_flag = flag;
					RunningMission = &mission;
					mission2 = &mission;
				}
			}
		}
		if (mission2 != NULL) mission2->Prosecutor = this;
	}
	if (RunningMission != NULL)
	{
		TargetAngle = RunningMission->Angle;
		TargetPosition = RunningMission->Position;
	}
	else
	{
		Enabled = false;
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
		if (unit == LeaderUnit) return unit->SpeedPerformance *0.8;
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
			local = Vec2(-count * 3 - 3, count * 13 + 13);
		}
		else
		{
			local = Vec2(-count * 3, -count * 13);
		}
		break;
	}

	if (unit == SupplyUnit) local = Vec2(-30, 0);


	if ((TargetPosition - LeaderUnit->Position).length() < 64)
		return  TargetPosition + local.rotated(Vec2ToRadian(TargetAngle));
	else
		return  LeaderUnit->Position + local.rotated(Vec2ToRadian(LeaderUnit->Angle));
}
Vec2 Platoon::getUnitTargetAngle(Unit* unit)
{
	if (unit == LeaderUnit)
	{
		if ((getUnitTargetPosition(unit) - unit->Position).length() < 1)
			return TargetAngle;
		else
			return (getUnitTargetPosition(unit) - unit->Position).normalized();
	}
	else
	{
		if ((getUnitTargetPosition(unit) - unit->Position).length() < 1)
			return TargetAngle;
		else
			return (getUnitTargetPosition(unit) - unit->Position).normalized();

	}
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