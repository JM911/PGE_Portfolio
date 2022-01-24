#include "Core.h"
#include "Scene/TestScene.h"

Core::Core()
{
	sAppName = "Core";
}

Core::~Core()
{
	ReleaseScene();
}

bool Core::OnUserCreate()
{
	// Called once at the start, so create things here
	_pScene = new TestScene();

	return true;
}

bool Core::OnUserUpdate(float fElapsedTime)
{
	if (!_pScene)
		return false;

	_pScene->Update(this);

	return true;
}

void Core::SetScene(Scene* pScene)
{
	if (_pScene)
		ReleaseScene();

	_pScene = pScene;
}

void Core::ReleaseScene()
{
	if (!_pScene)
		return;

	delete _pScene;
	_pScene = nullptr;
}
