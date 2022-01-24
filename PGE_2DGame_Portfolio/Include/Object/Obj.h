#pragma once

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
	int _x = 0;
	int _y = 0;

	// Get
public:
	int GetX() const { return _x; }
	int GetY() const { return _y; }

	// Set
public:
	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
};

