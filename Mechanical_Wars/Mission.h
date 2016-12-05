#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

/*
小隊に対し任務を指定する

*/

class Platoon;

class Mission : public Calculation
{
public:
	Mission() { Enabled = false; }


	bool set(Vec2 position, int iff, Platoon* platoon = NULL, int priority = 1);
	void update();
	void draw() const;
	bool getBattleFlag();	//戦闘中か
	void setBAL();

public:

	int BAL;		//戦闘地域レベル
	bool Enabled;
	Vec2 Position;	//ミッションの位置
	Vec2 Angle;		//ミッションの向く方向
	int IFF;		//制圧しているIFF(-で無所属を示す)
	Mission* Connects[10];	//接続しているミッション(10個まで指定可能)
	Platoon* Prosecutor;	//任務を請け負う小隊
	int Priority;	//優先度
private:

};