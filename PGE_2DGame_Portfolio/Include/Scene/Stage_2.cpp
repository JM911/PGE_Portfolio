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
	if (_pWave[_lastWaveIdx]->IsAllEnemyDead() && _playerLife > 0)
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
		3, 1, 2, 2, 1,	1, 1, 1, 2, 2,	1, 3,
		3, 1, 2, 2, 1,	2, 2, 1, 2, 2,	1, 3,
		3, 1, 2, 2, 1,	2, 2, 1, 2, 2,	1, 3,
		3, 1, 2, 2, 1,	2, 2, 1, 2, 2,	1, 3,

		3, 1, 2, 2, 1,	2, 2, 1, 2, 2,	1, 3,
		3, 1, 2, 2, 1,	2, 2, 1, 2, 2,	1, 3,
		3, 1, 1, 1, 1,	2, 2, 1, 1, 1,	1, 3,
		3, 3, 3, 3, 3,	3, 3, 3, 3, 3,	3, 3,
	};

	_pMap->SetTileTypeNum(tmpArr);

	// spawnGrid 설정
	_spawnGridX = 1;
	_spawnGridY = 1;

	// finalGrid 설정
	_finalGridX = 10;
	_finalGridY = 1;

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

		_pWave[i]->ChangeWaveDirAt(1, 1, DIRECTION::DOWN);
		_pWave[i]->ChangeWaveDirAt(1, 7, DIRECTION::RIGHT);
		_pWave[i]->ChangeWaveDirAt(4, 7, DIRECTION::UP);
		_pWave[i]->ChangeWaveDirAt(4, 1, DIRECTION::RIGHT);
		_pWave[i]->ChangeWaveDirAt(7, 1, DIRECTION::DOWN);
		_pWave[i]->ChangeWaveDirAt(7, 7, DIRECTION::RIGHT);
		_pWave[i]->ChangeWaveDirAt(10, 7, DIRECTION::UP);
	}
}
