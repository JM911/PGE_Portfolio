#include "Enemy.h"
#include "../Core.h"
#include "Bullet.h"
#include "../Scene/InGameScene.h"

Enemy::Enemy(Core* pEngine, InGameScene* pScene)	:
	Obj(pEngine), _pScene(pScene)
{
}

Enemy::~Enemy()
{
}

bool Enemy::Create(int genGridX, int genGridY, int size, int hp, int att, float speed, int reward, olc::Pixel color)
{
	_genGridX = genGridX;
	_genGridY = genGridY;
	_size = size;

	_HP = hp;
	_maxHP = hp;
	_ATT = att;
	_speed = speed;
	_reward = reward;
	_color = color;

	_alive = true;
	//_x = float(MAP_POS_X + TILE_SIZE * _genGridX + TILE_SIZE / 2);
	//_y = float(MAP_POS_Y + TILE_SIZE * _genGridY + TILE_SIZE / 2);

	float midX = float(MAP_POS_X + TILE_SIZE * _genGridX + TILE_SIZE / 2);
	float midY = float(MAP_POS_Y + TILE_SIZE * _genGridY + TILE_SIZE / 2);

	float eps = (float)TILE_SIZE / 4.f;
	float dltX = (float)(rand() % 21) / 10.f * eps;
	float dltY = (float)(rand() % 21) / 10.f * eps;

	if (_size >= 7)
	{
		eps /= float(_size - 5);
		dltX /= float(_size - 5);
		dltY /= float(_size - 5);
	}
	
	_x = midX - eps + dltX;
	_y = midY - eps + dltY;

	_epsX = _x - midX;
	_epsY = _y - midY;

	return true;
}

void Enemy::Update()
{
	if (!_alive)
		return;

	float fElapsedTime = _pEngine->GetElapsedTime();

	float curSpeed = _speed;

	// 디버프 여부 확인
	if (_debuffEnable)
	{
		_timeTickforDebuff += fElapsedTime;
		curSpeed *= (1 - _slowRate);
		//_color = olc::DARK_RED;

		if (_timeTickforDebuff > _debuffDuration)
		{
			_debuffEnable = false;
			_timeTickforDebuff = 0.f;
			//_color = olc::RED;
		}
	}

	// 이동
	switch (_dir)
	{
	case DIRECTION::RIGHT:
		_x += curSpeed * fElapsedTime;
		break;
	case DIRECTION::DOWN:
		_y += curSpeed * fElapsedTime;
		break;
	case DIRECTION::LEFT:
		_x -= curSpeed * fElapsedTime;
		break;
	case DIRECTION::UP:
		_y -= curSpeed * fElapsedTime;
		break;
	}
}

void Enemy::Render()
{
	if (!_alive)
		return;

	olc::Pixel curColor = _color;

	if (_debuffEnable)
	{
		curColor *= (1 - _slowRate);
		curColor.b += 100;
	}

	_pEngine->FillCircle((int)_x, (int)_y, _size, curColor);

	int hpBarX = (int)_x - _size;
	int hpBarY = (int)_y - _size - 2;

	int maxHPBarSize = _size * 2;
	int curHPBarSize = maxHPBarSize * _HP / _maxHP;

	_pEngine->DrawLine(hpBarX, hpBarY, hpBarX + maxHPBarSize, hpBarY, olc::RED);
	_pEngine->DrawLine(hpBarX, hpBarY, hpBarX + curHPBarSize, hpBarY, olc::GREEN);

	//string tmp = to_string(_HP);
	//_pEngine->DrawString((int)_x, (int)_y, tmp);
}

void Enemy::ChangeDirAt(int gridX, int gridY, DIRECTION dir)
{
	float fTileSize = (float)TILE_SIZE;

	float x = float(MAP_POS_X + fTileSize * gridX + fTileSize / 2) + _epsX;
	float y = float(MAP_POS_Y + fTileSize * gridY + fTileSize / 2) + _epsY;

	if (dir == DIRECTION::UP || dir == DIRECTION::DOWN)
	{
		if (_dir == DIRECTION::LEFT)
		{
			if (_x < x && _x > x - fTileSize / 2 && _y < y + fTileSize / 2 && _y > y - fTileSize / 2)
				_dir = dir;
		}
		else if (_dir == DIRECTION::RIGHT)
		{
			if (_x > x && _x < x + fTileSize / 2 && _y < y + fTileSize / 2 && _y > y - fTileSize / 2)
				_dir = dir;
		}
	}

	else
	{
		if (_dir == DIRECTION::UP)
		{
			if (_x > x - fTileSize / 2 && _x < x + fTileSize / 2 && _y < y && _y > y - fTileSize / 2)
				_dir = dir;
		}
		else if (_dir == DIRECTION::DOWN)
		{
			if (_x > x - fTileSize / 2 && _x < x + fTileSize / 2 && _y < y + fTileSize / 2 && _y > y)
				_dir = dir;
		}
	}
}

void Enemy::BeDamaged(int att)
{
	_HP -= att;

	if (_HP <= 0 && _HP + att > 0)
	{
		_alive = false;
		_pScene->GetReward(_reward);
	}
}

void Enemy::SetSlowDebuff(float slowRate, float duration)
{
	_debuffEnable = true;
	_slowRate = slowRate;
	_debuffDuration = duration;
}
