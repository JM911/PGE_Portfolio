#include "GameClear.h"
#include "../Core.h"
#include "StartScene.h"

GameClear::GameClear(Core* pEngine) :
	Scene(pEngine)
{
}

GameClear::~GameClear()
{
}

void GameClear::Update()
{
	// Á¾·á
	if (_pEngine->GetKey(olc::Key::SPACE).bReleased)
	{
		_pEngine->Exit();
	}
}

void GameClear::Render()
{
	// Clear
	_pEngine->Clear(olc::BLACK);

	_pEngine->DrawString(135, 100, "GAME CLEAR", olc::WHITE, 3);
}
