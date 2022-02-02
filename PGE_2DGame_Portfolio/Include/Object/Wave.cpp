#include "Wave.h"
#include "Enemy.h"
#include "../Core.h"

Wave::Wave(Core* pEngine)	:
	Obj(pEngine)
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
		_pEnemy[i] = new Enemy(_pEngine);
	}

	return true;
}

bool Wave::EnemyCreate(int spawnGridX, int spawnGridY, int size, int hp, int att, float speed, olc::Pixel color)
{
	for (int i = 0; i < _enemyNum; i++)
	{
		if (!_pEnemy[i])
			continue;

		if (!(_pEnemy[i]->Create(spawnGridX, spawnGridY, size, hp, att, speed, color)))
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

	if (_curEnemyIdx >= _enemyNum)
		return;

	if (_timeTickforStart < _spawnStartTime)
	{
		_timeTickforStart += elapsedTime;
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
	float finalX = float(MAP_POS_X + TILE_SIZE * finalGridX + TILE_SIZE / 2);
	float finalY = float(MAP_POS_Y + TILE_SIZE * finalGridY + TILE_SIZE / 2);

	for (int i = 0; i < _enemyNum; i++)
	{
		if (!_pEnemy[i] || !_pEnemy[i]->GetAlive())
			continue;

		float enemyX = _pEnemy[i]->GetX();
		float enemyY = _pEnemy[i]->GetY();
		float eps = 0.5f;

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
	for (int i = 0; i < _enemyNum; i++)
	{
		if (_pEnemy[i]->GetAlive())		// 하나라도 살아있으면 false 반환
			return false;
	}

	return true;
}
