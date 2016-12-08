# include "Game.h"
#include "Bullet.h"
#include "Unit.h"
#include "Motion.h"
#include "Graphics.h"
#include"Facility.h"
#include"Mission.h"
#include"Power.h"
#include"Division.h"
Array<Bullet> bullets;
Array<Unit> units;
Array<Motion> motions;
Array<Facility> facilities;
Array<Mission> missions;
Array<Power> powers;
Array<Division> divisions;
Mission* SelectedMission = NULL;

int FriendIFF = 0;
void Game::update()
{
	for (int i = 0; i < Speed; i++)
	{
		if (Input::MouseL.clicked)
		{
			++m_data->counter;
			changeScene(L"Result");
		}
		for (auto& power : powers)
			power.update();

		updateMissions();

		for (auto& facility : facilities)
			facility.update();

		for (auto& unit : units)
			unit.update();

		for (auto& division : divisions)
			division.update();

		for (auto& bullet : bullets)
			bullet.update();

		for (auto& motion : motions)
			motion.update();
	}
	drawUpdate();
	if (Input::KeyF1.clicked)
	{
		if (Speed <= 1) Speed = 0;
		else Speed /= 2;
	}
	if (Input::KeyF2.clicked)
	{
		if (Speed == 0) Speed = 1;
		else Speed *= 2;
	}
}


void Game::draw() const
{
	//Println(L"ダウンロードしていただき、ありがとうございます。");
	//Println(L"F1キーとF2キーで倍速の調整、マウスで視点移動が可能です。");

	Window::ClientRect().draw(Palette::Darkgreen);
	Rect(ConvertVec2ToPoint(Vec2(GROUND_LIMIT_MIN_X, GROUND_LIMIT_MIN_Y)), Point((GROUND_LIMIT_MAX_X - GROUND_LIMIT_MIN_X) * getZoom(), (GROUND_LIMIT_MAX_Y - GROUND_LIMIT_MIN_Y) * getZoom())).drawFrame(0, 5 * getZoom(), Palette::White);
	for (auto& power : powers)
		power.draw();
	for (auto& facility : facilities)
		facility.draw();
	for (auto& mission : missions)
		mission.draw();
	for (auto& division : divisions)
		division.draw();

	for (auto& unit : units)
		unit.draw();
	for (auto& bullet : bullets)
		bullet.draw();
	for (auto& motion : motions)
		motion.draw();


}


void Game::init()
{

	drawInit();



	for (int i = 0; i < 10; i++)
		facilities.push_back(Facility());
	for (int i = 0; i < 100; i++)
		units.push_back(Unit());
	for (int i = 0; i < 2000; i++)
		motions.push_back(Motion());
	for (int i = 0; i < 1000; i++)
		bullets.push_back(Bullet());
	for (int i = 0; i < 80; i++)
		missions.push_back(Mission());
	for (int i = 0; i < 360; i++)
		powers.push_back(Power(i));
	for (int i = 0; i < 100; i++)
		divisions.push_back(Division());
	powers[0].Enabled = true;
	powers[240].Enabled = true;
	powers[120].Enabled = true;

	/*
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 5; j++)
			for (auto& unit : units)
				if (unit.setUnit(240, 0, Vec2(700, 512))) break;
		for (auto& unit : units)
			if (unit.setUnit(240, 1, Vec2(700, 512))) break;
		for (auto& unit : units)
			if (unit.setUnit(240, 2, Vec2(700, 512))) break;
	}
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 5; j++)
			for (auto& unit : units)
				if (unit.setUnit(0, 0, Vec2(500, 512))) break;
		for (auto& unit : units)
			if (unit.setUnit(0, 1, Vec2(500, 512))) break;
		for (auto& unit : units)
			if (unit.setUnit(0, 2, Vec2(500, 512))) break;
	}*/




	//敵のMission
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 8; y++)
			for (auto& mission : missions)
				if ((x % 2) + y != 8 && mission.set(Vec2(x * 110 + 64, y * 128 + 64 + (x % 2) * 64), (240 * (x >= 8) + 120 * (x > 1 && x < 8)))) break;


	//工場のセット
	for (auto& facility : facilities)
		if (facility.set(&missions[5], 1)) break;
	for (auto& facility : facilities)
		if (facility.set(&missions[4], 0)) break;
	for (auto& facility : facilities)
		if (facility.set(&missions[73], 0)) break;
	for (auto& facility : facilities)
		if (facility.set(&missions[72], 1)) break;
	for (auto& facility : facilities)
		if (facility.set(&missions[30], 0)) break;
	for (auto& facility : facilities)
		if (facility.set(&missions[31], 1)) break;
}

void Game::updateFadeIn(double)
{
	update();
}

void Game::refreshArray()
{
	Erase_if(units, [](const Unit& unit) {return !unit.Enabled; });
	Erase_if(bullets, [](const Bullet& bullet) {return !bullet.Enabled; });
	Erase_if(motions, [](const Motion& motion) {return !motion.Enabled; });
}