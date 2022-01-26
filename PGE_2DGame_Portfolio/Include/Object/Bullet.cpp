#include "Bullet.h"
#include "../Core.h"
#include "Enemy.h"

Bullet::Bullet()
{
	_speed = 100.f;
}

Bullet::~Bullet()
{
}

void Bullet::Update(Core* pEngine)
{
	if (!_pTarget || !_enable)
		return;

	_dirX = _pTarget->GetX() - _x;
	_dirY = _pTarget->GetY() - _y;

	// Range Check & Die
	float dist = sqrtf(_dirX * _dirX + _dirY * _dirY);
	float eps = 0.1f;
	if (dist < eps)
	{
		// TODO: 타겟의 HP 깎이는 함수 구현 후 호출
		_enable = false;
	}

	// Update Direction
	_dirX /= dist;
	_dirY /= dist;

	// Move
	_x += _speed * pEngine->GetElapsedTime() * _dirX;
	_y += _speed * pEngine->GetElapsedTime() * _dirY;

}

void Bullet::Render(Core* pEngine)
{
	if (!_enable)
		return;

	if (_size == 0)
		pEngine->Draw((int)_x, (int)_y, _color);
	else
		pEngine->FillCircle((int)_x, (int)_y, _size, _color);
}
