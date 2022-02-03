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

	switch (_dir)
	{
	case DIRECTION::RIGHT:
		_x += _speed * fElapsedTime;
		break;
	case DIRECTION::DOWN:
		_y += _speed * fElapsedTime;
		break;
	case DIRECTION::LEFT:
		_x -= _speed * fElapsedTime;
		break;
	case DIRECTION::UP:
		_y -= _speed * fElapsedTime;
		break;
	}
}

void Enemy::Render()
{
	if (!_alive)
		return;

	_pEngine->FillCircle((int)_x, (int)_y, _size, _color);

	string tmp = to_string(_HP);
	_pEngine->DrawString((int)_x, (int)_y, tmp);
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
		xDiff = 0.2f;
		yDiff = 1.0f;
		break;
	case DIRECTION::LEFT:
	case DIRECTION::RIGHT:
		xDiff = 1.0f;
		yDiff = 0.2f;
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