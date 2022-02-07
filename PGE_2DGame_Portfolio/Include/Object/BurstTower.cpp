#include "BurstTower.h"
#include "../Core.h"
#include "Bullet.h"
#include "Enemy.h"

BurstTower::BurstTower(Core* pEngine)	:
	Tower(pEngine)
{
	_type = TOWER_TYPE::BURST;
}

BurstTower::~BurstTower()
{
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		SAFE_DELETE(_pBullet[i]);
	}
}

void BurstTower::Setting(int maxBurstNum, float range, float interval, olc::Pixel color)
{
	_maxBurstNum = maxBurstNum;
	_range = range;
	_interval = interval;
	_color = color;
}

void BurstTower::Update()
{
	if (!_enable)
		return;

	Tower::Update();

	// ���� ������Ʈ
	TimeTickInc();
	Attack();

	for (int i = 0; i < _maxBurstNum; i++)
	{
		// �Ѿ� ���� üũ
		if (_pBullet[i] && !(_pBullet[i]->GetEnable()))
			SAFE_DELETE(_pBullet[i]);

		// bullet Update
		if (_pBullet[i])
			_pBullet[i]->Update();
	}
}

void BurstTower::Render()
{
	if (!_enable)
		return;

	Tower::Render();

	// bullet Render
	for (int i = 0; i < _maxBurstNum; i++)
	{
		if (_pBullet[i])
			_pBullet[i]->Render();
	}
}

void BurstTower::TimeTickInc()
{
	// �ʹ� Ŀ���� ���� ���ϵ���
	if (_timeTick > 10000.f)
		return;

	_timeTick += _pEngine->GetElapsedTime();
}

void BurstTower::CreateBullet()
{
	if (_pBullet[_curIdx] || !_pTarget)
		return;

	_pBullet[_curIdx] = new Bullet(_pEngine);
	_pBullet[_curIdx]->Create(_x, _y, _pTarget);
	_pBullet[_curIdx]->Setting(2, 150.f, 1);

	_curIdx++;
}

void BurstTower::Attack()
{
	if (!CheckTargetInRange())
		return;

	if (_timeTick < _burstInterval || (_pBullet[_curIdx] && _pBullet[_curIdx]->GetEnable()))
		return;

	// ���� ��
	if (_curIdx < _maxBurstNum)
	{
		_timeTick = 0.f;
		CreateBullet();
		return;
	}

	// ���� ���� �� ���
	if (_timeTick < _interval)
		return;

	// ���� ���� �غ�
	_timeTick = 0.f;
	_curIdx = 0;
}
