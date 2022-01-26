#include "Tower.h"
#include "../Core.h"
#include "Bullet.h"
#include "Enemy.h"

Tower::Tower(int gridX, int gridY)	:
	_gridX(gridX), _gridY(gridY)
{
	// 원모양 타워의 중심으로 세팅
	_x = float(MAP_POS_X + TILE_SIZE * _gridX + TILE_SIZE / 2);
	_y = float(MAP_POS_Y + TILE_SIZE * _gridY + TILE_SIZE / 2);

	// test
	_range = 60.f;
	_interval = 2.f;
}

Tower::~Tower()
{
}

void Tower::Update(Core* pEngine)
{
	if (!_enable)
		return;
	
	TimeTickInc(pEngine);
	Attack();
	
	if (_pBullet && !(_pBullet->GetEnable()))
		ReleaseBullet();

	// bullet Update
	if(_pBullet)
		_pBullet->Update(pEngine);
}

void Tower::Render(Core* pEngine)
{
	if (!_enable)
		return;

	pEngine->FillCircle((int)_x, (int)_y, TOWER_SIZE);


	// bullet Render
	if (_pBullet)
		_pBullet->Render(pEngine);
}

void Tower::TimeTickInc(Core* pEngine)
{
	// 너무 커지면 증가 안하도록
	if (_timeTick > 10000.f)
		return;

	_timeTick += pEngine->GetElapsedTime();
}

void Tower::CreateBullet()
{
	if (_pBullet || !_pTarget)
		return;

	_pBullet = new Bullet;
	_pBullet->SetX(_x);
	_pBullet->SetY(_y);
	_pBullet->SetSize(2);
	_pBullet->SetEnable(true);
	_pBullet->SetTarget(_pTarget);
}

void Tower::ReleaseBullet()
{
	if (!_pBullet)
		return;

	delete _pBullet;
	_pBullet = nullptr;
}

bool Tower::CheckTargetInRange()
{
	if (!_pTarget)
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

