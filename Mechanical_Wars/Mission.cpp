#include"Mission.h"
#include"Graphics.h"
#include"Platoon.h"
#include"Unit.h"
extern Array<Mission> missions;
extern Mission* SelectedMission;
extern Array<Unit> units;
void Mission::update()
{
	if (!Enabled) return;
	if (Prosecutor != NULL && Prosecutor->RunningMission != this) Prosecutor = NULL;
	if (Priority <= 0) Enabled = false;
	//ìGÇ…ÇÊÇÈêËóÃîªíË
	Mission *target = NULL;
	int occupier = 0;
	if (Prosecutor != NULL)
	{
		for (auto& unit : Prosecutor->MemberUnits)
		{
			if (unit != NULL && unit->Position.distanceFrom(Position) < 192) ++occupier;
		}
	}
	else
	{
		occupier = 0;
	}

	int enemyOccupier = 0;
	for (auto& connect : Connects)
	{
		if (connect != NULL && connect->IFF != IFF && connect->Prosecutor != NULL)
		{
			int count = 0;
			for (auto& unit : connect->Prosecutor->MemberUnits)
			{
				if (unit != NULL && unit->Position.distanceFrom(Position) < 192) ++count;
			}
			if (count > enemyOccupier && count > occupier + 2) {
				enemyOccupier = count;
				target = connect;
			}
		}
	}
	if (target != NULL)
	{
		//ñ°ï˚ÅAìGÇÃóDóÚîªíË
		int count = 0;
		for (auto& unit : units)
		{
			if (unit.Enabled && unit.Position.distanceFrom(Position) < 192)
			{
				if (unit.IFF == IFF) --count;
				if (unit.IFF != IFF) ++count;
			}
		}
		if (count > 0)
		{
			if (Prosecutor != NULL) Prosecutor->RunningMission = target->Prosecutor->RunningMission;
			Prosecutor = target->Prosecutor;
			target->Prosecutor = NULL;
			IFF = target->IFF;
		}

	}


	//äpìxÇÃê›íË
	if (Prosecutor != NULL)
	{
		Vec2 enemyAngle = Vec2(0, 0);
		for (auto& connect : Connects)
		{
			if (connect != NULL && connect->IFF != IFF)
			{
				enemyAngle += (connect->Position - Position).normalized();
			}
		}
		Angle = Vec2(1, 0).rotated(Vec2ToRadian(enemyAngle));
	}
}

void Mission::draw() const
{
	if (!Enabled) return;
	if (SelectedMission == this) Circle(ConvertVec2ToVec2(Position), 35 * getZoom()).drawFrame(1 * getZoom(), 0, Palette::Yellow);
	for (auto& connect : Connects)
		if (connect != NULL) Line(ConvertVec2ToVec2(Position), ConvertVec2ToVec2(connect->Position)).draw(20 * getZoom(), Color(255, 255, 255, 64));
	if (Position.distanceFrom(DisConvertVec2ToVec2(Mouse::Pos())) < 50)
	{
		Circle(ConvertVec2ToVec2(Position), 35 * getZoom()).drawFrame(1 * getZoom(), 0, Color(Palette::Yellow, 128));

	}
	Circle(ConvertVec2ToVec2(Position), 64 * getZoom()).drawFrame(1 * getZoom(), 0, HSV(IFF));
	Circle(ConvertVec2ToVec2(Position), ((5 - BAL) * 5) * getZoom()).draw(HSV(IFF));

}

bool Mission::set(Vec2 position, int iff, Platoon* platoon, int priority)
{
	if (Enabled) return false;
	Enabled = true;
	Position = position;
	Angle = Vec2(1, 0);
	IFF = iff;
	Prosecutor = platoon;
	Priority = priority;
	for (auto& connect : Connects)
		connect = NULL;
	//ê⁄ë±êÊÇçÏê¨
	for (auto& mission : missions)
	{
		if (mission.Enabled && mission.Position.distanceFrom(position) <= 200 && &mission != this)
		{

			for (auto& connect : Connects)
			{
				if (connect == NULL)
				{
					connect = &mission;
					break;
				}
			}
			for (auto& connect : mission.Connects)
			{
				if (connect == NULL)
				{
					connect = this;
					break;
				}
			}
		}
	}
	return true;
}

bool Mission::getBattleFlag()
{
	if (!Enabled) return false;
	for (auto& connect : Connects)
		if (connect != NULL && connect->IFF != IFF) return true;
	return false;
}

void Mission::setBAL()
{
	if (!Enabled) return;
	if (getBattleFlag()) BAL = 0;
	for (auto& connect : Connects)
		if (connect != NULL && connect->IFF == IFF && connect->BAL < BAL) BAL = connect->BAL + 1;
}