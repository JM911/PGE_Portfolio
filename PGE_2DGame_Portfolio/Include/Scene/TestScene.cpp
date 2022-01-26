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

	// test (tower -> target) 설정
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			// 실제로는 여기에 for문을 한개 더 넣어서 모든 enemy 탐색

			if (!_pTower[i][j])
				continue;

			// 이미 설정한 타겟이 범위안에 있으면 넘어감
			if (_pTower[i][j]->GetTarget() && _pTower[i][j]->CheckTargetInRange())
				continue;

			float x = _pTower[i][j]->GetX() - _pTestEnemy->GetX();
			float y = _pTower[i][j]->GetY() - _pTestEnemy->GetY();
			float dist = sqrtf(x * x + y * y);

			if (_pTower[i][j]->GetRange() > dist)
				_pTower[i][j]->SetTarget(_pTestEnemy);
		}
	}
	


	// enemy update => for문으로 변경
	_pTestEnemy->Update(pEngine);
	_pTestEnemy->ChangeDirAt(10, 1, DIRECTION::DOWN);
	_pTestEnemy->ChangeDirAt(10, 4, DIRECTION::LEFT);
	_pTestEnemy->ChangeDirAt(1, 4, DIRECTION::DOWN);
	_pTestEnemy->ChangeDirAt(1, 7, DIRECTION::RIGHT);
}

void TestScene::Render(Core* pEngine)
{
	// Clear
	pEngine->Clear(olc::DARK_BLUE);

	// Test
	_pTestMap->Render(pEngine);
	pEngine->DrawCircle(_curX, _curY, 10);


	_pTestEnemy->Render(pEngine);

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTower[i][j])
				continue;

			_pTower[i][j]->Render(pEngine);
		}
	}

}
