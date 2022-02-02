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
	// �÷��̾� �Է�
	PlayerInput();

	// ��
	_pMap->Update();

	// ���̺�
	//_pWave[_curWaveIdx]->Update();
	WaveChangeDir();
	//_playerLife -= _pWave[_curWaveIdx]->CheckReachedEnemy(_finalGridX, _finalGridY);

	for (int i = 0; i < MAX_WAVE_NUM; i++)
	{
		if (!_pWave[i])
			continue;

		_pWave[i]->Update();
		_playerLife -= _pWave[i]->CheckReachedEnemy(_finalGridX, _finalGridY);	// Ȥ�� ������ ���� ����ȭ (_curWaveIdx ���)
	}

	// Ÿ��
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


	// ��Ÿ UI ����
	_curTime += _pEngine->GetElapsedTime();
}

void InGameScene::Render()
{
	// Clear
	_pEngine->Clear(olc::DARK_BLUE);

	// ��
	_pMap->Render();

	// ���̺�
	//_pWave[_curWaveIdx]->Render();
	for (int i = 0; i < MAX_WAVE_NUM; i++)
	{
		if (!_pWave[i])
			continue;

		_pWave[i]->Render();
	}

	// Ÿ��
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTower[i][j])
				continue;

			_pTower[i][j]->Render();
		}
	}

	// TODO: �Ѿ� Render �������� ���� �ϱ� (���� ���� ��µǵ���)


	/***  UI  ***/
	
	// �÷��̾� Ŀ��
	int _curX = MAP_POS_X + TILE_SIZE * _curGridX + TILE_SIZE / 2;
	int _curY = MAP_POS_Y + TILE_SIZE * _curGridY + TILE_SIZE / 2;
	_pEngine->FillCircle(_curX, _curY, 5, olc::BLACK);

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

	if (_pEngine->GetKey(olc::Key::SPACE).bPressed && !_pTower[_curGridY][_curGridX])
	{
		TowerCreate(_curGridX, _curGridY);
	}
}

void InGameScene::TowerCreate(int gridX, int gridY)
{
	if (!_pMap || _pMap->GetTileType(gridX, gridY) != TILE_TYPE::ABLE)
		return;
	
	_pTower[gridY][gridX] = new Tower(_pEngine);
	_pTower[gridY][gridX]->Create(gridX, gridY);

	_pMap->SetTileType(gridX, gridY, TILE_TYPE::OCCUPIED);
}

// �����丵 ����
void InGameScene::TowerTargetUpdate()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pMap || !_pTower[i][j])
				continue;

			// �̹� ������ Ÿ���� �����ȿ� ������ �Ѿ
			if (_pTower[i][j]->GetTarget() && _pTower[i][j]->CheckTargetInRange())
				continue;

			for (int k = 0; k < MAX_WAVE_NUM; k++)		// ���� ���̺갡 �ʿ� �־ ��� üũ�ϵ���
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