#pragma once
#include "../pch.h"

class Core;

class Obj
{
public:
	Obj();
	virtual ~Obj();

public:
	virtual void Update(Core* pEngine) = 0;
	virtual void Render(Core* pEngine) = 0;


protected:
	float _x = 0.f;
	float _y = 0.f;
	olc::Pixel _color = olc::BLACK;

	// Get
public:
	float GetX() const { return _x; }
	float GetY() const { return _y; }
	olc::Pixel GetColor() const { return _color; }

	// Set
public:
	void SetX(float x) { _x = x; }
	void SetY(float y) { _y = y; }
	void SetColor(olc::Pixel color) { _color = color; }
};

