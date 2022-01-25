#include "TestScene.h"
#include "Core.h"

#include "../Object/Map.h"
#include "../Object/Tower.h"
#include "../Object/Enemy.h"

TestScene::TestScene()
{
	_pTestMap = new Map();

	int tmpArr[MAP_HEIGHT][MAP_WIDTH] =
	{
		3, 3, 3, 3, 3, 3,	3, 3, 3, 3, 3, 3,
		3, 1, 1, 1, 1, 1,	1, 1, 1, 1, 1, 3,
		3, 2, 2, 2, 2, 2,	2, 2, 2, 2, 1, 3,
		3, 2, 2, 2, 2, 2,	2, 2, 2, 2, 1, 3,
		3, 1, 1, 1, 1, 1,	1, 1, 1, 1, 1, 3,

		3, 1, 2, 2, 2, 2,	2, 2, 2, 2, 2, 3,
		3, 1, 2, 2, 2, 2,	2, 2, 2, 2, 2, 3,
		3, 1, 1, 1, 1, 1,	1, 1, 1, 1, 1, 3,
		3, 3, 3, 3, 3, 3,	3, 3, 3, 3, 3, 3,
	};

	_pTestMap->SetTileTypeNum(tmpArr);

	_pTestEnemy = new Enemy();
}

TestScene::~TestScene()
{
	if (_pTestMap)
	{
		delete _pTestMap;
		_pTestMap = nullptr;
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTower[i][j])
				continue;

			delete _pTower[i][j];
			_pTower[i][j] = nullptr;
		}
	}

	if (_pTestEnemy)
	{
		delete _pTestEnemy;
		_pTestEnemy = nullptr;
	}
}

void TestScene::Update(Core* pEngine)
{
	// Input
	if (pEngine->GetKey(olc::Key::RIGHT).bPressed)
		_curGridX++;
	if (pEngine->GetKey(olc::Key::LEFT).bPressed)
		_curGridX--;
	if (pEngine->GetKey(olc::Key::UP).bPressed)
		_curGridY--;
	if (pEngine->GetKey(olc::Key::DOWN).bPressed)
		_curGridY++;

	if (pEngine->GetKey(olc::Key::SPACE).bPressed && !_pTower[_curGridY][_curGridX])
	{
		_pTower[_curGridY][_curGridX] = new Tower(_curGridX, _curGridY);
		_pTower[_curGridY][_curGridX]->SetEnable(true);
	}

	// Test
	_pTestMap->Update(pEngine);
	_curX = MAP_POS_X + TILE_SIZE * _curGridX + TILE_SIZE / 2;
	_curY = MAP_POS_Y + TILE_SIZE * _curGridY + TILE_SIZE / 2;

	// tower update
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTower[i][j])
				continue;

			_pTower[i][j]->Update(pEngine);
		}
	}

	// enemy update
	_pTestEnemy->Update(pEngine);
}

void TestScene::Render(Core* pEngine)
{
	// Clear
	pEngine->Clear(olc::DARK_BLUE);

	// Test
	_pTestMap->Render(pEngine);
	pEngine->DrawCircle(_curX, _curY, 10);

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTower[i][j])
				continue;

			_pTower[i][j]->Render(pEngine);
		}
	}

	_pTestEnemy->Render(pEngine);
}
