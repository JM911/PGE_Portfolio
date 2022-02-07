#include "NormalTower.h"
#include "../Core.h"
#include "Bullet.h"
#include "Enemy.h"

NormalTower::NormalTower(Core* pEngine)	:
	Tower(pEngine)
{
	_type = TOWER_TYPE::NORMAL;
}

NormalTower::~NormalTower()
{
	SAFE_DELETE(_pBullet);
}
void NormalTower::Setting(float range, float interval, olc::Pixel color)
{
	_range = range;
	_interval = interval;
	_color = color;
}

void NormalTower::Update()
{
	if (!_enable)
		return;

	Tower::Update();


	// ���� ������Ʈ
	TimeTickInc();
	Attack();

	// �Ѿ� ���� üũ
	if (_pBullet && !(_pBullet->GetEnable()))
		SAFE_DELETE(_pBullet);

	// bullet Update
	if (_pBullet)
		_pBullet->Update();
}

void NormalTower::Render()
{
	if (!_enable)
		return;

	Tower::Render();

	// bullet Render
	if (_pBullet)
		_pBullet->Render();
}


void NormalTower::TimeTickInc()
{
	// �ʹ� Ŀ���� ���� ���ϵ���
	if (_timeTick > 10000.f)
		return;

	_timeTick += _pEngine->GetElapsedTime();
}

void NormalTower::CreateBullet()
{
	if (_pBullet || !_pTarget)
		return;

	_pBullet = new Bullet(_pEngine);
	_pBullet->Create(_x, _y, _pTarget);
	_pBullet->Setting(2, 150.f, 1);		// TODO: ���� ���� �ý����� ���ٸ� �������� �ٸ� ���ݷ�
}

void NormalTower::Attack()
{
	if (!CheckTargetInRange())
		return;

	if (_timeTick < _interval || (_pBullet && _pBullet->GetEnable()))
		return;

	_timeTick = 0.f;
	CreateBullet();
}
