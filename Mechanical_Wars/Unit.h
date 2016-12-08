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


	void update();	//������
	void draw() const;	//�`��
	void addDamege(Bullet* bullet);
	void mountTurret();
	bool setUnit(int IFF_p, int type, Vec2 position = Vec2(Random(1024), Random(1024)));
	void reset();
	bool hitCheck(Vec2 pos);
	Vec2 getSpeedVec2();	//���݂̃X�s�[�h��Vec2�^�ŕԂ�
	double getSpeedDouble();	//���݂̃X�s�[�h��double�^�ŕԂ�
	void setUnitData();
	void drawUnit() const;
	void turnUpdate();	//�p�x
	void shot();
	void limitMoving();
	bool isSupplyUnit();

public:
	//�ϐ�
	Division* AssignedDivision = NULL;
	bool Enabled;
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetPosition;
	int IFF;	//���ʃR�[�h
	double Health;	//�ϋv
	Unit* Target;
	//�Œ萔�l
	double SpeedPerformance;	//���x���\
	double TurningPerformance;	//���񐫔\
	double HealthPerformance;	//�ϋv���\
	int Type;

	//�⋋
	double Supply;	//�⋋��
	double Fuel;	//�R��
	double SupplyMax;
	double FuelMax;

	Turret turrets[MAX_TURRET];

};
