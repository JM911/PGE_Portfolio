#pragma once
#include "InGameScene.h"

class StageTest :
    public InGameScene
{
public:
    StageTest(Core* pEngine);
    virtual ~StageTest();

public:
    virtual bool Create() override;
    virtual void Update() override;
    virtual void Render() override;

private:
    virtual bool MapCreate() override;
    virtual bool WaveCreate() override;    
    virtual void WaveChangeDir() override; 
};

