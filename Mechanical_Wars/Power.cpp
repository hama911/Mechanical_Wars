#include"Power.h"
#include"Mission.h"
#include"Platoon.h"
#include"Unit.h"
extern Array<Mission> missions;
extern Array<Platoon> platoons;
void Power::update()
{
	if (!Enabled) return;
	FindFreeMission();
	FindNeedUnits();
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
		if (!platoon.Enabled || platoon.LeaderUnit->IFF != IFF) continue;
		if (platoon.SupplyUnit == NULL) ++NeedUnits[2];	//•â‹‹ƒgƒ‰ƒbƒN
		NeedUnits[0] += MAX_MEMBER - platoon.getTotalMember() - (platoon.SupplyUnit == NULL);
	}
	if (FreeMission)
	{
		NeedUnits[0] += 5;
		NeedUnits[1] += 1;
	}
}