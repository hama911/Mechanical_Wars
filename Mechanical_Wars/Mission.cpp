#include"Mission.h"
#include"Graphics.h"
#include"Unit.h"
extern Array<Mission> missions;
extern Mission* SelectedMission;
extern Array<Unit> units;

void updateMissions()
{
	for (auto& mission : missions)
		mission.BAL = 4;
	for (int i = 0; i < 5; i++)
	{
		for (auto& mission : missions)
			mission.setBAL();
	}
	for (auto& mission : missions)
		mission.update();
}

void Mission::setBAL()
{
	if (!Enabled) return;
	for (auto& connect : Connects)
	{
		if (connect != NULL) {

			//隣が異なるIFFの場合
			if (connect->IFF != IFF) 
			{
				BAL = 0;
				return;
			}

			//隣のBALによって決まる場合
			if (connect->BAL < BAL) BAL = connect->BAL + 1;	//違うIFFなら必ずBAL=0となるため、記述しない
		}
	}
}

void Mission::update()
{
	if (!Enabled) return;


}

Vec2 Mission::getAngle() const
{
	if (!Enabled) LOG_ERROR(L"Mission::getAngle() Enabled is false");

	int count = 0;
	Vec2 position = Vec2(0, 0);
	for (auto& connect : Connects)
	{
		if (connect != NULL && connect->IFF!=IFF)
		{
			++count;
			position += connect->Position;
		}
	}

	if (count == 0) return Vec2(1, 0);	//もし隣接するすべてが友好的ミッションの場合
	return (position / count - Position).normalized();
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

bool Mission::set(Vec2 position, int iff)
{
	if (Enabled) return false;
	ActiveDivision = NULL;
	Enabled = true;
	Position = position;
	IFF = iff;
	for (auto& connect : Connects)
		connect = NULL;
	//接続先を作成
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
