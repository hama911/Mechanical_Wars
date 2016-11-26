# include "Game.h"
#include "Bullet.h"
#include "Unit.h"
#include "Motion.h"
#include "Graphics.h"

Array<Bullet> bullets;
Array<Unit> units;
Array<Motion> motions;

void Game::update()
{
	if (Input::MouseL.clicked)
	{
		++m_data->counter;
		changeScene(L"Result");
	}
	Erase_if(units, [](Unit &unit) {
		return unit.update();
	});
	Erase_if(bullets, [](Bullet &bullet) {
		return bullet.update();
	});
	Erase_if(motions, [](Motion &motion) {
		return motion.update();
	});
	drawUpdate();
}

void Game::draw() const
{
	Window::ClientRect().draw(Palette::Black);
	for (auto& unit : units)
		unit.draw();
	for (auto& bullet : bullets)
		bullet.draw();
	for (auto& motion : motions)
		motion.draw();

	Rect(ConvertVec2ToPoint(Vec2(0,0)),Point(1024*getZoom(),1024*getZoom())).drawFrame(10 * getZoom(), 0, Palette::White);
}


void Game::init()
{
	drawInit();
	for (int i = 0; i < 20; i++)
	{
		units.push_back(Unit(0, 0));
	}
	for (int i = 0; i < 20; i++)
	{
		units.push_back(Unit(240, 0));
	}
	for (int i = 0; i < 20; i++)
	{
		units.push_back(Unit(120, 0));
	}
	for (int i = 0; i < 5; i++)
	{
		units.push_back(Unit(0, 1));
	}
	for (int i = 0; i < 5; i++)
	{
		units.push_back(Unit(240, 1));
	}
	for (int i = 0; i < 5; i++)
	{
		units.push_back(Unit(120, 1));
	}
}

void Game::updateFadeIn(double)
{
	update();
}