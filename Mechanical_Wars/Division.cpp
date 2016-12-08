#include"Division.h"
#include"Graphics.h"
#include"Unit.h"
#include"Mission.h"

extern Array<Mission> missions;

void Division::update()
{
	if (!Enabled) return;
	// 整合性チェック
	for (auto& memberUnit : MemberUnits)
		if (memberUnit != NULL && memberUnit->AssignedDivision != this) memberUnit = NULL;
	findMission();
	if (!Enabled) return;
	rushEnemyMission();
	relocate();
}

void Division::reset()
{
	Enabled = false;
	TargetMission = NULL;
	for (auto& memberUnit : MemberUnits)
	{
		if (memberUnit == NULL) continue;
		memberUnit->AssignedDivision = NULL;
		memberUnit = NULL;
	}
	if (InProcessMission != NULL)
	{
		InProcessMission->ActiveDivision = NULL;
		InProcessMission = NULL;
	}
	IFF = 0;
}
Mission* Division::getFriendlyMission(bool Right) const
{
	if (!Enabled) return NULL;
	if (InProcessMission == NULL) return NULL;	//もし実行できないなら
	if (InProcessMission->BAL != 0) return NULL;	//戦闘地域でない
	Mission* FriendlyMission = NULL;

	for (auto& connect : InProcessMission->Connects)
	{
		if (connect != NULL && connect->IFF == IFF)
		{
			for (auto& mission1 : connect->Connects)
			{
				if (mission1 != NULL && mission1->IFF != IFF)
				{
					for (auto& mission2 : InProcessMission->Connects)
					{
						if (mission1 == mission2)	//隣接したミッション
						{
							if (FriendlyMission != NULL && FriendlyMission != connect) return connect;
							if (Right) return connect;
							FriendlyMission = connect;
							break;
						}
					}
				}
			}
		}
	}
	return NULL;	//片方しかない場合
}

void Division::leaveDivision(Unit* unit)
{
	for (auto& memberUnit : MemberUnits)
	{
		if (memberUnit == unit) {
			memberUnit->AssignedDivision = NULL;
			memberUnit = NULL;
			return;
		}
	}

	LOG_ERROR(L"Division::leaveDivision() unit is not found in Division");
}

void Division::rushEnemyMission()
{
	TargetMission = NULL;
	//エラー処理
	if (!Enabled) { LOG_ERROR(L"Division::rushEnemyMission() Enabled is false"); return; }
	if (getNumMemberUnit() == 0) return;
	if (InProcessMission == NULL) return;	//ミッションに所属していない
	if (InProcessMission->BAL != 0) return;	//ミッションが戦闘状態ではない
	if (getPosition().distanceFrom(InProcessMission->Position) > 96) return;	//自分が遠すぎ
	int NumEnemyUnit = 100;
	for (auto& connect : InProcessMission->Connects)
	{
		if (connect != NULL && connect->IFF != IFF)
		{
			if (connect->ActiveDivision == NULL)
			{
				TargetMission = connect;
				for (auto& memberUnit : MemberUnits)
				{
					if (memberUnit != NULL && memberUnit->Position.distanceFrom(connect->Position) < 96) {
						TargetMission = NULL;
						connect->ActiveDivision = this;
						InProcessMission->ActiveDivision = NULL;
						InProcessMission = connect;
						connect->IFF = IFF;
					}
				}
			}
			else
			{
				/*
				if (connect->ActiveDivision->getNumMemberUnit() < NumEnemyUnit)
				{
					NumEnemyUnit = connect->ActiveDivision->getNumMemberUnit();
					TargetMission = connect;
				}*/
			}
		}
	}

}

void Division::receiveSupply(Unit* unit)
{

	//エラー処理
	if (!Enabled) { LOG_ERROR(L"Division::receiveSupply() Enabled is false"); return; }


	if (getNumSupplyUnit() == 0) return;	//補給できるユニットがない場合
	//Supplyの補給処理
	for (auto& memberUnit : MemberUnits)
	{
		if (memberUnit != NULL && memberUnit->isSupplyUnit() && getPosition().distanceFrom(memberUnit->Position) < 64)
		{
			if (memberUnit->Supply > unit->SupplyMax - unit->Supply)
			{
				memberUnit->Supply -= unit->SupplyMax - unit->Supply;
				unit->Supply = unit->SupplyMax;
				break;
			}
			else
			{
				unit->Supply += memberUnit->Supply;
				memberUnit->Supply = 0;
			}
		}
	}

	//Fuelの補給処理
	for (auto& memberUnit : MemberUnits)
	{
		if (memberUnit != NULL && memberUnit->isSupplyUnit() && getPosition().distanceFrom(memberUnit->Position) < 64)
		{
			if (memberUnit->Fuel > unit->FuelMax - unit->Fuel)
			{
				memberUnit->Fuel -= unit->FuelMax - unit->Fuel;
				unit->Fuel = unit->FuelMax;
				break;
			}
			else
			{
				unit->Fuel += memberUnit->Fuel;
				memberUnit->Fuel = 0;
			}
		}
	}

}

bool Division::canJoinDivision(Unit* unit) const
{
	if (!Enabled || IFF != unit->IFF || getNumMemberUnit() == DIVISION_MAX_MEMBER) return false;
	if (!unit->isSupplyUnit() && getNumSupplyUnit() == 0 && getNumMemberUnit() == DIVISION_MAX_MEMBER - 1) return false;
	if (getNumSupplyUnit() > 0 && unit->isSupplyUnit()) return false;
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
			if (InProcessMission == NULL) InProcessMission = &mission;
			if (mission.BAL == 0)
				InProcessMission = &mission;
		}
	}
	if (InProcessMission != NULL)
	{
		if (InProcessMission->BAL != 0) { reset(); return; }
		InProcessMission->ActiveDivision = this;
	}
}

bool Division::set(int iff)
{
	if (Enabled) return false;
	Enabled = true;
	IFF = iff;
	for (auto& memberUnit : MemberUnits)
		memberUnit = NULL;
	InProcessMission = NULL;
	TargetMission = NULL;
	findMission();
	return true;
}

void Division::JoinDivision(Unit* unit)
{


	if (!Enabled)
	{
		LOG_ERROR(L"Division::JoinDivision() Enabled is false");
		return;
	}
	if (IFF != unit->IFF)
	{
		LOG_ERROR(L"Division::JoinDivision() IFF is not unit->IFF");
		return;
	}


	for (auto& memberUnit : MemberUnits)
	{
		if (memberUnit != NULL) continue;
		memberUnit = unit;
		unit->AssignedDivision = this;
		return;
	}


	LOG_ERROR(L"Division::JoinDivision() Over member capacity");


}


void Division::relocate()
{
	//最も近いものに設定
	Unit* target = NULL;
	double distance = 0xFFFFFF;
	if (InProcessMission != NULL)
	{
		for (auto& memberUnit : MemberUnits)
		{
			if (memberUnit != NULL && !memberUnit->isSupplyUnit() && memberUnit->Position.distanceFrom(InProcessMission->Position) < distance)
			{
				distance = memberUnit->Position.distanceFrom(InProcessMission->Position);
				target = memberUnit;
			}
		}
		if (target != NULL)
		{
			for (auto& memberUnit : MemberUnits)
			{
				if (target == memberUnit)
				{
					memberUnit = MemberUnits[0];
				}
			}
			MemberUnits[0] = target;
		}
	}

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



	Println(L"Division::getPosition()　No MemberUnit");
	return Vec2(0, 0);

}
Unit* Division::getLeader() const
{
	for (auto& memberUnit : MemberUnits)
		if (memberUnit != NULL) return memberUnit;


	LOG_ERROR(L"Division::getLeader()　No MemberUnit");
	return NULL;



}

Vec2 Division::getTargetPosition(Unit* unit) const
{
	if (unit == NULL)
	{
		if (getLeader() != NULL) return getLeader()->Position;

		LOG_ERROR(L"Division::getTargetPosition()　No MemberUnit");
		return Vec2(0, 0);

	}
	else
	{
		if (unit->isSupplyUnit() && MemberUnits[0]!=unit)
		{
			return MemberUnits[0]->Position - getTargetAngle() * 32;
		}
		for (int i = 0; i < DIVISION_MAX_MEMBER; i++)
		{
			if (MemberUnits[i] != unit) continue;

			//リーダー
			if (i == 0)
			{
				if (unit->isSupplyUnit()) return unit->Position;
				if (TargetMission == NULL)
				{
					if (InProcessMission != NULL) return InProcessMission->Position;
					return unit->Position;	//所属しているミッションがないなら
				}
				else
				{
					return (TargetMission->Position + InProcessMission->Position) / 2;
				}
			}
			if (InProcessMission != NULL && InProcessMission->Position.distanceFrom(getPosition()) < 64)
			{
				Mission* targetMission = getFriendlyMission(i % 2 == 1);
				if (i % 2)
				{
					if (targetMission == NULL) return InProcessMission->Position + i * getUnitInterval() * getTargetAngle().rotated(HalfPi);
					return InProcessMission->Position + i * getUnitInterval() * (targetMission->Position - InProcessMission->Position).normalized();
				}
				else
				{
					if (targetMission == NULL)
					{
						Mission* targetMission2 = getFriendlyMission(1);
						if (targetMission2 != NULL) return InProcessMission->Position - i * getUnitInterval() * (targetMission2->Position - InProcessMission->Position).normalized();
						return InProcessMission->Position - i * getUnitInterval() * getTargetAngle().rotated(HalfPi);
					}
					return InProcessMission->Position + i * getUnitInterval() * (targetMission->Position - InProcessMission->Position).normalized();
				}
			}
			else
			{
				if (i % 2)
				{
					return getPosition() + i * getUnitInterval() * getLeader()->Angle;
				}
				else
				{
					return getPosition() - i * getUnitInterval() * getLeader()->Angle;

				}

			}

		}
	}


	LOG_ERROR(L"Division::getTargetPosition()　unit isn't MemberUnit");
	return Vec2(0, 0);


}

double Division::getUnitInterval() const
{


	if (!Enabled) LOG_ERROR(L"Division::getUnitInterval() Enabled is false");
	if (getNumMemberUnit() == 0) LOG_ERROR(L"Division::getUnitInterval() no member unit");


	return 64.0 / double(getNumMemberUnit());
}

Vec2 Division::getTargetAngle() const
{
	if (TargetMission != NULL) return (TargetMission->Position - getPosition()).normalized();
	if (InProcessMission == NULL) return Vec2(1, 0);
	if (InProcessMission->Position.distanceFrom(getLeader()->Position) < 64) return InProcessMission->getAngle();
	return (InProcessMission->Position - getPosition()).normalized();
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