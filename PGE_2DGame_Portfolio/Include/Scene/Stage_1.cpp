#include "Stage_1.h"
#include "../Core.h"

#include "../Object/Map.h"
#include "../Object/NormalTower.h"
#include "../Object/BurstTower.h"
#include "../Object/DebuffTower.h"
#include "../Object/Enemy.h"
#include "../Object/Wave.h"

#include "Stage_2.h"

Stage_1::Stage_1(Core* pEngine) :
	InGameScene(pEngine)
{
}

Stage_1::~Stage_1()
{
}

bool Stage_1::Create()
{
	MapCreate();
	WaveCreate();
	_playerGold = 300;

	// 1스테이지에만 체력 원상복구 (다시시작)
	_playerLife = 20;

	return true;
}

void Stage_1::Update()
{
	InGameScene::Update();

	// 스테이지 클리어
	if (_pWave[_lastWaveIdx]->IsAllEnemyDead() && _playerLife > 0)
	{
		_timeTickforNextStage += _pEngine->GetElapsedTime();

		if (_timeTickforNextStage > 5.f)
		{
			Stage_2* pNextScene = new Stage_2(_pEngine);
			pNextScene->Create();
			_pEngine->SetNextScene(pNextScene);
		}
	}
}

void Stage_1::Render()
{
	// 시작 알림
	if (_timeTickforStageStart < 3.f)
	{
		_pEngine->Clear(olc::VERY_DARK_BLUE);
		_pEngine->DrawString(72, 120, "STAGE 1", olc::WHITE, 9);
		return;
	}

	InGameScene::Render();

	// 스테이지 표시
	_pEngine->DrawString(MAP_POS_X + 100, 15, "Stage 1", olc::WHITE, 2);
}

bool Stage_1::MapCreate()
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

bool Stage_1::WaveCreate()
{
	_pWave[0] = new Wave(_pEngine, this);
	_pWave[0]->Create(5, 10.f, 0.5f);
	_pWave[0]->EnemyCreate(_spawnGridX, _spawnGridY, 3, 3, 1, 30.f, 30, olc::Pixel(255, 150, 150));

	_pWave[1] = new Wave(_pEngine, this);
	_pWave[1]->Create(10, 20.f, 0.5f);
	_pWave[1]->EnemyCreate(_spawnGridX, _spawnGridY, 5, 5, 1, 30.f, 50);

	_pWave[2] = new Wave(_pEngine, this);
	_pWave[2]->Create(10, 30.f, 0.5f);
	_pWave[2]->EnemyCreate(_spawnGridX, _spawnGridY, 5, 10, 1, 30.f, 70, olc::DARK_RED);

	_pWave[3] = new Wave(_pEngine, this);
	_pWave[3]->Create(5, 45.f, 1.f);
	_pWave[3]->EnemyCreate(_spawnGridX, _spawnGridY, 7, 20, 3, 25.f, 100, olc::VERY_DARK_RED);

	_pWave[4] = new Wave(_pEngine, this);
	_pWave[4]->Create(1, 60.f, 0.5f);
	_pWave[4]->EnemyCreate(_spawnGridX, _spawnGridY, 10, 200, 5, 20.f, 200, olc::VERY_DARK_GREY);

	_lastWaveIdx = 4;

	return true;
}

void Stage_1::WaveChangeDir()
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
