#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Update(class Core* pEngine) = 0;
	virtual void Render(class Core* pEngine) = 0;
};
