#include "DebuffTower.h"
#include "../Core.h"

DebuffTower::DebuffTower(Core* pEngine) :
	Tower(pEngine)
{
	_type = TOWER_TYPE::DEBUFF;
}

DebuffTower::~DebuffTower()
{
}

void DebuffTower::Setting(float range, float interval, olc::Pixel color)
{
	_range = range;
	_interval = interval;
	_color = color;
}

void DebuffTower::Update()
{
	if (!_enable)
		return;

	Tower::Update();

	Attack();
}

void DebuffTower::Render()
{
	if (!_enable)
		return;

	Tower::Render();
}

void DebuffTower::BulletRender()
{
	if (!_enable)
		return;

	if (_attEnable)
	{
		_pEngine->DrawCircle((int)_x, (int)_y, (int)_curRadius, olc::DARK_BLUE);
	}
}

void DebuffTower::Attack()
{
	if (!_attEnable && (!CheckTargetInRange() || _timeTick < _interval))
		return;

	if (_curRadius > _range)
	{
		_timeTick = 0.f;
		_curRadius = 0.f;
		_attEnable = false;
		return;
	}

	_attEnable = true;
	_curRadius += _attSpeed * _pEngine->GetElapsedTime();
}
