#pragma once

# include <Siv3D.hpp>
#include"Turret.h"

#define MAX_TURRET 10

class Bullet;
class Division;

class Unit : public Calculation
{
public:
	Unit() { Enabled = false; }


	void update();	//初期化
	void draw() const;	//描画
	void addDamege(Bullet* bullet);
	void mountTurret();
	bool setUnit(int IFF_p, int type, Vec2 position = Vec2(Random(1024), Random(1024)));
	void reset();
	bool hitCheck(Vec2 pos);
	Vec2 getSpeedVec2();	//現在のスピードをVec2型で返す
	double getSpeedDouble();	//現在のスピードをdouble型で返す
	void setUnitData();
	void drawUnit() const;
	void turnUpdate();	//角度
	void shot();
	void limitMoving();
	bool isSupplyUnit();

public:
	//変数
	Division* AssignedDivision = NULL;
	bool Enabled;
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetPosition;
	int IFF;	//識別コード
	double Health;	//耐久
	Unit* Target;
	//固定数値
	double SpeedPerformance;	//速度性能
	double TurningPerformance;	//旋回性能
	double HealthPerformance;	//耐久性能
	int Type;

	//補給
	double Supply;	//補給量
	double Fuel;	//燃料
	double SupplyMax;
	double FuelMax;

	Turret turrets[MAX_TURRET];

};
