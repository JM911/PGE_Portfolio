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
	_x = float(MAP_POS_X + TILE_SIZE * _genGridX + TILE_SIZE / 2);
	_y = float(MAP_POS_Y + TILE_SIZE * _genGridY + TILE_SIZE / 2);

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
		_color = olc::DARK_RED;

		if (_timeTickforDebuff > _debuffDuration)
		{
			_debuffEnable = false;
			_timeTickforDebuff = 0.f;
			_color = olc::RED;
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

	_pEngine->FillCircle((int)_x, (int)_y, _size, _color);

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
	float x = float(MAP_POS_X + TILE_SIZE * gridX + TILE_SIZE / 2);
	float y = float(MAP_POS_Y + TILE_SIZE * gridY + TILE_SIZE / 2);
	
	float xDiff = 0.f;
	float yDiff = 0.f;

	switch (dir)
	{
	case DIRECTION::UP:
	case DIRECTION::DOWN:
		xDiff = 0.3f;
		yDiff = 1.0f;
		break;
	case DIRECTION::LEFT:
	case DIRECTION::RIGHT:
		xDiff = 1.0f;
		yDiff = 0.3f;
		break;
	}


	if (_x > x - xDiff && _x <x + xDiff && _y > y - yDiff && _y < y + yDiff)
		_dir = dir;
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
