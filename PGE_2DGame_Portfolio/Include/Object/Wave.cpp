#include "Wave.h"
#include "Enemy.h"
#include "../Core.h"

Wave::Wave(Core* pEngine, InGameScene* pScene)	:
	Obj(pEngine), _pScene(pScene)
{
}

Wave::~Wave()
{
	EnemyClear();
}

bool Wave::Create(int enemyNum, float spawnStartTime, float spawnInterval)
{
	if (enemyNum > MAX_ENEMY_NUM)
		return false;

	EnemyClear();

	_enemyNum = enemyNum;
	_spawnStartTime = spawnStartTime;
	_spawnInterval = spawnInterval;
	_timeTickforNext = spawnInterval;		// 첫 enemy는 바로 생성되도록 하기 위함

	for (int i = 0; i < _enemyNum; i++)
	{
		_pEnemy[i] = new Enemy(_pEngine, _pScene);
	}

	return true;
}

bool Wave::EnemyCreate(int spawnGridX, int spawnGridY, int size, int hp, int att, float speed, int reward, olc::Pixel color)
{
	for (int i = 0; i < _enemyNum; i++)
	{
		if (!_pEnemy[i])
			continue;

		if (!(_pEnemy[i]->Create(spawnGridX, spawnGridY, size, hp, att, speed, reward, color)))
			return false;

		_pEnemy[i]->SetAlive(false);
	}

	return true;
}

void Wave::Update()
{
	SpawnEnemy();

	for (int i = 0; i < _enemyNum; i++)
	{
		if (!_pEnemy[i] || !(_pEnemy[i]->GetAlive()))
			continue;

		_pEnemy[i]->Update();
	}
}

void Wave::Render()
{
	for (int i = 0; i < _enemyNum; i++)
	{
		if (!_pEnemy[i] || !(_pEnemy[i]->GetAlive()))
			continue;

		_pEnemy[i]->Render();
	}
}

void Wave::EnemyClear()
{
	for (int i = 0; i < _enemyNum; i++)
	{
		SAFE_DELETE(_pEnemy[i]);
	}

	_enemyNum = 0;
}

void Wave::ChangeWaveDirAt(int gridX, int gridY, DIRECTION dir)
{
	// Scene의 Update에서 계속 돌아갈 예정
	for (int i = 0; i < _enemyNum; i++)
	{
		if (!_pEnemy[i] || !(_pEnemy[i]->GetAlive()))
			continue;

		_pEnemy[i]->ChangeDirAt(gridX, gridY, dir);
	}
}

void Wave::SpawnEnemy()
{
	float elapsedTime = _pEngine->GetElapsedTime();

	if (_timeTickforStart < _spawnStartTime + 10.f)
	{
		_timeTickforStart += elapsedTime;
	}

	if (_curEnemyIdx >= _enemyNum)
		return;

	if (_timeTickforStart < _spawnStartTime)
	{
		return;
	}

	if (_timeTickforNext < _spawnInterval)
	{
		_timeTickforNext += elapsedTime;
		return;
	}

	_timeTickforNext = 0.f;

	_pEnemy[_curEnemyIdx]->SetAlive(true);
	_curEnemyIdx++;
}

int Wave::CheckReachedEnemy(int finalGridX, int finalGridY)
{
	float fTileSize = (float)TILE_SIZE;

	float finalX = float(MAP_POS_X + fTileSize * finalGridX + fTileSize / 2);
	float finalY = float(MAP_POS_Y + fTileSize * finalGridY + fTileSize / 2);

	for (int i = 0; i < _enemyNum; i++)
	{
		if (!_pEnemy[i] || !_pEnemy[i]->GetAlive())
			continue;

		float enemyX = _pEnemy[i]->GetX();
		float enemyY = _pEnemy[i]->GetY();
		float eps = fTileSize / 2;

		if (enemyX < finalX - eps || enemyX > finalX + eps)
			continue;
		if (enemyY < finalY - eps || enemyY > finalY + eps)
			continue;

		_pEnemy[i]->SetAlive(false);
		return _pEnemy[i]->GetATT();
	}

	return 0;
}

bool Wave::IsAllEnemyDead()
{
	// 아직 시작도 안했으면 false 반환
	if (_timeTickforStart < _spawnStartTime + 2.f)
		return false;

	for (int i = 0; i < _enemyNum; i++)
	{
		if (_pEnemy[i]->GetAlive())		// 하나라도 살아있으면 false 반환
			return false;
	}

	return true;
}
