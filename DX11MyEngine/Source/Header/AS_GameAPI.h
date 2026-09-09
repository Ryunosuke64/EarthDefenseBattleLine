#pragma once

//=========================================================================================
//
//						AngelScript内で使用するゲームAPI群
//
//=========================================================================================
namespace GIGA_Engine::ScriptAPI::Game
{
	// ミッション開始からの時間を取得
	float GetMissionTime();

	// エネミーの出現（単体）
	// タイプ・位置・回転・攻撃状態か
	u_int SpawnEnemy(EnemyData::ENEMY_TYPE type,const VECTOR3::VEC3& pos, const VECTOR3::VEC3& rot, bool isAgro);

	// エネミーグループ出現
	// タイプ・位置・出現範囲・出現数・攻撃状態か
	u_int SpawnEnemyGroup(EnemyData::ENEMY_TYPE type, const VECTOR3::VEC3& pos, float spawnRadius, u_int count, bool isAgro);

	// 指定IDのエネミーが倒されたか
	bool IsEnemyDead(u_int enemyID);

	// 指定IDのエネミーグループがすべて倒されたか
	bool IsEnemyGroupDestroyed(u_int groupID);

	// 指定IDのエネミーグループの生存数を取得
	int GetEnemyGroupAliveCount(u_int groupID);

	// エネミーの生存数を取得
	int GetAliveEnemyCount();

	// プレイヤーが指定エリア内に入ったか
	bool IsPlayerInArea(const VECTOR3::VEC3& pos, float radius);

	// イベント：空爆
	void EventAirstrike();

	// 無線の再生
	void PlayMessage(const std::string& msg);


};