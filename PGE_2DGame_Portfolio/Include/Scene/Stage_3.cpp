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
	InGameScene::Render();
	TowerTypeUIRender();

	// 스테이지 표시
	_pEngine->DrawString(280, 20, "Stage 3");
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

