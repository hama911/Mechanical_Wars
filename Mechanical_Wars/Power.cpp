#include"Power.h"
#include"Mission.h"
#include"Unit.h"
#include"Division.h"
extern Array<Division> divisions;
extern Array<Mission> missions;
void Power::update()
{
	if (!Enabled) return;
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
			int need = division.getNumMemberUnit() / 10 + 1 - division.getNumSupplyUnit();
			if (need > 0) NeedUnits[2] += need;	//10ëÃÇ…ÇPÇ¬íçï∂
			++count;
		}
	}

	if (count == 0) {
		for (auto& division : divisions)
			if (division.set(IFF)) break;
	}
}