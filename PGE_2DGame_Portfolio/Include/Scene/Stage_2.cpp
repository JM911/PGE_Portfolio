#include "Stage_2.h"
#include "../Core.h"

#include "../Object/Map.h"
#include "../Object/NormalTower.h"
#include "../Object/BurstTower.h"
#include "../Object/DebuffTower.h"
#include "../Object/Enemy.h"
#include "../Object/Wave.h"

#include "Stage_3.h"

Stage_2::Stage_2(Core* pEngine) :
	InGameScene(pEngine)
{
}

Stage_2::~Stage_2()
{
}

bool Stage_2::Create()
{
	MapCreate();
	WaveCreate();
	_playerGold = 1000;

	return true;
}

void Stage_2::Update()
{
	InGameScene::Update();

	// 스테이지 클리어
	if (_pWave[_lastWaveIdx]->IsAllEnemyDead())
	{
		_timeTickforNextStage += _pEngine->GetElapsedTime();

		if (_timeTickforNextStage > 5.f)
		{
			Stage_3* pNextScene = new Stage_3(_pEngine);
			pNextScene->Create();
			_pEngine->SetNextScene(pNextScene);
		}
	}
}

void Stage_2::Render()
{
	InGameScene::Render();
	TowerTypeUIRender();

	// 스테이지 표시
	_pEngine->DrawString(280, 20, "Stage 2");
}

bool Stage_2::MapCreate()
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

bool Stage_2::WaveCreate()
{
	_pWave[0] = new Wave(_pEngine, this);
	_pWave[0]->Create(10, 5.f, 0.5f);
	_pWave[0]->EnemyCreate(_spawnGridX, _spawnGridY, 5, 5, 1, 30.f, 50);

	_pWave[1] = new Wave(_pEngine, this);
	_pWave[1]->Create(10, 20.f, 0.5f);
	_pWave[1]->EnemyCreate(_spawnGridX, _spawnGridY, 5, 10, 1, 30.f, 50);

	_pWave[2] = new Wave(_pEngine, this);
	_pWave[2]->Create(10, 35.f, 0.5f);
	_pWave[2]->EnemyCreate(_spawnGridX, _spawnGridY, 5, 15, 1, 30.f, 50);

	_pWave[3] = new Wave(_pEngine, this);
	_pWave[3]->Create(1, 50.f, 0.5f);
	_pWave[3]->EnemyCreate(_spawnGridX, _spawnGridY, 8, 200, 1, 20.f, 50);

	_lastWaveIdx = 3;

	return true;
}

void Stage_2::WaveChangeDir()
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

int Stage_2::Cost(TOWER_TYPE type)
{
	switch (type)
	{
	case TOWER_TYPE::NORMAL:
		return 100;
	case TOWER_TYPE::BURST:
		return 150;
	case TOWER_TYPE::DEBUFF:
		return 200;
	default:
		return 0;
	}
}

void Stage_2::SelectTypeInput()
{
	if (_pEngine->GetKey(olc::Key::K1).bPressed)
		_towerType = TOWER_TYPE::NORMAL;
	if (_pEngine->GetKey(olc::Key::K2).bPressed)
		_towerType = TOWER_TYPE::BURST;
	if (_pEngine->GetKey(olc::Key::K3).bPressed)
		_towerType = TOWER_TYPE::DEBUFF;
}

void Stage_2::TowerSetting(int gridX, int gridY)
{
	switch (_towerType)
	{
	case TOWER_TYPE::NORMAL:
		static_cast<NormalTower*>(_pTower[gridY][gridX])->Setting(60.f, 2.f, olc::WHITE);
		break;
	case TOWER_TYPE::BURST:
		static_cast<BurstTower*>(_pTower[gridY][gridX])->Setting(5, 60.f, 1.5f, olc::YELLOW);
		break;
	case TOWER_TYPE::DEBUFF:
		static_cast<DebuffTower*>(_pTower[gridY][gridX])->Setting(60.f, 2.f, olc::BLUE);
		break;
	case TOWER_TYPE::MORTAR:
		//_pTower[gridY][gridX]->Setting(TOWER_SIZE, 60.f, 2.f, olc::BLUE);
		break;
	}
}

void Stage_2::TowerTypeUIRender()
{
	_pEngine->FillCircle(200, 300, TOWER_SIZE, olc::WHITE);
	_pEngine->DrawString(188, 320, "100");

	_pEngine->FillCircle(300, 300, TOWER_SIZE, olc::YELLOW);
	_pEngine->DrawString(288, 320, "150");

	_pEngine->FillCircle(400, 300, TOWER_SIZE, olc::BLUE);
	_pEngine->DrawString(388, 320, "200");

	switch (_towerType)
	{
	case TOWER_TYPE::NORMAL:
		_pEngine->DrawRect(175, 283, 50, 50);
		break;
	case TOWER_TYPE::BURST:
		_pEngine->DrawRect(275, 283, 50, 50);
		break;
	case TOWER_TYPE::DEBUFF:
		_pEngine->DrawRect(375, 283, 50, 50);
		break;
	}
}
