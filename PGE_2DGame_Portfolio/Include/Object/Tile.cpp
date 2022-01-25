#include "Tile.h"
#include "../Core.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::Update(Core* pEngine)
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
	}
}

void Tile::Render(Core* pEngine)
{
	pEngine->FillRect((int)_x, (int)_y, _size, _size, _color);
	pEngine->DrawRect((int)_x, (int)_y, _size, _size, olc::BLACK);
}
