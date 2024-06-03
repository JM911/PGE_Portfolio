#include "Stage_3.h"
#include "../Core.h"

#include "../Object/Map.h"
#include "../Object/NormalTower.h"
#include "../Object/BurstTower.h"
#include "../Object/DebuffTower.h"
#include "../Object/Enemy.h"
#include "../Object/Wave.h"

#include "GameClear.h"

Stage_3::Stage_3(Core* pEngine) :
	InGameScene(pEngine)
{
}

Stage_3::~Stage_3()
{
}

bool Stage_3::Create()
{
	MapCreate();
	WaveCreate();
	_playerGold = 1000;

	return true;
}

void Stage_3::Update()
{
	InGameScene::Update();

	// 스테이지 클리어
	if (_pWave[_lastWaveIdx]->IsAllEnemyDead() && _playerLife > 0)
	{
		_timeTickforNextStage += _pEngine->GetElapsedTime();

		if (_timeTickforNextStage > 5.f)
		{
			GameClear* pNextScene = new GameClear(_pEngine);
			//pNextScene->Create();
			_pEngine->SetNextScene(pNextScene);
		}
	}
}

void Stage_3::Render()
{
	// 시작 알림
	if (_timeTickforStageStart < 3.f)
	{
		_pEngine->Clear(olc::VERY_DARK_BLUE);
		_pEngine->DrawString(72, 120, "STAGE 3", olc::WHITE, 9);
		return;
	}

	InGameScene::Render();

	// 스테이지 표시
	_pEngine->DrawString(MAP_POS_X + 100, 15, "Stage 3", olc::WHITE, 2);
}

bool Stage_3::MapCreate()
{
	// 맵 생성
	_pMap = new Map(_pEngine);

	int tmpArr[MAP_HEIGHT][MAP_WIDTH] =
	{
		3, 3, 3, 3, 3,	3, 3, 3, 3, 3,	3, 3,
		3, 1, 1, 1, 1,	1, 1, 1, 1, 1,	1, 3,
		3, 2, 2, 2, 2,	2, 2, 2, 2, 2,	1, 3,
		3, 1, 1, 1, 1,	1, 1, 1, 1, 2,	1, 3,
		3, 1, 2, 2, 2,	2, 2, 2, 1, 2,	1, 3,

		3, 1, 2, 1, 1,	1, 1, 1, 1, 2,	1, 3,
		3, 1, 2, 2, 2,	2, 2, 2, 2, 2,	1, 3,
		3, 1, 1, 1, 1,	1, 1, 1, 1, 1,	1, 3,
		3, 3, 3, 3, 3,	3, 3, 3, 3, 3,	3, 3,
	};

	_pMap->SetTileTypeNum(tmpArr);

	// spawnGrid 설정
	_spawnGridX = 1;
	_spawnGridY = 1;

	// finalGrid 설정
	_finalGridX = 3;
	_finalGridY = 5;

	return true;
}

bool Stage_3::WaveCreate()
{
	_pWave[0] = new Wave(_pEngine, this);
	_pWave[0]->Create(5, 10.f, 0.5f);
	_pWave[0]->EnemyCreate(_spawnGridX, _spawnGridY, 3, 20, 1, 25.f, 150, olc::Pixel(255, 150, 150));

	_pWave[1] = new Wave(_pEngine, this);
	_pWave[1]->Create(3, 20.f, 0.7f);
	_pWave[1]->EnemyCreate(_spawnGridX, _spawnGridY, 5, 80, 1, 20.f, 300);

	_pWave[2] = new Wave(_pEngine, this);
	_pWave[2]->Create(1, 35.f, 0.5f);
	_pWave[2]->EnemyCreate(_spawnGridX, _spawnGridY, 8, 200, 1, 15.f, 700, olc::DARK_RED);

	_pWave[3] = new Wave(_pEngine, this);
	_pWave[3]->Create(2, 50.f, 1.0f);
	_pWave[3]->EnemyCreate(_spawnGridX, _spawnGridY, 5, 200, 1, 15.f, 500, olc::VERY_DARK_RED);

	_pWave[4] = new Wave(_pEngine, this);
	_pWave[4]->Create(1, 65.f, 0.5f);
	_pWave[4]->EnemyCreate(_spawnGridX, _spawnGridY, 10, 500, 1, 15.f, 1000, olc::VERY_DARK_GREY);

	_lastWaveIdx = 4;

	return true;
}

void Stage_3::WaveChangeDir()
{
	for (int i = 0; i < MAX_WAVE_NUM; i++)
	{
		if (!_pWave[i])
			continue;

		_pWave[i]->ChangeWaveDirAt(10, 1, DIRECTION::DOWN);
		_pWave[i]->ChangeWaveDirAt(10, 7, DIRECTION::LEFT);
		_pWave[i]->ChangeWaveDirAt(1, 7, DIRECTION::UP);
		_pWave[i]->ChangeWaveDirAt(1, 3, DIRECTION::RIGHT);
		_pWave[i]->ChangeWaveDirAt(8, 3, DIRECTION::DOWN);
		_pWave[i]->ChangeWaveDirAt(8, 5, DIRECTION::LEFT);
	}
}

