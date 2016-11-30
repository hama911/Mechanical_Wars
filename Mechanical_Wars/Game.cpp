# include "Game.h"
#include "Bullet.h"
#include "Unit.h"
#include "Motion.h"
#include "Graphics.h"
#include"Facility.h"
#include"Platoon.h"
Array<Bullet> bullets;
Array<Unit> units;
Array<Motion> motions;
Array<Facility> facilities;
Array<Platoon> platoons;
Platoon* SelectedPlatoon = NULL;
int FriendIFF = 0;
void Game::update()
{
	if (Input::MouseL.clicked)
	{
		++m_data->counter;
		changeScene(L"Result");
	}
	for (auto& facility : facilities)
		facility.update();
	for (auto& platoon : platoons)
		platoon.update();
	for (auto& unit : units)
		unit.update();
	for (auto& bullet : bullets)
		bullet.update();
	for (auto& motion : motions)
		motion.update();
	drawUpdate();

	if (Input::MouseL.clicked)
	{
		for (auto& platoon : platoons)
			if (platoon.Enabled && platoon.LeaderUnit->IFF == FriendIFF && platoon.getLeaderInfo()->Position.distanceFrom(DisConvertVec2ToVec2(Mouse::Pos())) < 16) SelectedPlatoon = &platoon;
	}

	if (Input::MouseR.clicked&&SelectedPlatoon != NULL&&SelectedPlatoon->Enabled)
		SelectedPlatoon->TargetPosition = DisConvertVec2ToVec2(Mouse::Pos());
	if (Input::MouseR.pressed && SelectedPlatoon != NULL&&SelectedPlatoon->Enabled)
		SelectedPlatoon->TargetAngle = (DisConvertVec2ToVec2(Mouse::Pos()) - SelectedPlatoon->TargetPosition).normalized();
}

void Game::draw() const
{

	Window::ClientRect().draw(Palette::Black);
	ground.resize(1024 * getZoom(), 1024 * getZoom()).draw(ConvertVec2ToPoint(Vec2(0, 0)));
	Rect(ConvertVec2ToPoint(Vec2(0, 0)), Point(1024 * getZoom(), 1024 * getZoom())).drawFrame(10 * getZoom(), 0, Palette::White);
	for (auto& facility : facilities)
		facility.draw();
	for (auto& platoon : platoons)
		platoon.draw();
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
			(noise.octaveNoise0_1(v.x, v.y, 0.0, 4) + 1)*0.09,
			(noise.octaveNoise0_1(v.x, v.y, 0.0, 4) + 1)*0.06,
			(noise.octaveNoise0_1(v.x, v.y, 0.0, 4) + 1)*0.03);
	}));


	drawInit();



	for (int i = 0; i < 1000; i++)
		facilities.push_back(Facility());
	for (int i = 0; i < 1000; i++)
		units.push_back(Unit());
	for (int i = 0; i < 1000; i++)
		motions.push_back(Motion());
	for (int i = 0; i < 1000; i++)
		bullets.push_back(Bullet());
	for (int i = 0; i < 1000; i++)
		platoons.push_back(Platoon());

	//工場のセット
	for (auto& facility : facilities)
		if (facility.set(240, 768, 512, 0)) break;
	for (auto& facility : facilities)
		if (facility.set(0, 256, 512, 0)) break;
	for (auto& facility : facilities)
		if (facility.set(240, 768, 256, 1)) break;
	for (auto& facility : facilities)
		if (facility.set(0, 256, 768, 1)) break;

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