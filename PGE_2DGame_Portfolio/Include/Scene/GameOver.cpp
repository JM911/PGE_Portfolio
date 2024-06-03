#include "GameOver.h"
#include "../Core.h"
#include "StartScene.h"

GameOver::GameOver(Core* pEngine) :
	Scene(pEngine)
{
}

GameOver::~GameOver()
{
}

void GameOver::Update()
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
		StartScene* pNextScene = new StartScene(_pEngine);

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
}

void GameOver::Render()
{
	// Clear
	_pEngine->Clear(olc::BLACK);

	_pEngine->DrawString(130, 100, "GAME OVER", olc::WHITE, 5);

	// 메뉴 렌더
	_pEngine->DrawString(230, 200, "Main Menu", olc::WHITE, 2);
	_pEngine->DrawString(230, 250, "Exit", olc::WHITE, 2);

	_pEngine->FillTriangle(_cursorX, _cursorY, _cursorX, _cursorY + 10, _cursorX + 10, _cursorY + 5);
}
