#include"Power.h"
#include"Mission.h"
#include"Unit.h"
#include"Division.h"
extern Array<Division> divisions;
extern Array<Mission> missions;
extern Array<Unit> units;
void Power::update()
{
	if (!Enabled) return;

	//Division‚Ì‘”‚ðŒvŽZ
	NumDivision = 0;
	for (auto& division : divisions)
		if (division.Enabled && division.IFF == IFF) ++NumDivision;
	for (auto& unit : NumFreeUnit)
		unit = 0;
	for (auto& unit : units)
		if (unit.Enabled && unit.IFF == IFF && unit.AssignedDivision == NULL) ++NumFreeUnit[unit.Type];

	//Mission‚Ì‘”‚ðŒvŽZ(BAL‚²‚Æ‚É)
	for (auto& mission : NumMission)
		mission = 0;
	for (auto& mission : missions)
		if (mission.IFF == IFF && mission.Enabled) ++NumMission[mission.BAL];

	FindNeedUnits();
}

void Power::draw() const
{

}


void Power::FindNeedUnits()
{
	for (auto& unit : NeedUnits)
		unit = 0;

	int count = 0;
	for (auto& division : divisions)
	{
		if (division.Enabled && division.IFF == IFF)
		{
			int need = 1 - division.getNumSupplyUnit();
			if (need > 0) NeedUnits[2] += need;	//10‘Ì‚É‚P‚Â’•¶
			++count;
		}
	}

	if (NumMission[0] > NumDivision)
	{
		for (auto& division : divisions)
			if (division.set(IFF)) break;
	}
}