#include "Tower.h"
#include "../Core.h"

Tower::Tower(int gridX, int gridY)	:
	_gridX(gridX), _gridY(gridY)
{
	// 원모양 타워의 중심으로 세팅
	_x = float(MAP_POS_X + TILE_SIZE * _gridX + TILE_SIZE / 2);
	_y = float(MAP_POS_Y + TILE_SIZE * _gridY + TILE_SIZE / 2);
}

Tower::~Tower()
{
}

void Tower::Update(Core* pEngine)
{
	if (!_enable)
		return;
	
}

void Tower::Render(Core* pEngine)
{
	if (!_enable)
		return;

	pEngine->FillCircle((int)_x, (int)_y, TOWER_SIZE);
}

