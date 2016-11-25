#pragma once

# include <Siv3D.hpp>
#include"Turret.h"

class Unit
{
public:
	Unit();
	Unit(int IFF_p);
	~Unit();

	bool update();	//初期化
	void draw() const;	//描画

	void addDamege(double value);

	//初期化
	void mountTurret();

	Vec2 getPosition();
	Vec2 getAngle();
	int getIFF();
	double getSpeedPerformance();


private:

	//移動系
	void moveForward(double length);	//距離
	void moveBack(double length);		//距離

	//回転系
	void turnUpdate();	//角度

	//攻撃系
	void shot();

	//制限
	void limitMoving();



	//変数
	int Heat;	//射撃クールダウン
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetAngle;
	int IFF;	//識別コード
	double Health;	//体力

	//固定数値
	double SpeedPerformance;	//速度性能
	double TurningPerformance;	//旋回性能

	Array<Turret> turrets;

};
