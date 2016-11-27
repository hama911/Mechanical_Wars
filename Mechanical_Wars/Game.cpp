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
	for (auto& unit : units)
		unit.update();
	for (auto& bullet : bullets)
		bullet.update();
	for (auto& motion : motions)
		motion.update();
	drawUpdate();


}

void Game::draw() const
{

	Window::ClientRect().draw(Palette::Black);
	ground.resize(1024*getZoom(),1024*getZoom()).draw(ConvertVec2ToPoint(Vec2(0,0)));
	Rect(ConvertVec2ToPoint(Vec2(0, 0)), Point(1024 * getZoom(), 1024 * getZoom())).drawFrame(10 * getZoom(), 0, Palette::White);
	for (auto& unit : units)
		unit.draw();
	for (auto& bullet : bullets)
		bullet.draw();
	for (auto& motion : motions)
		motion.draw();


}


void Game::init()
{
	PerlinNoise noise(11111);

	ground = Texture(Image(1024, 1024, [&noise](const Point pos)
	{
		const Vec2 v(pos.x * 0.5, pos.y * 0.5);
		return ColorF(
			(noise.octaveNoise0_1(v.x, v.y, 0.0, 4)+1)*0.09,
			(noise.octaveNoise0_1(v.x, v.y, 0.0, 4)+1)*0.06,
			(noise.octaveNoise0_1(v.x, v.y, 0.0, 4)+1)*0.03);
	}));


	drawInit();

	for (int i = 0; i < 100; i++)
		units.push_back(Unit(0, 0));
	for (int i = 0; i < 100; i++)
		units.push_back(Unit(120, 0));
	for (int i = 0; i < 100; i++)
		units.push_back(Unit(240, 0));
	for (int i = 0; i < 0; i++)
		units.push_back(Unit(0, 1));
	for (int i = 0; i < 0; i++)
		units.push_back(Unit(120, 1));
	for (int i = 0; i < 0; i++)
		units.push_back(Unit(240, 1));
}

void Game::updateFadeIn(double)
{
	update();
}

void Game::refreshArray()
{
	Erase_if(units, [](const Unit& unit) {return !unit.getEnabled(); });
	Erase_if(bullets, [](const Bullet& bullet) {return !bullet.getEnabled(); });
	Erase_if(motions, [](const Motion& motion) {return !motion.getEnabled(); });
}