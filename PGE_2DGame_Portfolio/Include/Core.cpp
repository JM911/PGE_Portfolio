#include "Core.h"
#include "Scene/TestScene.h"
#include "Scene/StageTest.h"

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
	_pScene = new StageTest(this);
	((StageTest*)_pScene)->Create();

	return true;
}

bool Core::OnUserUpdate(float fElapsedTime)
{
	if (!_pScene)
		return false;

	_pScene->Update();
	_pScene->Render();

	return true;
}

void Core::SetScene(Scene* pScene)
{
	if (_pScene)
		SAFE_DELETE(_pScene);

	_pScene = pScene;
}