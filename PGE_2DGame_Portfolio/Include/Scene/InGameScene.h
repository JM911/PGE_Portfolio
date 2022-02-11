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



    // �÷��̾� ���� (Ŀ��, HP, Gold)
protected:
    int _curGridX = 0;
    int _curGridY = 0;
    static int _playerLife;     // ����� ���������� �̾������� ����
    int _playerGold = 0;        // ���� �� �������� �ʱ�ȭ
    float _curTime = 0.f;

protected:
    void PlayerInput();
    
public:
    void GetReward(int reward);
    

    // �������� ���
protected:
    Map* _pMap = nullptr;
    Tower* _pTower[MAP_HEIGHT][MAP_WIDTH] = { nullptr };
    Wave* _pWave[MAX_WAVE_NUM] = { nullptr };

    int _spawnGridX = 0;
    int _spawnGridY = 0;
    int _finalGridX = 0;
    int _finalGridY = 0;

    int _curWaveIdx = 0;    // �ʿ� ������? (������ update, render���� ��� ���̺긦 ����)

    int _lastWaveIdx = MAX_WAVE_NUM;
    float _timeTickforNextStage = 0.f;

    float _timeTickforGameOver = 0.f;

protected:
    virtual bool MapCreate() = 0;       // �� ���� (�ϵ� �ڵ�)
    virtual bool WaveCreate() = 0;      // ���̺� ���� (�ϵ� �ڵ�)
    virtual void WaveChangeDir() = 0;   // ���̺� ������ȯ (�ϵ� �ڵ�)

    void TowerCreate(int gridX, int gridY, TOWER_TYPE type);     // TODO: ���߿� Ÿ�� Ÿ�� �߰�

    void TowerTargetUpdate();

    // Ÿ�� �Ǽ� ����
protected:
    TOWER_TYPE _towerType = TOWER_TYPE::NORMAL;

    virtual int Cost(TOWER_TYPE type) = 0;  // Ÿ�� Ÿ�Ժ� ���� ����(�ϵ� �ڵ�)
    virtual void SelectTypeInput() = 0;     // Ÿ�Ժ� �Է� Ű ����(�ϵ� �ڵ�)
    virtual void TowerSetting(int gridX, int gridY) = 0;    // Ÿ�Ժ� ���� ��ġ ����(�ϵ� �ڵ�)
    // => ���� ��� �ʿ��� Ÿ�� ������ �����Ѵٸ� �ٸ� ������� �����丵 ���



    // ����� Ÿ����
protected:
    vector<pair<int, int>> _vecDTGrid;

    void DebuffAttack();
};

