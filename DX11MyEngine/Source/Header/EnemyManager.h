#pragma once
#include "EnemyFactory.h"

using EnemyGroupID = uint32_t;

// ***************************************************************************************
// ---------------------------------------------------------------------------------------
/* --- @:BuildingManager Class --- */
//
//  ★★★シングルトン★★★
//
// 【?】建物の管理
//
// ***************************************************************************************
class EnemyManager
{
private:


public:

public:
    EnemyManager();
    ~EnemyManager();


private:
    // コピー禁止
    EnemyManager(const EnemyManager&) = delete;
    EnemyManager& operator=(const EnemyManager&) = delete;

};
