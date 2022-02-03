#include "StageTest.h"
#include "../Core.h"

#include "../Object/Map.h"
#include "../Object/Tower.h"
#include "../Object/Enemy.h"
#include "../Object/Wave.h"

StageTest::StageTest(Core* pEngine)	:
	InGameScene(pEngine)
{
}

StageTest::~StageTest()
{
}

bool StageTest::Create()
{
	MapCreate();
	WaveCreate();
	_playerGold = 1000;

	return true;
}

void StageTest::Update()
{
	InGameScene::Update();
}

void StageTest::Render()
{
	InGameScene::Render();
	TowerTypeUIRender();
}

bool StageTest::MapCreate()
{
	// 맵 생성
	_pMap = new Map(_pEngine);

	int tmpArr[MAP_HEIGHT][MAP_WIDTH] =
	{
		3, 3, 3, 3, 3,	3, 3, 3, 3, 3,	3, 3,
		3, 1, 1, 1, 1,	1, 1, 1, 1, 1,	1, 3,
		3, 2, 2, 2, 2,	2, 2, 2, 2, 2,	1, 3,
		3, 2, 2, 2, 2,	2, 2, 2, 2, 2,	1, 3,
		3, 1, 1, 1, 1,	1, 1, 1, 1, 1,	1, 3,

		3, 1, 2, 2, 2,	2, 2, 2, 2, 2,	2, 3,
		3, 1, 2, 2, 2,	2, 2, 2, 2, 2,	2, 3,
		3, 1, 1, 1, 1,	1, 1, 1, 1, 1,	1, 3,
		3, 3, 3, 3, 3,	3, 3, 3, 3, 3,	3, 3,
	};

	_pMap->SetTileTypeNum(tmpArr);

	// spawnGrid 설정
	_spawnGridX = 1;
	_spawnGridY = 1;

	// finalGrid 설정
	_finalGridX = 10;
	_finalGridY = 7;

	return true;
}

bool StageTest::WaveCreate()
{
	_pWave[0] = new Wave(_pEngine, this);
	_pWave[0]->Create(10, 5.f, 0.5f);
	_pWave[0]->EnemyCreate(_spawnGridX, _spawnGridY, 5, 5, 1, 30.f, 50);

	return true;
}

void StageTest::WaveChangeDir()
{
	for (int i = 0; i < MAX_WAVE_NUM; i++)
	{
		if (!_pWave[i])
			continue;

		_pWave[i]->ChangeWaveDirAt(10, 1, DIRECTION::DOWN);
		_pWave[i]->ChangeWaveDirAt(10, 4, DIRECTION::LEFT);
		_pWave[i]->ChangeWaveDirAt(1, 4, DIRECTION::DOWN);
		_pWave[i]->ChangeWaveDirAt(1, 7, DIRECTION::RIGHT);
	}
}

int StageTest::Cost(TOWER_TYPE type)
{
	switch (type)
	{
	case TOWER_TYPE::WHITE:
		return 100;
	case TOWER_TYPE::YELLOW:
		return 150;
	case TOWER_TYPE::BLUE:
		return 200;
	default:
		return 0;
	}
}

void StageTest::SelectTypeInput()
{
	if (_pEngine->GetKey(olc::Key::K1).bPressed)
		_towerType = TOWER_TYPE::WHITE;
	if (_pEngine->GetKey(olc::Key::K2).bPressed)
		_towerType = TOWER_TYPE::YELLOW;
	if (_pEngine->GetKey(olc::Key::K3).bPressed)
		_towerType = TOWER_TYPE::BLUE;
}

void StageTest::TowerSetting(int gridX, int gridY)
{
	switch (_towerType)
	{
	case TOWER_TYPE::WHITE:
		_pTower[gridY][gridX]->Setting(TOWER_SIZE, 60.f, 2.f, olc::WHITE);
		break;
	case TOWER_TYPE::YELLOW:
		_pTower[gridY][gridX]->Setting(TOWER_SIZE, 60.f, 2.f, olc::YELLOW);
		break;
	case TOWER_TYPE::BLUE:
		_pTower[gridY][gridX]->Setting(TOWER_SIZE, 60.f, 2.f, olc::BLUE);
		break;
	}
}

void StageTest::TowerTypeUIRender()
{
	_pEngine->FillCircle(200, 300, TOWER_SIZE, olc::WHITE);
	_pEngine->DrawString(188, 320, "100");

	_pEngine->FillCircle(300, 300, TOWER_SIZE, olc::YELLOW);
	_pEngine->DrawString(288, 320, "150");

	_pEngine->FillCircle(400, 300, TOWER_SIZE, olc::BLUE);
	_pEngine->DrawString(388, 320, "200");

	switch(_towerType)
	{
	case TOWER_TYPE::WHITE:
		_pEngine->DrawRect(175, 283, 50, 50);
		break;
	case TOWER_TYPE::YELLOW:
		_pEngine->DrawRect(275, 283, 50, 50);
		break;
	case TOWER_TYPE::BLUE:
		_pEngine->DrawRect(375, 283, 50, 50);
		break;
	}
}
