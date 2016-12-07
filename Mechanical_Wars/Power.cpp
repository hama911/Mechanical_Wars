#include"Power.h"
#include"Mission.h"
#include"Platoon.h"
#include"Unit.h"
extern Array<Mission> missions;
extern Array<Platoon> platoons;
extern Array<Unit> units;
void Power::update()
{
	if (!Enabled) return;
	FindFreeMission();
	FindNeedUnits();

	//bal‚Ì‚»‚ê‚¼‚ê‚Ì”‚ğŒv‘ª
	for (int i = 0; i < 5; i++)
	{
		NumberOfBAL[i] = 0;
		for (auto& mission : missions)
			if (mission.Enabled && mission.IFF == IFF && mission.BAL == i) ++NumberOfBAL[i];
	}
	//platoon‚Ì‚»‚ê‚¼‚ê‚Ì”‚ğŒv‘ª
	for (int i = 0; i < 5; i++)
	{
		NumberOfPlatoonBAL[i] = 0;
		for (auto& platoon : platoons)
			if (platoon.Enabled && platoon.RunningMission != NULL && platoon.LeaderUnit->IFF == IFF && platoon.RunningMission->BAL == i) ++NumberOfPlatoonBAL[i];
	}
}

void Power::draw() const
{

}

void Power::FindFreeMission()
{
	FreeMission = false;
	for (auto mission : missions)
	{
		if (!mission.Enabled || mission.IFF != IFF || mission.Prosecutor != NULL) continue;
		for (auto connect : mission.Connects)
		{
			if (connect != NULL && connect->IFF != IFF)
			{
				FreeMission = true;
				return;
			}
		}
	}
	return;
}

void Power::FindNeedUnits()
{
	for (auto& unit : NeedUnits)
		unit = 0;
	for (auto& platoon : platoons)
	{
		if (platoon.Enabled && platoon.LeaderUnit->IFF == IFF)
		{
			++NeedUnits[2];
			NeedUnits[0] += MAX_MEMBER - 1;
		}
	}
	if (FreeMission)
	{
		NeedUnits[0] += 1;
	}
	NeedUnits[0] += 100;
	for (auto&unit : units)
	{
		if (!unit.Enabled || unit.IFF != IFF) continue;
		if (unit.Type == 2) NeedUnits[2]--;
		else NeedUnits[0]--;
	}
}