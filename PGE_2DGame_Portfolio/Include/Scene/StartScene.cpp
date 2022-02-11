#include "StartScene.h"
#include "../Core.h"
#include "Stage_1.h"

StartScene::StartScene(Core* pEngine) :
	Scene(pEngine)
{
}

StartScene::~StartScene()
{
}

void StartScene::Update()
{
	// 인게임으로
	if (_pEngine->GetKey(olc::Key::SPACE).bReleased)
	{
		Stage_1* pNextScene = new Stage_1(_pEngine);
		pNextScene->Create();
		_pEngine->SetNextScene(pNextScene);
	}

	// 종료
	if (_pEngine->GetKey(olc::Key::ESCAPE).bReleased)
	{
		_pEngine->Exit();
	}
}

void StartScene::Render()
{
	// Clear
	_pEngine->Clear(olc::BLACK);

	_pEngine->DrawString(135, 100, "Circle Invaders", olc::WHITE, 3);
}
