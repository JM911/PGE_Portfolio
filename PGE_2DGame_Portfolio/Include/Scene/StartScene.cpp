#include "StartScene.h"
#include "../Core.h"
#include "Stage_1.h"

StartScene::StartScene(Core* pEngine) :
	Scene(pEngine)
{
	srand((unsigned int)time(nullptr));

	for (int i = 0; i < 10; i++)
	{
		_cirY[i] = -100.f;
	}
}

StartScene::~StartScene()
{
}

void StartScene::Update()
{
	// 커서 움직임
	if (_pEngine->GetKey(olc::Key::UP).bPressed)
	{
		_cursorY = 202;
		_menu = SCENE_MENU::START;
	}
	if (_pEngine->GetKey(olc::Key::DOWN).bPressed)
	{
		_cursorY = 252;
		_menu = SCENE_MENU::EXIT;
	}


	// 메뉴 선택
	if (_pEngine->GetKey(olc::Key::SPACE).bReleased)
	{
		Stage_1* pNextScene = new Stage_1(_pEngine);
		pNextScene->Create();

		switch (_menu)
		{
		case SCENE_MENU::START:
			_pEngine->SetNextScene(pNextScene);
			break;
		case SCENE_MENU::EXIT:
			delete pNextScene;
			_pEngine->Exit();
			break;
		}
	}

	CreateRandomCircle();
	UpdateRandomCircle();
}

void StartScene::Render()
{
	// Clear
	_pEngine->Clear(olc::BLACK);

	_pEngine->DrawString(80, 100, "Circle Invaders", olc::WHITE, 4);

	// deco
	_pEngine->DrawCircle(0, 230, 100);
	_pEngine->DrawCircle(640, 320, 100);
	_pEngine->DrawCircle(500, 0, 50);

	// deco2
	RenderRandomCircle();

	// 메뉴 렌더
	_pEngine->DrawString(230, 200, "Game Start", olc::WHITE, 2);
	_pEngine->DrawString(230, 250, "Exit", olc::WHITE, 2);

	_pEngine->FillTriangle(_cursorX, _cursorY, _cursorX, _cursorY + 10, _cursorX + 10, _cursorY + 5);

}

void StartScene::CreateRandomCircle()
{
	float elapsedTime = _pEngine->GetElapsedTime();
	_timeTick += elapsedTime;

	if (_cirY[_curCirIdx] > -50.f)
		return;

	if (_timeTick < _interval)
		return;

	_timeTick = 0.f;
	_interval = float(rand() % 200) * 0.01f + 1.f;

	_cirX[_curCirIdx] = float(rand() % 440) + 100.f;
	_cirY[_curCirIdx] = 400.f;

	_cirSize[_curCirIdx] = rand() % 15 + 10;
	_cirSpeed[_curCirIdx] = float(rand() % 20) + 20.f;

	_cirColor[_curCirIdx].r = rand() % 255;
	_cirColor[_curCirIdx].g = rand() % 255;
	_cirColor[_curCirIdx].b = rand() % 255;

	// 다음 인덱스
	_curCirIdx++;
	if (_curCirIdx >= 10)
		_curCirIdx = 0;
}

void StartScene::UpdateRandomCircle()
{
	float elapsedTime = _pEngine->GetElapsedTime();

	for (int i = 0; i < 10; i++)
	{
		_cirY[i] -= _cirSpeed[i] * elapsedTime;
	}
}

void StartScene::RenderRandomCircle()
{
	for (int i = 0; i < 10; i++)
	{
		_pEngine->DrawCircle((int)_cirX[i], (int)_cirY[i], _cirSize[i], _cirColor[i]);
	}
}
