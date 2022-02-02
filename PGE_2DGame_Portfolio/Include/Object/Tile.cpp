#include "Tile.h"
#include "../Core.h"

Tile::Tile(Core* pEngine)	:
	Obj(pEngine)
{
}

Tile::~Tile()
{
}

bool Tile::Create(float offsetX, float offsetY, int gridX, int gridY, int size)
{
	_offsetX = offsetX;
	_offsetY = offsetY;
	_gridX = gridX;
	_gridY = gridY;
	_size = size;

	_x = _offsetX + (float)(_gridX * _size);
	_y = _offsetY + (float)(_gridY * _size);

	//_type = type;
	//TileColorUpdate();

	return true;
}

void Tile::Update()
{
}

void Tile::Render()
{
	_pEngine->FillRect((int)_x, (int)_y, _size, _size, _color);
	_pEngine->DrawRect((int)_x, (int)_y, _size, _size, olc::BLACK);
}

void Tile::TileColorUpdate()
{
	switch (_type)
	{
	case TILE_TYPE::NONE:
		_color = olc::BLACK;
		break;
	case TILE_TYPE::PATH:
		_color = olc::DARK_YELLOW;
		break;
	case TILE_TYPE::ABLE:
		_color = olc::GREEN;
		break;
	case TILE_TYPE::UNABLE:
		_color = olc::DARK_RED;
		break;
	default:
		_color = olc::BLACK;
		break;
	}
}
