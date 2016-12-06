#pragma once

# include <Siv3D.hpp>
#include"Turret.h"

#define MAX_TURRET 10

class Platoon;

class Unit : public Calculation
{
public:
	Unit() { Enabled = false; }


	void update();	//初期化
	void draw() const;	//描画

	void addDamege(double value);

	//初期化
	void mountTurret();

	void updatePlatoon();

	bool setUnit(int IFF_p, int type, Vec2 position = Vec2(Random(1024), Random(1024)));
	void reset();


	bool hitCheck(Vec2 pos);


public:	//内部データにアクセス
	int getMotionType() const;

	Vec2 getSpeedVec2() const;	//現在のスピードをVec2型で返す
	double getSpeedDouble() const;	//現在のスピードをdouble型で返す

public:
	//個別データ
	void updateUnit();
	void setUnitData();
	void drawUnit() const;



	//回転系
	void turnUpdate();	//角度

	//攻撃系
	void shot();

	//制限
	void limitMoving();

public:
	//変数
	bool Enabled;
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetPosition;
	int IFF;	//識別コード
	double Health;	//耐久
	Unit* Target;	
	Platoon* MyPlatoon;

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
