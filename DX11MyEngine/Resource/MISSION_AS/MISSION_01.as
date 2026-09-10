
uint32 groupID1 = 0;
uint32 groupID2 = 0;
uint32 enemyID = 0;


void as_main()
{
    // アリ グループ１
    groupID1 = SpawnEnemyGroup(
        ENEMY_TYPE::GIANT_ANT_Normal,
        VEC3(0.0f,0.0f,0.0f),
        50.0f,
        20,
        200.0f,
        true
    );

    // アリ グループ2
    groupID2 = SpawnEnemyGroup(
        ENEMY_TYPE::GIANT_ANT_Normal,
        VEC3(-100.0f,0.0f,100.0f),
        50.0f,
        30,
        200.0f,
        true
    );

    // 八面体 
    enemyID = SpawnEnemy(
        ENEMY_TYPE::OCTAHEDRON,
        VEC3(0.0f,150.0f,0.0f),
        VEC3(0.0f),
        600.0f,
        true
    );
}   
