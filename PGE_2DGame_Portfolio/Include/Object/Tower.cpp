#include "Tower.h"
#include "../Core.h"
#include "Bullet.h"
#include "Enemy.h"

Tower::Tower(Core* pEngine)	:
	Obj(pEngine)
{
	// test
	_size = TOWER_SIZE;
	_range = 60.f;
	_interval = 2.f;
}

Tower::~Tower()
{
	SAFE_DELETE(_pBullet);
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

void Tower::Setting(int size, float range, float interval, olc::Pixel color)
{
	_size = size;
	_range = range;
	_interval = interval;
	_color = color;
}

void Tower::Update()
{
	if (!_enable)
		return;
	
	TimeTickInc();
	Attack();
	
	// 총알 생사 체크
	if (_pBullet && !(_pBullet->GetEnable()))
		SAFE_DELETE(_pBullet);

	// bullet Update
	if(_pBullet)
		_pBullet->Update();
}

void Tower::Render()
{
	if (!_enable)
		return;

	_pEngine->FillCircle((int)_x, (int)_y, _size, _color);


	// bullet Render
	if (_pBullet)
		_pBullet->Render();
}

void Tower::TimeTickInc()
{
	// 너무 커지면 증가 안하도록
	if (_timeTick > 10000.f)
		return;

	_timeTick += _pEngine->GetElapsedTime();
}

void Tower::CreateBullet()
{
	if (_pBullet || !_pTarget)
		return;

	_pBullet = new Bullet(_pEngine);
	_pBullet->Create(_x, _y, _pTarget);
	_pBullet->Setting(2, 150.f, 1);		// 외부변경? 타워 타입별로 다르게
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

void Tower::Attack()
{
	if (!CheckTargetInRange())
		return;

	if (_timeTick < _interval || (_pBullet && _pBullet->GetEnable()))
		return;

	_timeTick = 0;
 	CreateBullet();
}

