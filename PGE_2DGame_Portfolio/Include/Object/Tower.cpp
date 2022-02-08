#include "Tower.h"
#include "../Core.h"
#include "Enemy.h"

Tower::Tower(Core* pEngine)	:
	Obj(pEngine)
{
	_size = TOWER_SIZE;
}

Tower::~Tower()
{
}

bool Tower::Create(int gridX, int gridY)
{
	// 원모양 타워의 중심으로 세팅
	_gridX = gridX;
	_gridY = gridY;

	_x = float(MAP_POS_X + TILE_SIZE * _gridX + TILE_SIZE / 2);
	_y = float(MAP_POS_Y + TILE_SIZE * _gridY + TILE_SIZE / 2);

	_enable = true;

	return true;
}

void Tower::Update()
{
	if (!_enable)
		return;

	TimeTickInc();
}

void Tower::Render()
{
	if (!_enable)
		return;

	_pEngine->FillCircle((int)_x, (int)_y, _size, _color);
}



void Tower::TimeTickInc()
{
	// 너무 커지면 증가 안하도록
	if (_timeTick > 10000.f)
		return;

	_timeTick += _pEngine->GetElapsedTime();
}

bool Tower::CheckTargetInRange()
{
	if (!_pTarget || !_pTarget->GetAlive())
		return false;

	float x = _x - _pTarget->GetX();
	float y = _y - _pTarget->GetY();
	float dist = sqrtf(x * x + y * y);

	return dist < _range;
}