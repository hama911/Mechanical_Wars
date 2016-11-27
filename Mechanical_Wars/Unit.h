#pragma once

# include <Siv3D.hpp>
#include"Turret.h"

#define MAX_TURRET 10

class Platoon;

class Unit : public Calculation
{
public:
	Unit(int IFF_p = 0, int type = 0, Vec2 position = Vec2(Random(1024), Random(1024)));
	~Unit();

	void update();	//������
	void draw() const;	//�`��

	void addDamege(double value);

	//������
	void mountTurret();
	void setEnabled(bool enabled);

	void updatePlatoon();

	void resetUnit(int IFF_p, int type, Vec2 position = Vec2(Random(1024), Random(1024)));

	Vec2 getPosition() const;
	Vec2 getAngle() const;
	int getIFF() const;
	bool getEnabled() const;
	double getSpeedPerformance() const;
	int getMotionType() const;

	bool hitCheck(Vec2 pos);

	void setPlatoon(Platoon* platoon);

private:
	//�ʃf�[�^
	void setUnitData();
	void drawUnit() const;


	//�ړ��n
	void moveForward(double length);	//����
	void moveBack(double length);		//����

	//��]�n
	void turnUpdate();	//�p�x

	//�U���n
	void shot();

	//����
	void limitMoving();

	//�ϐ�
	bool Enabled;
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetAngle;
	int IFF;	//���ʃR�[�h
	double Health;	//�ϋv

	Platoon* MyPlatoon;

	//�Œ萔�l
	double SpeedPerformance;	//���x���\
	double TurningPerformance;	//���񐫔\
	double HealthPerformance;	//�ϋv���\
	int Type;

	Turret turrets[MAX_TURRET];

};
