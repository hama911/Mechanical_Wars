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
	TextureAsset::Register(L"fact0",		L"/1000");
	TextureAsset::Register(L"fact1",		L"/1001");
	TextureAsset::Register(L"T-34_Chassis", L"/1002");
	TextureAsset::Register(L"T-34_Turret",	L"/1003");
	TextureAsset::Register(L"Ratte_Chassis",L"/1004");
	TextureAsset::Register(L"Ratte_Turret", L"/1005");
	TextureAsset::Register(L"Ratte_Turret2",L"/1006");
	TextureAsset::Register(L"Effect1",		L"/1007");
	TextureAsset::Register(L"Effect2",		L"/1008");
	TextureAsset::Register(L"Supply_Truck", L"/1009");
	TextureAsset::Register(L"Rifle",		L"/1010");
	TextureAsset::Register(L"Soldier",		L"/1011");
	SoundAsset::Register(L"cannon1",		L"/1012");
	SoundAsset::Register(L"cannon2",		L"/1013");
	SoundAsset::Register(L"explosive1",		L"/1014");
	SoundAsset::Register(L"explosive2",		L"/1015");
	SoundAsset::Register(L"shot1",			L"/1016");
	SoundAsset::Register(L"engine",			L"/1017");
	SoundAsset::Register(L"engine2",		L"/1018");
	SoundAsset::Register(L"pom",			L"/1019");

	Window::Resize(1280, 720);
	//Window::SetFullscreen(true,Size(1920,1080));
	Window::SetTitle(L"Mechanical Wars開発版 @LPC1768_");
	MyApp manager;

	//manager.add<Title>(L"Title");
	manager.add<Game>(L"Game");
	//manager.add<Result>(L"Result");
	while (System::Update())
	{
		manager.updateAndDraw();
	}
}