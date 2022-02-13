#include "Core.h"
#include "Scene/StartScene.h"

//#include "Scene/GameClear.h"

Core::Core()
{
	sAppName = "Circle Invaders";
}

Core::~Core()
{
	SAFE_DELETE(_pScene);
}

bool Core::OnUserCreate()
{
	// Called once at the start, so create things here
	_pScene = new StartScene(this);
	//((Stage_3*)_pScene)->Create();

	return true;
}

bool Core::OnUserUpdate(float fElapsedTime)
{
	if (!_pScene)
		return false;

	_pScene->Update();
	_pScene->Render();

	// ¥Ÿ¿Ω æ¿ √º≈©
	if (_pNextScene)
	{
		SetScene(_pNextScene);
		_pNextScene = nullptr;
	}

	if (_bExit)
		return false;
	
	return true;
}

void Core::SetScene(Scene* pScene)
{
	SAFE_DELETE(_pScene);

	_pScene = pScene;
}