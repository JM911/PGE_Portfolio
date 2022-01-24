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
}

void Tile::Render(Core* pEngine)
{
	pEngine->FillRect(_x, _y, _size, _size);
}
