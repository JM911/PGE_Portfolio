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

    //virtual int Cost(TOWER_TYPE type) override;
    //virtual void SelectTypeInput() override;
    //virtual void TowerSetting(int gridX, int gridY) override;

    //void TowerTypeUIRender();
};

