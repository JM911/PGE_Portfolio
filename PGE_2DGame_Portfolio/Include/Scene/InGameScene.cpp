#include "InGameScene.h"
#include "../Core.h"

#include "../Object/Map.h"
#include "../Object/Tower.h"
#include "../Object/Enemy.h"
#include "../Object/Wave.h"

int InGameScene::_playerLife = 20;

InGameScene::InGameScene(Core* pEngine)	:
	Scene(pEngine)
{
}

InGameScene::~InGameScene()
{
	SAFE_DELETE(_pMap);

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			SAFE_DELETE(_pTower[i][j]);
		}
	}

	for (int i = 0; i < MAX_WAVE_NUM; i++)
	{
		SAFE_DELETE(_pWave[i]);
	}
}

void InGameScene::Update()
{
	// 플레이어 입력
	PlayerInput();

	// 맵
	_pMap->Update();

	// 웨이브
	//_pWave[_curWaveIdx]->Update();
	WaveChangeDir();
	//_playerLife -= _pWave[_curWaveIdx]->CheckReachedEnemy(_finalGridX, _finalGridY);

	for (int i = 0; i < MAX_WAVE_NUM; i++)
	{
		if (!_pWave[i])
			continue;

		_pWave[i]->Update();
		_playerLife -= _pWave[i]->CheckReachedEnemy(_finalGridX, _finalGridY);	// 혹시 느리면 여기 최적화 (_curWaveIdx 사용)
	}

	// 타워
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTower[i][j])
				continue;

			_pTower[i][j]->Update();
		}
	}

	TowerTargetUpdate();


	// 기타 UI 관련
	_curTime += _pEngine->GetElapsedTime();
}

void InGameScene::Render()
{
	// Clear
	_pEngine->Clear(olc::DARK_BLUE);

	// 맵
	_pMap->Render();

	// 웨이브
	//_pWave[_curWaveIdx]->Render();
	for (int i = 0; i < MAX_WAVE_NUM; i++)
	{
		if (!_pWave[i])
			continue;

		_pWave[i]->Render();
	}

	// 타워
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTower[i][j])
				continue;

			_pTower[i][j]->Render();
		}
	}

	// TODO: 총알 Render 마지막에 따로 하기 (제일 위에 출력되도록)


	/***  UI  ***/
	
	// 플레이어 커서
	int _curX = MAP_POS_X + TILE_SIZE * _curGridX + TILE_SIZE / 2;
	int _curY = MAP_POS_Y + TILE_SIZE * _curGridY + TILE_SIZE / 2;
	_pEngine->FillCircle(_curX, _curY, 5, olc::BLACK);

	// 시간
	string strTime = "TIME: ";
	strTime += to_string((int)_curTime);
	_pEngine->DrawString(50, 50, strTime);

	// 목숨
	string strLife = "LIFE: ";
	strLife += to_string(_playerLife);
	_pEngine->DrawString(50, 100, strLife);

	// 골드
	string strGold = "GOLD: ";
	strGold += to_string(_playerGold);
	_pEngine->DrawString(50, 150, strGold);
}

void InGameScene::PlayerInput()
{
	if (_pEngine->GetKey(olc::Key::RIGHT).bPressed)
		_curGridX++;
	if (_pEngine->GetKey(olc::Key::LEFT).bPressed)
		_curGridX--;
	if (_pEngine->GetKey(olc::Key::UP).bPressed)
		_curGridY--;
	if (_pEngine->GetKey(olc::Key::DOWN).bPressed)
		_curGridY++;

	SelectTypeInput();

	if (_pEngine->GetKey(olc::Key::SPACE).bPressed && !_pTower[_curGridY][_curGridX])
	{
		TowerCreate(_curGridX, _curGridY, _towerType);
	}
}

void InGameScene::GetReward(int reward)
{
	_playerGold += reward;
}

void InGameScene::TowerCreate(int gridX, int gridY, TOWER_TYPE type)
{
	if (!_pMap || _pMap->GetTileType(gridX, gridY) != TILE_TYPE::ABLE)
		return;

	if (_playerGold < Cost(type))
		return;
	
	_pTower[gridY][gridX] = new Tower(_pEngine);
	_pTower[gridY][gridX]->Create(gridX, gridY);

	TowerSetting(gridX, gridY);

	_playerGold -= Cost(type);

	_pMap->SetTileType(gridX, gridY, TILE_TYPE::OCCUPIED);
}

// 리팩토링 고려
void InGameScene::TowerTargetUpdate()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pMap || !_pTower[i][j])
				continue;

			// 이미 설정한 타겟이 범위안에 있으면 넘어감
			if (_pTower[i][j]->GetTarget() && _pTower[i][j]->CheckTargetInRange())
				continue;

			for (int k = 0; k < MAX_WAVE_NUM; k++)		// 여러 웨이브가 맵에 있어도 모두 체크하도록
			{
				if (!_pWave[k])
					continue;

				int enemyNum = _pWave[k]->GetEnemyNum();
				Enemy** pWaveEnemyArr = _pWave[k]->GetEnemyArr();
				
				for (int l = 0; l < enemyNum; l++)
				{
					if (!pWaveEnemyArr[l] || !pWaveEnemyArr[l]->GetAlive())
						continue;

					float waveX = _pTower[i][j]->GetX() - pWaveEnemyArr[l]->GetX();
					float waveY = _pTower[i][j]->GetY() - pWaveEnemyArr[l]->GetY();
					float waveDist = sqrtf(waveX * waveX + waveY * waveY);

					if (_pTower[i][j]->GetRange() > waveDist)
						_pTower[i][j]->SetTarget(pWaveEnemyArr[l]);
				}
			}
		}
	}
}