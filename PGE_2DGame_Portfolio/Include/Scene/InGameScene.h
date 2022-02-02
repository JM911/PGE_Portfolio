#pragma once
#include "Scene.h"
#include "../pch.h"

class Core;
class Map;
class Tower;
class Enemy;
class Wave;

class InGameScene :
    public Scene
{
public:
    InGameScene(Core* pEngine);
    virtual ~InGameScene();

public:
    virtual bool Create() = 0;
    virtual void Update() override;
    virtual void Render() override;



    // 플레이어 관련 (커서, HP, Gold)
protected:
    int _curGridX = 0;
    int _curGridY = 0;
    static int _playerLife;     // 목숨은 스테이지간 이어지도록 설계
    int _playerGold = 0;        // 골드는 매 스테이지 초기화
    float _curTime = 0.f;

protected:
    void PlayerInput();
    

    // 스테이지 요소
protected:
    Map* _pMap = nullptr;
    Tower* _pTower[MAP_HEIGHT][MAP_WIDTH] = { nullptr };
    Wave* _pWave[MAX_WAVE_NUM] = { nullptr };

    int _spawnGridX = 0;
    int _spawnGridY = 0;
    int _finalGridX = 0;
    int _finalGridY = 0;

    int _curWaveIdx = 0;    // 필요 없을듯? (어차피 update, render에도 모든 웨이브를 실행)

protected:
    virtual bool MapCreate() = 0;       // 맵 제작 (하드 코딩)
    virtual bool WaveCreate() = 0;      // 웨이브 제작 (하드 코딩)
    virtual void WaveChangeDir() = 0;   // 웨이븝 방향전환 (하드 코딩)

    void TowerCreate(int gridX, int gridY);     // TODO: 나중에 타워 타입 추가

    void TowerTargetUpdate();
};

