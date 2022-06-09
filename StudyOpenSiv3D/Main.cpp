# include <Siv3D.hpp> // OpenSiv3D v0.6.4

void Main()
{
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);
	Scene::SetBackground(Palette::Cyan);

	int32 count = 0;

	Array<Vec2> points;
	Array<Circle> circles;

	constexpr RectF window{ 0, 0, 800, 600 };
	
	window.draw(Palette::Gray);

	// 敵描画
	for (int32 i = 0; i < 5; i++) {
		Vec2 point = RandomVec2(window);
		points << point;
		circles << Circle{point, 10};
	}

	while (System::Update())
	{
		// Player描画
		Circle player{ Cursor::Pos(), 20 };
		player.draw(Palette::Red);

		for (auto& circle : circles) {
			circle.draw();
		}

		circles.remove_if([&](Circle c) {return player.intersects(c); });


		// 

		const double t = Scene::Time();

		if (MouseL.pressed()) {
			for (auto i : step(6))
			{
				// 円座標系における角度座標
				// 60° ごとに配置し、毎秒 30° の速さで回転する
				const double theta = (i * 60_deg + t * 30_deg);

				const Vec2 pos = OffsetCircular{ Cursor::Pos(), 200, theta };

				Circle{ pos, 20 }.draw(ColorF{ 0.25 });
			}
		}

		

		// Exit
		if (SimpleGUI::Button(U"Exit", Vec2{ 640, 40 }))
		{
			System::Exit();
		}
	}
}
