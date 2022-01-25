#include "Enemy.h"
#include "../Core.h"

Enemy::Enemy()
{
	// test
	_genGridX = 1;
	_genGridY = 1;
	_HP = 5;
	_size = 5;
	_color = olc::RED;
	_speed = 10;

	// 
	_x = float(MAP_POS_X + TILE_SIZE * _genGridX + TILE_SIZE / 2);
	_y = float(MAP_POS_Y + TILE_SIZE * _genGridY + TILE_SIZE / 2);
}

Enemy::~Enemy()
{
}

void Enemy::Update(Core* pEngine)
{
	switch (_dir)
	{
	case DIRECTION::RIGHT:
		_x += _speed * pEngine->GetElapsedTime();
		break;
	case DIRECTION::DOWN:
		_y += _speed * pEngine->GetElapsedTime();
		break;
	case DIRECTION::LEFT:
		_x -= _speed * pEngine->GetElapsedTime();
		break;
	case DIRECTION::UP:
		_y -= _speed * pEngine->GetElapsedTime();
		break;
	}
}

void Enemy::Render(Core* pEngine)
{
	pEngine->FillCircle((int)_x, (int)_y, _size, _color);
}
