
void as_main()
{
    float deltaTime = GetDeltaTime();
    string deltaTimeStr = deltaTime;
    ErrorMesageBox("デルタタイム",deltaTimeStr);
}   


// void mission_update()
// {   
//     PlayerPosition(VEC3(-100.0f,0.0f,200.0f));
//     PlayerRotation(VEC3(0.0f,0.0f,0.0f));

//     // タイプ・位置・出現範囲・数・攻撃状態
//     SpawnEnemyGroupe(ENMEY::ANT, VEC3(300.0f,0.0f,100.0f), 30.0f, 50,true);

//     if(EnemyAllDestoroy() == false)
//     {
//         return;
//     }

//     SpawnEnemyGroupe(ENMEY::ANT, VEC3(300.0f,0.0f,100.0f), 30.0f, 50, true);
//     SpawnEnemyGroupe(ENMEY::DRONE, VEC3(300.0f,390.0f,100.0f), 100.0f, 30, true);



// }