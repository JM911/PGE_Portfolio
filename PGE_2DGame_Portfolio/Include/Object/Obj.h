#pragma once
#include "../pch.h"

class Core;

class Obj
{
public:
	Obj(Core* pEngine);
	virtual ~Obj();

public:
	virtual void Update() = 0;
	virtual void Render() = 0;


protected:
	Core* _pEngine;

	float _x = 0.f;
	float _y = 0.f;
	olc::Pixel _color = olc::BLACK;
	int _size = 0;

	// Get
public:
	float GetX() const { return _x; }
	float GetY() const { return _y; }
	olc::Pixel GetColor() const { return _color; }
	int GetSize() const { return _size; }

	// Set
public:
	void SetX(float x) { _x = x; }
	void SetY(float y) { _y = y; }
	void SetColor(olc::Pixel color) { _color = color; }
	void SetSize(int size) { _size = size; }
};

