#include "TestScene.h"
#include "Core.h"

#include "../Object/Map.h"
#include "../Object/Tower.h"
#include "../Object/Enemy.h"

TestScene::TestScene(Core* pEngine)	:
	Scene(pEngine)
{
	// TODO: InGameScene 만들면 MapMake 함수 만들어서 리팩토링
	_pTestMap = new Map(_pEngine);

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

	_pTestMap->SetTileTypeNum(tmpArr);

	// 적들 도착 지점
	int finalGridX = 10;
	int finalGridY = 7;

	_finalX = float(MAP_POS_X + TILE_SIZE * finalGridX + TILE_SIZE / 2);
	_finalY = float(MAP_POS_Y + TILE_SIZE * finalGridY + TILE_SIZE / 2);

	// 적 생성
	_pTestEnemy = new Enemy(_pEngine);
	_pTestEnemy->Create(1, 1, 5, 5, 1, 30.f);
	_pTestEnemy->SetAlive(false);

	// 웨이브 생성
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		_pArrEnemy[i] = new Enemy(_pEngine);
		_pTestEnemy->SetAlive(false);
	}
	_spawnInterval = 0.5f;

	// 기타
	_playerHP = 20;
}

TestScene::~TestScene()
{
	SAFE_DELETE(_pTestMap);

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			SAFE_DELETE(_pTower[i][j]);
		}
	}

	SAFE_DELETE(_pTestEnemy);

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		SAFE_DELETE(_pArrEnemy[i]);
	}
}

void TestScene::Update()
{
	// Input
	if (_pEngine->GetKey(olc::Key::RIGHT).bPressed)
		_curGridX++;
	if (_pEngine->GetKey(olc::Key::LEFT).bPressed)
		_curGridX--;
	if (_pEngine->GetKey(olc::Key::UP).bPressed)
		_curGridY--;
	if (_pEngine->GetKey(olc::Key::DOWN).bPressed)
		_curGridY++;

	if (_pEngine->GetKey(olc::Key::SPACE).bPressed && !_pTower[_curGridY][_curGridX])
	{
		_pTower[_curGridY][_curGridX] = new Tower(_pEngine);
		_pTower[_curGridY][_curGridX]->Create(_curGridX, _curGridY);
	}

	// Test
	_pTestMap->Update();
	_curX = MAP_POS_X + TILE_SIZE * _curGridX + TILE_SIZE / 2;
	_curY = MAP_POS_Y + TILE_SIZE * _curGridY + TILE_SIZE / 2;

	// tower update
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTower[i][j])
				continue;

			_pTower[i][j]->Update();
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

			// testEnemy
			float x = _pTower[i][j]->GetX() - _pTestEnemy->GetX();
			float y = _pTower[i][j]->GetY() - _pTestEnemy->GetY();
			float dist = sqrtf(x * x + y * y);

			if (_pTower[i][j]->GetRange() > dist)
				_pTower[i][j]->SetTarget(_pTestEnemy);


			// Wave
			for (int k = 0; k < ENEMY_NUM; k++)
			{
				if (!_pArrEnemy[k] || !_pArrEnemy[k]->GetAlive())
					continue;

				float waveX = _pTower[i][j]->GetX() - _pArrEnemy[k]->GetX();
				float waveY = _pTower[i][j]->GetY() - _pArrEnemy[k]->GetY();
				float waveDist = sqrtf(waveX * waveX + waveY * waveY);

				if (_pTower[i][j]->GetRange() > waveDist)
					_pTower[i][j]->SetTarget(_pArrEnemy[k]);
			}
		}
	}
	


	// enemy update => for문으로 변경
	_pTestEnemy->Update();
	_pTestEnemy->ChangeDirAt(10, 1, DIRECTION::DOWN);
	_pTestEnemy->ChangeDirAt(10, 4, DIRECTION::LEFT);
	_pTestEnemy->ChangeDirAt(1, 4, DIRECTION::DOWN);
	_pTestEnemy->ChangeDirAt(1, 7, DIRECTION::RIGHT);

	CheckEnemyReach(_pTestEnemy);

	// Wave 업데이트
	SpawnWave(_pEngine->GetElapsedTime());

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!_pArrEnemy[i])
			continue;

		_pArrEnemy[i]->Update();
		_pArrEnemy[i]->ChangeDirAt(10, 1, DIRECTION::DOWN);
		_pArrEnemy[i]->ChangeDirAt(10, 4, DIRECTION::LEFT);
		_pArrEnemy[i]->ChangeDirAt(1, 4, DIRECTION::DOWN);
		_pArrEnemy[i]->ChangeDirAt(1, 7, DIRECTION::RIGHT);

		CheckEnemyReach(_pArrEnemy[i]);
	}
}

void TestScene::Render()
{
	// Clear
	_pEngine->Clear(olc::DARK_BLUE);

	// Test
	_pTestMap->Render();
	_pEngine->DrawCircle(_curX, _curY, 10);


	_pTestEnemy->Render();

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTower[i][j])
				continue;

			_pTower[i][j]->Render();
		}
	}

	// Wave 렌더
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!_pArrEnemy)
			continue;

		_pArrEnemy[i]->Render();
	}



	// HP 디스플레이
	string tmp = to_string(_playerHP);
	_pEngine->DrawString(300, 30, tmp);
}

void TestScene::SpawnWave(float elapsedTime)
{
	if (_spawnIndex >= ENEMY_NUM)
		return;

	_spawnTimeTick += elapsedTime;

	if (_spawnTimeTick >= _spawnInterval)
	{
		_spawnTimeTick = 0.f;
		if (_pArrEnemy[_spawnIndex])
			_pArrEnemy[_spawnIndex]->Create(1, 1, 5, 5, 1, 30.f);
		_spawnIndex++;
	}
}

void TestScene::CheckEnemyReach(Enemy* pEnemy)
{
	// TODO: 적 늘리고 for문으로 변경 => 차라리 매개변수로 pEnemy를 받고 밖에서 for문?
	if (!pEnemy || !pEnemy->GetAlive())
		return;

	float enemyX = pEnemy->GetX();
	float enemyY = pEnemy->GetY();
	float eps = 0.5f;

	if (enemyX < _finalX - eps || enemyX > _finalX + eps)
		return;
	if (enemyY < _finalY - eps || enemyY > _finalY + eps)
		return;

	_playerHP -= pEnemy->GetATT();
	pEnemy->SetAlive(false);
}
