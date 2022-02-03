#include "Bullet.h"
#include "../Core.h"
#include "Enemy.h"

Bullet::Bullet(Core* pEngine)	:
	Obj(pEngine)
{
	// test
	_speed = 150.f;
	_ATT = 1;
}

Bullet::~Bullet()
{
}

void Bullet::Create(float x, float y, Enemy* pTarget)
{
	_x = x;
	_y = y;

	_pTarget = pTarget;
	_enable = true;
}

void Bullet::Setting(int size, float speed, int att, olc::Pixel color)
{
	_size = size;
	_speed = speed;
	_ATT = att;
	_color = color;
}

void Bullet::Update()
{
	if (!_pTarget || !_enable)
		return;

	float fElapsedTime = _pEngine->GetElapsedTime();

	_dirX = _pTarget->GetX() - _x;
	_dirY = _pTarget->GetY() - _y;

	// Range Check & Die
	float dist = sqrtf(_dirX * _dirX + _dirY * _dirY);
	float eps = 0.25f;
	if (dist < eps)
	{
		_pTarget->BeDamaged(_ATT);
		_enable = false;
	}

	// Update Direction
	_dirX /= dist;
	_dirY /= dist;

	// Move
	_x += _speed * fElapsedTime * _dirX;
	_y += _speed * fElapsedTime * _dirY;

}

void Bullet::Render()
{
	if (!_enable)
		return;

	if (_size == 0)
		_pEngine->Draw((int)_x, (int)_y, _color);
	else
		_pEngine->FillCircle((int)_x, (int)_y, _size, _color);
}
