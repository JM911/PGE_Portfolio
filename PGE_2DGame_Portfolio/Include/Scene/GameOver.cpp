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
	// ��ŸƮ ȭ������
	if (_pEngine->GetKey(olc::Key::SPACE).bReleased)
	{
		StartScene* pNextScene = new StartScene(_pEngine);
		_pEngine->SetNextScene(pNextScene);
	}

	// ����
	if (_pEngine->GetKey(olc::Key::ESCAPE).bReleased)
	{
		_pEngine->Exit();
	}
}

void GameOver::Render()
{
	// Clear
	_pEngine->Clear(olc::BLACK);

	_pEngine->DrawString(135, 100, "GAME OVER", olc::WHITE, 3);
}
