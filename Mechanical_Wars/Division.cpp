#include"Division.h"
#include"Graphics.h"
#include"Unit.h"
#include"Mission.h"

extern Array<Mission> missions;

void Division::update()
{
	if (!Enabled) return;
	findMission();
	relocate();
}

bool Division::canJoinDivision(Unit* unit) const
{
	if (!Enabled || IFF != unit->IFF || getNumMemberUnit() == DIVISION_MAX_MEMBER) return false;
	return true;
}

double Division::getJoinPriority(Unit* unit) const
{
	double priority = 0;
	if (getNumMemberUnit() != 0)
	{
		priority = getPosition().distanceFrom(unit->Position);	//距離で優先度を設定
	}
	else
	{
		priority = 0;
	}
	if (unit->isSupplyUnit() && getNumSupplyUnit() == 0) priority *= 0.01;	//補給ユニットがない場合
	priority *= Pow(getNumMemberUnit(), 2);
	return priority*0.01;
}

void Division::findMission()
{
	if (InProcessMission != NULL) InProcessMission->ActiveDivision = NULL;
	for (auto& mission : missions)
	{
		if (mission.Enabled && mission.IFF == IFF && mission.ActiveDivision == NULL)
		{
			if (InProcessMission != NULL && mission.BAL >= InProcessMission->BAL) continue;
			InProcessMission = &mission;
		}
	}
	if (InProcessMission != NULL) InProcessMission->ActiveDivision = this;
}

bool Division::set(int iff)
{
	if (Enabled) return false;
	Enabled = true;
	IFF = iff;
	for (auto& memberUnit : MemberUnits)
		memberUnit = NULL;
	InProcessMission = NULL;
	findMission();
	return true;
}

void Division::JoinDivision(Unit* unit)
{


#ifdef ERROR
	if (!Enabled)
	{
		LOG_ERROR(L"Division::JoinDivision() Enabled is false");
		return;
	}
#endif // ERROR

	for (auto& memberUnit : MemberUnits)
	{
		if (memberUnit != NULL) continue;
		memberUnit = unit;
		unit->AssignedDivision = this;
		return;
	}

#ifdef ERROR
	LOG_ERROR(L"Division::JoinDivision() Over member capacity");
#endif // ERROR

}


void Division::relocate()
{
	//間の空いているユニットを前に入れ替え
	for (int i = 0; i < DIVISION_MAX_MEMBER; i++)
	{
		if (MemberUnits[i] == NULL)
		{
			for (int j = i + 1; j < DIVISION_MAX_MEMBER; j++)
			{
				if (MemberUnits[j] == NULL) continue;
				MemberUnits[i] = MemberUnits[j];
				break;
			}
		}
	}

	//先頭のユニットが補給ユニットなら交代
	if (MemberUnits[0] != NULL && MemberUnits[0]->isSupplyUnit())
	{
		for (auto& memberUnit : MemberUnits)
		{
			if (memberUnit != NULL && !memberUnit->isSupplyUnit())
			{
				Unit* unit = MemberUnits[0];
				MemberUnits[0] = memberUnit;
				memberUnit = unit;
				break;
			}
		}
	}
}


Vec2 Division::getPosition() const
{
	if (getLeader() != NULL) return getLeader()->Position;


#ifdef ERROR
	Println(L"Division::getPosition()　No MemberUnit");
	return Vec2(0, 0);
#endif // ERROR
}
Unit* Division::getLeader() const
{
	for (auto& memberUnit : MemberUnits)
		if (memberUnit != NULL) return memberUnit;

#ifdef ERROR
	LOG_ERROR(L"Division::getLeader()　No MemberUnit");
	return NULL;
#endif // ERROR


}

Vec2 Division::getTargetPosition(Unit* unit) const
{
	if (unit == NULL)
	{
		if (getLeader() != NULL) return getLeader()->Position;

#ifdef ERROR
		LOG_ERROR(L"Division::getTargetPosition()　No MemberUnit");
		return Vec2(0, 0);
#endif // ERROR


	}
	else
	{
		for (int i = 0; i < DIVISION_MAX_MEMBER; i++)
		{
			if (MemberUnits[i] != unit) continue;

			//リーダー
			if (i == 0)
			{
				if (InProcessMission != NULL) return InProcessMission->Position;
			}
			if (i % 2)
			{
				return getPosition() + i * getUnitInterval() * getTargetAngle().rotated(HalfPi);
			}
			else
			{
				return getPosition() - i * getUnitInterval() * getTargetAngle().rotated(HalfPi);
			}
		}
	}

#ifdef ERROR
	LOG_ERROR(L"Division::getTargetPosition()　unit isn't MemberUnit");
	return Vec2(0, 0);
#endif // ERROR

}

double Division::getUnitInterval() const
{

#ifdef ERROR
	if (!Enabled) LOG_ERROR(L"Division::getUnitInterval() Enabled is false");
	if (getNumMemberUnit() == 0) LOG_ERROR(L"Division::getUnitInterval() no member unit");
#endif // ERROR

	return 64.0 / double(getNumMemberUnit());
}

Vec2 Division::getTargetAngle() const
{
	if (InProcessMission == NULL)
		return Vec2(1, 0);
	else
		return InProcessMission->getAngle();
}

int Division::getNumSupplyUnit() const
{
	int count = 0;
	for (auto& memberUnit : MemberUnits)
	{
		if (memberUnit == NULL || !memberUnit->isSupplyUnit()) continue;
		++count;
	}
	return count;
}

int Division::getNumMemberUnit() const
{
	int count = 0;
	for (auto& memberUnit : MemberUnits)
	{
		if (memberUnit != NULL) ++count;
	}
	return count;
}

void Division::draw() const
{

	if (!Enabled) return;
	if (getNumMemberUnit() == 0) return;	//部隊がいないなら
	//中心の円
	Circle(ConvertVec2ToVec2(getPosition()), 64 * getZoom()).draw(Color(HSV(IFF), 64));

	//目標の方向
	Line(ConvertVec2ToVec2(getPosition()), ConvertVec2ToVec2(getPosition() + getTargetAngle() * 128)).drawArrow(32, Vec2(64, 64)*getZoom(), Color(HSV(IFF), 64));
}