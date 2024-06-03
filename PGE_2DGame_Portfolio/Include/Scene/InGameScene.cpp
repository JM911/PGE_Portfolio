#include "InGameScene.h"
#include "../Core.h"

#include "../Object/Map.h"
#include "../Object/NormalTower.h"
#include "../Object/BurstTower.h"
#include "../Object/DebuffTower.h"
#include "../Object/MortarTower.h"
#include "../Object/Enemy.h"
#include "../Object/Wave.h"

#include "GameOver.h"

int InGameScene::_playerLife = 20;

InGameScene::InGameScene(Core* pEngine)	:
	Scene(pEngine)
{
	sprHeart = make_unique<olc::Sprite>("Resources/heart.png");
	sprStar = make_unique<olc::Sprite>("Resources/star.png");
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
	// 시작 알림
	if (_timeTickforStageStart < 3.f)
	{
		_timeTickforStageStart += _pEngine->GetElapsedTime();
		return;
	}

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

	// 범위 타워 공격 업데이트
	DebuffAttack();
	MortarAttack();

	// 스테이지 실패(게임오버)
	if (_playerLife <= 0)
	{
		_playerLife = 0;
		_timeTickforGameOver += _pEngine->GetElapsedTime();

		if (_timeTickforGameOver > 5.f)
		{
			GameOver* pNextScene = new GameOver(_pEngine);
			//pNextScene->Create();
			_pEngine->SetNextScene(pNextScene);
		}
	}

	// 기타 UI 관련
	_curTime += _pEngine->GetElapsedTime();
}

void InGameScene::Render()
{
	// Clear
	_pEngine->Clear(olc::DARK_BLUE);

	// 맵
	_pEngine->FillRect(MAP_POS_X - 7, MAP_POS_Y - 7,
		TILE_SIZE * MAP_WIDTH + 14, TILE_SIZE * MAP_HEIGHT + 14, olc::BLACK);
	_pMap->Render();

	// 적 스폰지역 & 데미지 지역 스프라이트
	_pEngine->SetPixelMode(olc::Pixel::MASK);

	int tmpX = MAP_POS_X + TILE_SIZE * _spawnGridX + TILE_SIZE / 2;
	int tmpY = MAP_POS_Y + TILE_SIZE * _spawnGridY + TILE_SIZE / 2;
	_pEngine->DrawSprite(tmpX - 10, tmpY - 10, sprStar.get());

	tmpX = MAP_POS_X + TILE_SIZE * _finalGridX + TILE_SIZE / 2;
	tmpY = MAP_POS_Y + TILE_SIZE * _finalGridY + TILE_SIZE / 2;
	_pEngine->DrawSprite(tmpX - 10, tmpY - 10, sprHeart.get());

	_pEngine->SetPixelMode(olc::Pixel::NORMAL);

	// 웨이브
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

	// 공격수단 (총알 등)
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTower[i][j])
				continue;

			_pTower[i][j]->BulletRender();
		}
	}


	/***  UI  ***/

	// 타워 소개
	TowerTypeUIRender();
	
	// 플레이어 커서
	int _curX = MAP_POS_X + TILE_SIZE * _curGridX + TILE_SIZE / 2;
	int _curY = MAP_POS_Y + TILE_SIZE * _curGridY + TILE_SIZE / 2;
	_pEngine->FillCircle(_curX, _curY, 5, olc::BLACK);



	TextUIRender();
	ControlUIRender();


	// 스테이지 클리어
	if (_pWave[_lastWaveIdx]->IsAllEnemyDead() && _playerLife > 0)
	{
		/*_pEngine->DrawString(80, 80, "STAGE", olc::VERY_DARK_GREY, 13);
		_pEngine->DrawString(80, 200, "CLEAR", olc::VERY_DARK_GREY, 13);*/
		_pEngine->FillRect(120, 130, 400, 50);
		_pEngine->DrawString(145, 140, "STAGE CLEAR", olc::BLACK, 4);
	}

	// 게임 오버
	if (_playerLife <= 0)
	{
		//_pEngine->DrawString(140, 90, "GAME\nOVER", olc::BLACK, 12);
		_pEngine->DrawString(120, 80, "GAME", olc::BLACK, 13);
		_pEngine->DrawString(120, 200, "OVER", olc::BLACK, 13);
	}
}

void InGameScene::PlayerInput()
{
	// 방향키
	if (_pEngine->GetKey(olc::Key::RIGHT).bPressed)
		_curGridX++;
	if (_pEngine->GetKey(olc::Key::LEFT).bPressed)
		_curGridX--;
	if (_pEngine->GetKey(olc::Key::UP).bPressed)
		_curGridY--;
	if (_pEngine->GetKey(olc::Key::DOWN).bPressed)
		_curGridY++;

	// 클리핑
	if (_curGridX < 0)
		_curGridX = 0;
	else if (_curGridX >= MAP_WIDTH)
		_curGridX = MAP_WIDTH - 1;
	if (_curGridY < 0)
		_curGridY = 0;
	else if (_curGridY >= MAP_HEIGHT)
		_curGridY = MAP_HEIGHT - 1;

	// 숫자키
	SelectTypeInput();

	// 스페이스바
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
	
	switch (type)
	{
	case TOWER_TYPE::NORMAL:
		_pTower[gridY][gridX] = new NormalTower(_pEngine);
		_pTower[gridY][gridX]->Create(gridX, gridY);
		break;
	case TOWER_TYPE::BURST:
		_pTower[gridY][gridX] = new BurstTower(_pEngine);
		_pTower[gridY][gridX]->Create(gridX, gridY);
		break;
	case TOWER_TYPE::DEBUFF:
		_pTower[gridY][gridX] = new DebuffTower(_pEngine);
		_pTower[gridY][gridX]->Create(gridX, gridY);
		_vecDTGrid.push_back({ gridX, gridY });
		break;
	case TOWER_TYPE::MORTAR:
		_pTower[gridY][gridX] = new MortarTower(_pEngine);
		_pTower[gridY][gridX]->Create(gridX, gridY);
		_vecMTGrid.push_back({ gridX, gridY });
		break;
	case TOWER_TYPE::SNIPE:
		_pTower[gridY][gridX] = new NormalTower(_pEngine);
		_pTower[gridY][gridX]->Create(gridX, gridY);
		break;
	case TOWER_TYPE::RESTLESS:
		_pTower[gridY][gridX] = new BurstTower(_pEngine);
		_pTower[gridY][gridX]->Create(gridX, gridY);
		break;
	}

	TowerSetting(gridX, gridY);

	_playerGold -= Cost(type);

	_pMap->SetTileType(gridX, gridY, TILE_TYPE::OCCUPIED);
}


void InGameScene::TowerTargetUpdate()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pMap || !_pTower[i][j])
				continue;

			// 이미 설정한 타겟이 범위안에 있으면 넘어감
			if (_pTower[i][j]->GetTarget() 
				&& _pTower[i][j]->CheckTargetInRange())
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


int InGameScene::Cost(TOWER_TYPE type)
{
	switch (type)
	{
	case TOWER_TYPE::NORMAL:
		return 100;
	case TOWER_TYPE::BURST:
		return 150;
	case TOWER_TYPE::DEBUFF:
		return 200;
	case TOWER_TYPE::MORTAR:
		return 300;
	case TOWER_TYPE::SNIPE:
		return 300;
	case TOWER_TYPE::RESTLESS:
		return 500;
	default:
		return 0;
	}
}

void InGameScene::SelectTypeInput()
{
	if (_pEngine->GetKey(olc::Key::K1).bPressed)
		_towerType = TOWER_TYPE::NORMAL;
	if (_pEngine->GetKey(olc::Key::K2).bPressed)
		_towerType = TOWER_TYPE::BURST;
	if (_pEngine->GetKey(olc::Key::K3).bPressed)
		_towerType = TOWER_TYPE::DEBUFF;
	if (_pEngine->GetKey(olc::Key::K4).bPressed)
		_towerType = TOWER_TYPE::MORTAR;
	if (_pEngine->GetKey(olc::Key::K5).bPressed)
		_towerType = TOWER_TYPE::SNIPE;
	if (_pEngine->GetKey(olc::Key::K6).bPressed)
		_towerType = TOWER_TYPE::RESTLESS;
}

void InGameScene::TowerSetting(int gridX, int gridY)
{
	switch (_towerType)
	{
	case TOWER_TYPE::NORMAL:
		static_cast<NormalTower*>(_pTower[gridY][gridX])->Setting(80.f, 2.f, olc::WHITE);
		break;
	case TOWER_TYPE::BURST:
		static_cast<BurstTower*>(_pTower[gridY][gridX])->Setting(5, 60.f, 1.5f, olc::YELLOW);
		break;
	case TOWER_TYPE::DEBUFF:
		static_cast<DebuffTower*>(_pTower[gridY][gridX])->Setting(60.f, 2.f, olc::BLUE);
		break;
	case TOWER_TYPE::MORTAR:
		static_cast<MortarTower*>(_pTower[gridY][gridX])->Setting(60.f, 3.f, olc::Pixel(235, 150, 70));
		break;
	case TOWER_TYPE::SNIPE:
		static_cast<NormalTower*>(_pTower[gridY][gridX])->Setting(100.f, 4.f, olc::DARK_GREEN);
		static_cast<NormalTower*>(_pTower[gridY][gridX])->SetAttack(20);
		break;
	case TOWER_TYPE::RESTLESS:
		static_cast<BurstTower*>(_pTower[gridY][gridX])->Setting(MAX_BULLET_NUM - 5, 60.f, 0.f, olc::DARK_CYAN);
		break;
	}
}

void InGameScene::TowerTypeUIRender()
{
	int totalOffsetX = 20;
	int totalOffsetY = 8;
	int intervalX = 85;

	// 텍스트
	string textCost = "Tower\n\nCost";
	_pEngine->DrawString(30, 310, textCost);

	int textOffsetX = 97;
	int textOffsetY = 270;
	int curTextPointX = textOffsetX + totalOffsetX;
	int curTextPointY = textOffsetY + totalOffsetY;

	for (int i = 1; i <= 6; i++)
	{
		string textKey = to_string(i);
		_pEngine->DrawString(curTextPointX, curTextPointY, textKey);
		curTextPointX += intervalX;
	}

	// 그림
	string towerCost;
	int circleOffsetX = 100;
	int circleOffsetY = 300;
	int stringOffsetX = 88;
	int stringOffsetY = 320;

	int curCirclePointX = circleOffsetX + totalOffsetX;
	int curCirclePointY = circleOffsetY + totalOffsetY;

	int curStringPointX = stringOffsetX + totalOffsetX;
	int curStringPointY = stringOffsetY + totalOffsetY;

	_pEngine->FillCircle(curCirclePointX, curCirclePointY, TOWER_SIZE, olc::WHITE);
	towerCost = to_string(Cost(TOWER_TYPE::NORMAL));
	_pEngine->DrawString(curStringPointX, curStringPointY, towerCost);
	_pEngine->DrawString(curStringPointX - 10, curStringPointY + 16, "Normal", olc::DARK_GREY);

	curCirclePointX += intervalX;
	curStringPointX += intervalX;
	_pEngine->FillCircle(curCirclePointX, curCirclePointY, TOWER_SIZE, olc::YELLOW);
	towerCost = to_string(Cost(TOWER_TYPE::BURST));
	_pEngine->DrawString(curStringPointX, curStringPointY, towerCost);
	_pEngine->DrawString(curStringPointX - 7, curStringPointY + 16, "Burst", olc::DARK_GREY);

	curCirclePointX += intervalX;
	curStringPointX += intervalX;
	_pEngine->FillCircle(curCirclePointX, curCirclePointY, TOWER_SIZE, olc::BLUE);
	towerCost = to_string(Cost(TOWER_TYPE::DEBUFF));
	_pEngine->DrawString(curStringPointX + 1, curStringPointY, towerCost);
	_pEngine->DrawString(curStringPointX, curStringPointY + 16, "Ice", olc::DARK_GREY);

	curCirclePointX += intervalX;
	curStringPointX += intervalX;
	_pEngine->FillCircle(curCirclePointX, curCirclePointY, TOWER_SIZE, olc::Pixel(235, 150, 70));
	towerCost = to_string(Cost(TOWER_TYPE::MORTAR));
	_pEngine->DrawString(curStringPointX, curStringPointY, towerCost);
	_pEngine->DrawString(curStringPointX - 10, curStringPointY + 16, "Mortar", olc::DARK_GREY);

	curCirclePointX += intervalX;
	curStringPointX += intervalX;
	_pEngine->FillCircle(curCirclePointX, curCirclePointY, TOWER_SIZE, olc::DARK_GREEN);
	towerCost = to_string(Cost(TOWER_TYPE::SNIPE));
	_pEngine->DrawString(curStringPointX + 1, curStringPointY, towerCost);
	_pEngine->DrawString(curStringPointX - 7, curStringPointY + 16, "Snipe", olc::DARK_GREY);

	curCirclePointX += intervalX;
	curStringPointX += intervalX;
	_pEngine->FillCircle(curCirclePointX, curCirclePointY, TOWER_SIZE, olc::DARK_CYAN);
	towerCost = to_string(Cost(TOWER_TYPE::RESTLESS));
	_pEngine->DrawString(curStringPointX + 1, curStringPointY, towerCost);
	_pEngine->DrawString(curStringPointX - 16, curStringPointY + 16, "Restless", olc::DARK_GREY);


	int rectOffsetX = 75;
	int rectOffsetY = 283;
	int curRectPointX = rectOffsetX + totalOffsetX;
	int curRectPointY = rectOffsetY + totalOffsetY;

	switch (_towerType)
	{
	case TOWER_TYPE::NORMAL:
		_pEngine->DrawRect(curRectPointX, curRectPointY, 50, 50);
		break;
	case TOWER_TYPE::BURST:
		curRectPointX += intervalX;
		_pEngine->DrawRect(curRectPointX, curRectPointY, 50, 50);
		break;
	case TOWER_TYPE::DEBUFF:
		curRectPointX += 2 * intervalX;
		_pEngine->DrawRect(curRectPointX, curRectPointY, 50, 50);
		break;
	case TOWER_TYPE::MORTAR:
		curRectPointX += 3 * intervalX;
		_pEngine->DrawRect(curRectPointX, curRectPointY, 50, 50);
		break;
	case TOWER_TYPE::SNIPE:
		curRectPointX += 4 * intervalX;
		_pEngine->DrawRect(curRectPointX, curRectPointY, 50, 50);
		break;
	case TOWER_TYPE::RESTLESS:
		curRectPointX += 5 * intervalX;
		_pEngine->DrawRect(curRectPointX, curRectPointY, 50, 50);
		break;
	}
}


void InGameScene::DebuffAttack()
{
	for (auto curGridPos : _vecDTGrid)
	{
		int curGridX = curGridPos.first;
		int curGridY = curGridPos.second;

		DebuffTower* pCurTower = static_cast<DebuffTower*>(_pTower[curGridY][curGridX]);

		if (!pCurTower->GetAttEnable())
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

				float waveX = pCurTower->GetX() - pWaveEnemyArr[l]->GetX();
				float waveY = pCurTower->GetY() - pWaveEnemyArr[l]->GetY();
				float waveDist = sqrtf(waveX * waveX + waveY * waveY);

				if (pCurTower->GetRadius() > waveDist)
					pWaveEnemyArr[l]->SetSlowDebuff(pCurTower->GetSlowRate(), pCurTower->GetDuration());
			}
		}
	}
}

void InGameScene::MortarAttack()
{
	for (auto curGridPos : _vecMTGrid)
	{
		int curGridX = curGridPos.first;
		int curGridY = curGridPos.second;

		MortarTower* pCurTower = static_cast<MortarTower*>(_pTower[curGridY][curGridX]);

		if (!pCurTower->GetAttacking())
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

				float tmpDistX = pCurTower->GetCannonX() - pWaveEnemyArr[l]->GetX();
				float tmpDistY = pCurTower->GetCannonY() - pWaveEnemyArr[l]->GetY();
				float tmpDist = sqrtf(tmpDistX * tmpDistX + tmpDistY * tmpDistY);

				if (tmpDist < pCurTower->GetAOERange() + pWaveEnemyArr[l]->GetSize())
				{
					pWaveEnemyArr[l]->BeDamaged(pCurTower->GetATT());
					pCurTower->FinishAttacking();
				}
			}
		}
	}
}

void InGameScene::TextUIRender()
{
	// 시간
	string strTime = "TIME ";
	_pEngine->DrawString(30, 50, strTime);
	int curMin = (int)_curTime / 60;
	int curSec = (int)_curTime % 60;

	string strMin = "";
	if (curMin < 10)
		strMin = "0";
	strMin += to_string(curMin);

	string strSec = "";
	if (curSec < 10)
		strSec = "0";
	strSec += to_string(curSec);

	strTime = strMin + ":" + strSec;

	//strTime += to_string((int)_curTime);
	_pEngine->DrawString(70, 50, strTime, olc::GREY);

	// 골드
	string strGold = "GOLD ";
	_pEngine->DrawString(30, 90, strGold);
	strGold = to_string(_playerGold);
	_pEngine->DrawString(70, 90, strGold, olc::YELLOW);

	// 목숨
	string strLife = "LIFE ";
	_pEngine->DrawString(30, 130, strLife);
	strLife = to_string(_playerLife);
	_pEngine->DrawString(70, 130, strLife, olc::RED);

	LifeVisulize();
}

void InGameScene::ControlUIRender()
{
	string tmpStr;
	tmpStr = "CONTROL";
	_pEngine->DrawString(525, 20, tmpStr);
	_pEngine->DrawRect(520, 15, 65, 15);


	// 설명박스
	_pEngine->DrawRect(485, 30, 143, 235);

	// 컨트롤 설명
	tmpStr = "\"ARROWS\"";
	_pEngine->DrawString(525, 40, tmpStr);
	tmpStr = "to Move Cursor";
	_pEngine->DrawString(500, 50, tmpStr);

	tmpStr = "\"SPACE\"";
	_pEngine->DrawString(530, 75, tmpStr);
	tmpStr = "to Build Tower";
	_pEngine->DrawString(500, 85, tmpStr);

	tmpStr = "\"NUMBER\"";
	_pEngine->DrawString(525, 110, tmpStr);
	tmpStr = "to Select Tower";
	_pEngine->DrawString(500, 120, tmpStr);

	// 타일 설명
	_pEngine->FillRect(495, 150, TILE_SIZE, TILE_SIZE, olc::DARK_RED);
	_pEngine->DrawRect(495, 150, TILE_SIZE, TILE_SIZE, olc::BLACK);
	tmpStr = ": Wall";
	_pEngine->DrawString(525, 160, tmpStr);

	_pEngine->FillRect(495, 190, TILE_SIZE, TILE_SIZE, olc::DARK_YELLOW);
	_pEngine->DrawRect(495, 190, TILE_SIZE, TILE_SIZE, olc::BLACK);
	tmpStr = ": Enemy Path";
	_pEngine->DrawString(525, 200, tmpStr);

	_pEngine->FillRect(495, 230, TILE_SIZE, TILE_SIZE, olc::GREEN);
	_pEngine->DrawRect(495, 230, TILE_SIZE, TILE_SIZE, olc::BLACK);
	tmpStr = ": Tower Room";
	_pEngine->DrawString(525, 240, tmpStr);
}

void InGameScene::LifeVisulize()
{
	_pEngine->SetPixelMode(olc::Pixel::MASK);
	int sprOffsetX = 5;
	int sprOffsetY = 160;

	int intervalX = 25;
	int intervalY = 25;

	for (int i = 1; i <= _playerLife; i++)
	{
		int sprGridX = (i - 1) % 5 + 1;
		int sprGridY = (i - 1) / 5;

		int sprX = sprOffsetX + intervalX * sprGridX;
		int sprY = sprOffsetY + intervalY * sprGridY;

		_pEngine->DrawSprite(sprX, sprY, sprHeart.get());
	}
	
	_pEngine->SetPixelMode(olc::Pixel::NORMAL);
}
