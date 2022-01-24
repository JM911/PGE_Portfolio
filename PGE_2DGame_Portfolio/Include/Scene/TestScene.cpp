#include "TestScene.h"
#include "Core.h"

#include "../Object/Tile.h"

TestScene::TestScene()
{
	testTile = new Tile();
}

TestScene::~TestScene()
{
	if (testTile)
		delete testTile;
}

void TestScene::Update(Core* pEngine)
{
	// Clear
	pEngine->Clear(olc::DARK_BLUE);

	// Test
	testTile->SetSize(50);
	testTile->Render(pEngine);
}
