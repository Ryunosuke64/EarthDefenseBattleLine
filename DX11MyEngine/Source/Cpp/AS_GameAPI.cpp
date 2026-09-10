#include "pch.h"
#include "AS_GameAPI.h"

using namespace EnemyData;

//=========================================================================================
// ミッション開始からの時間を取得
//=========================================================================================
float GIGA_Engine::ScriptAPI::Game::
GetMissionTime()
{
	return 0.0f;
}

//=========================================================================================
// エネミーの出現（単体）
// タイプ・位置・回転・HP・攻撃状態か
//=========================================================================================
uint32_t GIGA_Engine::ScriptAPI::Game::
SpawnEnemy(EnemyData::ENEMY_TYPE type, const VECTOR3::VEC3& pos, const VECTOR3::VEC3& rot, float hp, bool isAggro)
{
	EnemySpawnData spawnData;
	spawnData.enemyType = type;
	spawnData.isAggro = isAggro;
	spawnData.position = pos;
	spawnData.rotation = rot;
	spawnData.hp = hp;

	return EnemyFactory::SpawnEnemy(spawnData);
}

//=========================================================================================
// エネミーグループ出現
// タイプ・位置・出現範囲・出現数・HP・攻撃状態か
//=========================================================================================
uint32_t GIGA_Engine::ScriptAPI::Game::
SpawnEnemyGroup(EnemyData::ENEMY_TYPE type, const VECTOR3::VEC3& pos, float spawnRadius, u_int count, float hp, bool isAggro)
{
	EnemyGroupSpawnData spawnData;
	spawnData.enemyType = type;
	spawnData.position = pos;
	spawnData.spawnRadius = spawnRadius;
	spawnData.isAggro = isAggro;
	spawnData.count = count;
	spawnData.hp = hp;

	return EnemyFactory::SpawnEnemyGroup(spawnData);
}
