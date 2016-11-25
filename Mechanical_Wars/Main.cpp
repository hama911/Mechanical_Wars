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