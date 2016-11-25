#pragma once

# include <Siv3D.hpp>
# include <HamFramework.hpp>

struct CommonData
{
	int counter = 0;
	Font font{ 50 };
};

using MyApp = SceneManager<String, CommonData>;