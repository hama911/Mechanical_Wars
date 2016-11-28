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

	void setUnit(int IFF_p, int type, Vec2 position = Vec2(Random(1024), Random(1024)));
	void reset();


	bool hitCheck(Vec2 pos);


public:	//内部データにアクセス
	Vec2 getPosition() const { return Position; }
	Vec2 getAngle() const { return Angle; }
	int getIFF() const { return IFF; }
	bool getEnabled() const { return Enabled; }
	double getSpeed() const { return Speed; }
	Platoon* getPlatoon()const { return MyPlatoon; }
	int getMotionType() const;

	void setEnabled(bool enabled) { Enabled = enabled; }
	void setPlatoon(Platoon* platoon) { MyPlatoon = platoon; }

private:
	//個別データ
	void setUnitData();
	void drawUnit() const;


	//移動系
	void moveForward(double length);	//距離
	void moveBack(double length);		//距離

	//回転系
	void turnUpdate();	//角度

	//攻撃系
	void shot();

	//制限
	void limitMoving();

private:
	//変数
	bool Enabled;
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetAngle;
	int IFF;	//識別コード
	double Health;	//耐久
	double Speed;	//現在のスピード

	Platoon* MyPlatoon;

	//固定数値
	double SpeedPerformance;	//速度性能
	double TurningPerformance;	//旋回性能
	double HealthPerformance;	//耐久性能
	int Type;

	Turret turrets[MAX_TURRET];

};
