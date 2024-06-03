#include "MortarTower.h"
#include "../Core.h"
#include "Enemy.h"

MortarTower::MortarTower(Core* pEngine)	:
	Tower(pEngine)
{
	_cannonBallRad = 4;
	_cannonBallSpeed = 80.f;
	_aoeRange = 20.f;
	_ATT = 8;
}

MortarTower::~MortarTower()
{
}

void MortarTower::Setting(float range, float interval, olc::Pixel color)
{
	_range = range;
	_interval = interval;
	_color = color;
}

void MortarTower::Update()
{
	if (!_enable)
		return;

	Tower::Update();

	float elapsedTime = _pEngine->GetElapsedTime();

	// 공격 업데이트
	Attack();

	// TODO: Cannon 업데이트
	if (_cannonEnable)
	{
		float dirX = _targetX - _cannonBallX;
		float dirY = _targetY - _cannonBallY;
		float dist = sqrtf(dirX * dirX + dirY * dirY);

		// Range Check & Die
		float eps = 0.2f;
		if (dist < eps)
		{
			_cannonEnable = false;
			_isAttacking = true;
			_isAttackRendering = true;
		}

		// Update Direction
		dirX /= dist;
		dirY /= dist;

		_cannonBallX += dirX * _cannonBallSpeed * elapsedTime;
		_cannonBallY += dirY * _cannonBallSpeed * elapsedTime;
	}
}

void MortarTower::Render()
{
	if (!_enable)
		return;

	Tower::Render();
}

void MortarTower::BulletRender()
{
	float elapsedTime = _pEngine->GetElapsedTime();

	if (_cannonEnable)
		_pEngine->FillCircle((int)_cannonBallX, (int)_cannonBallY, _cannonBallRad, olc::BLACK);
	
	else if (_isAttackRendering)
	{
		_timeTickforAOE += elapsedTime;

		float alpha = (1.5f - _timeTickforAOE) / 2.f;

		if (alpha < 0.f)
		{
			_isAttackRendering = false;
			_timeTickforAOE = 0.f;
		}
		else
		{
			//olc::Pixel aoeColor(235, 150, 70);

			_pEngine->SetPixelMode(olc::Pixel::ALPHA);
			_pEngine->SetPixelBlend(alpha);
			_pEngine->FillCircle((int)_cannonBallX, (int)_cannonBallY, (int)_aoeRange, olc::VERY_DARK_GREEN);
			_pEngine->SetPixelMode(olc::Pixel::NORMAL);
		}
	}
}

void MortarTower::CreateCannon()
{
	_cannonBallX = _x;
	_cannonBallY = _y;
	_targetX = _pTarget->GetX();
	_targetY = _pTarget->GetY();
	_cannonEnable = true;
}

void MortarTower::Attack()
{
	if (!CheckTargetInRange())
		return;

	if (_timeTick < _interval)
		return;

	if (_cannonEnable || _isAttacking)
		return;

	_timeTick = 0.f;
	CreateCannon();
}
