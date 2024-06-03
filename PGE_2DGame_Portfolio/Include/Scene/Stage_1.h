#pragma once
#include "InGameScene.h"
class Stage_1 :
    public InGameScene
{
public:
    Stage_1(Core* pEngine);
    virtual ~Stage_1();

public:
    virtual bool Create() override;
    virtual void Update() override;
    virtual void Render() override;

private:
    virtual bool MapCreate() override;
    virtual bool WaveCreate() override;
    virtual void WaveChangeDir() override;
};

