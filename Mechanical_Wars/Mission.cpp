#include"Mission.h"
#include"Graphics.h"
#include"Platoon.h"

extern Array<Mission> missions;
extern Mission* SelectedMission;

void Mission::update()
{
	if (!Enabled) return;
	if (Prosecutor != NULL && Prosecutor->RunningMission != this) Prosecutor = NULL;
	if (Priority <= 0) Enabled = false;
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
	Circle(ConvertVec2ToVec2(Position), 50 * getZoom()).drawFrame(1 * getZoom(), 0, HSV(IFF));
	Circle(ConvertVec2ToVec2(Position), (Priority * 5) * getZoom()).draw(HSV(IFF));

}

bool Mission::set(Vec2 position, double angle, int iff, Platoon* platoon, int priority)
{
	if (Enabled) return false;
	Enabled = true;
	Position = position;
	Angle = Vec2(1, 0);
	if (iff == 0) Angle = Vec2(-1, 0);
	Angle.rotate(angle);
	IFF = iff;
	Prosecutor = platoon;
	Priority = priority;
	for (auto& connect : Connects)
		connect = NULL;
	//Ú‘±æ‚ðì¬
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