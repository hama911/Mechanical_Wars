# include "Main.h"
# include "Game.h"

class Title : public MyApp::Scene
{
public:

	void update() override
	{
		if (Input::MouseL.clicked)
		{
			++m_data->counter;
			changeScene(L"Game");
		}

	}

	void draw() const override
	{
		Window::ClientRect().draw(Palette::Blue);
		m_data->font(L"TITLE:", m_data->counter).drawCenter(Window::Center());
	}
};


class Result : public MyApp::Scene
{
public:

	void update() override
	{
		if (Input::MouseL.clicked)
		{
			++m_data->counter;
			changeScene(L"Title");
		}
	}

	void draw() const override
	{
		Window::ClientRect().draw(Palette::Green);
		m_data->font(L"RESULT:", m_data->counter).drawCenter(Window::Center());
	}
};

void Main()
{
	//リソース
	TextureAsset::Register(L"T-34_Chassis", L"T-34 Chassis.png");
	TextureAsset::Register(L"T-34_Turret", L"T-34 Turret.png");
	TextureAsset::Register(L"Ratte_Chassis", L"Ratte Chassis.png");
	TextureAsset::Register(L"Ratte_Turret", L"Ratte Turret.png");
	TextureAsset::Register(L"Ratte_Turret2", L"Ratte Turret2.png");
	TextureAsset::Register(L"Effect1", L"Effect1.png");
	TextureAsset::Register(L"Effect2", L"Effect2.png");
	TextureAsset::Register(L"Supply_Truck", L"SupplyTruck.png");
	SoundAsset::Register(L"cannon1", L"sound_cannon1.mp3");
	SoundAsset::Register(L"cannon2", L"sound_cannon2.mp3");
	SoundAsset::Register(L"explosive1", L"sound_explosive1.mp3");
	SoundAsset::Register(L"explosive2", L"sound_explosive2.mp3");


	Window::Resize(1280, 768, true);
	MyApp manager;

	//manager.add<Title>(L"Title");
	manager.add<Game>(L"Game");
	//manager.add<Result>(L"Result");
	while (System::Update())
	{
		manager.updateAndDraw();
	}
}