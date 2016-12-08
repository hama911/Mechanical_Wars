#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

class Division;

void updateMissions();

class Mission : public Calculation
{
public:
	Mission() { Enabled = false; }


	bool set(Vec2 position, int iff);
	void update();
	void draw() const;
	void setBAL();

	Vec2 getAngle() const;

public:

	int BAL;		//戦闘地域レベル
	bool Enabled;
	Vec2 Position;	//ミッションの位置
	int IFF;		//制圧しているIFF(-で無所属を示す)
	Mission* Connects[10];	//接続しているミッション(10個まで指定可能)
	Division* ActiveDivision;
private:

};