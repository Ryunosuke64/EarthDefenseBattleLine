#include "pch.h"
#include "ScriptManager.h"
#include <angelscript/add_on/scriptbuilder/scriptbuilder.h>     // ファイル読み込み用
#include <angelscript/add_on/scriptstdstring/scriptstdstring.h> // string型を使えるようにする
#include <angelscript/add_on/scriptarray/scriptarray.h>         // arrayを使えるようにする
#include <angelscript/add_on/scriptmath/scriptmath.h>           // 数学関数を使えるようにする
#include <angelscript/add_on/scripthelper/scripthelper.h>       // 数学関数を使えるようにする

using namespace Tool;

// メッセージコールバック
void MessageCallback(const asSMessageInfo* msg, void* param)
{
    const char* type = "ERR ";
    if (msg->type == asMSGTYPE_WARNING) type = "WARN";
    else if (msg->type == asMSGTYPE_INFORMATION) type = "INFO";

    printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}


//*---------------------------------------------------------------------------------------
//*【?】コンストラクタ
//*----------------------------------------------------------------------------------------
ScriptManager::ScriptManager()
{
}

//*---------------------------------------------------------------------------------------
//*【?】デストラクタ
//*----------------------------------------------------------------------------------------
ScriptManager::~ScriptManager()
{
}

//*---------------------------------------------------------------------------------------
//*【?】初期化
//*
//* [引数] 
//* なし
//* [返値]
//* true : 成功
//* false : 失敗
//*----------------------------------------------------------------------------------------
bool ScriptManager::Init()
{
    // =====================================
    // AngelScriptエンジン作成
    // =====================================
    m_pEngine = asCreateScriptEngine();
    assert(m_pEngine != nullptr);

    // メッセージコールバック登録
    int r = m_pEngine->SetMessageCallback(
        asFUNCTION(MessageCallback), 
        0, 
        asCALL_CDECL
    );
    assert(r >= 0);

    // =====================================
    // アドオンの登録
    // =====================================
    {
        // arrayアドオンの登録
        RegisterScriptArray(m_pEngine, true);

        // string型を使えるようにする
        RegisterStdString(m_pEngine);

        // 数学
        RegisterScriptMath(m_pEngine);
    }

    // =====================================
    // AS内で使用するAPIの登録
    // =====================================
    {
        // コアAPIの登録
        RegisterCoreAPI(m_pEngine);
    }

    // =====================================
    // スクリプト読み込み
    // =====================================
    // スクリプトビルダーでモジュール作成
    CScriptBuilder builder;
    r = builder.StartNewModule(m_pEngine, "MyModule");
    if (r < 0)
    {
        ErrorMessage(L"モジュール作成失敗", L"ScriptManager");
        return false;
    }

    r = builder.AddSectionFromFile("Resource/MISSION_AS/test.as");
    if (r < 0)
    {
        ErrorMessage(L"ファイル読み込み失敗\n", L"ScriptManager");
        return false;
    }
    
    
    // =====================================
    // スクリプトをコンパイル
    // =====================================
    r = builder.BuildModule();
    if (r < 0)
    {
        ErrorMessage(L"コンパイルが出来ませんでした\n", L"ScriptManager");
        return false;
    }

    // モジュール取得
    asIScriptModule* mod = m_pEngine->GetModule("MyModule");
    if (!mod)
    {
        ErrorMessage(L"モジュールが見つかりません\n", L"ScriptManager");
        return false;
    }

    // 関数取得
	asIScriptFunction* func = mod->GetFunctionByDecl("void as_main(void)");
    if (!func)
    {
        ErrorMessage(L"関数が見つかりません\n", L"ScriptManager");
        return false;
    }

    // コンテキスト作成・準備・実行
    m_pContext = m_pEngine->CreateContext();
    m_pContext->Prepare(func);
    r = m_pContext->Execute();
    if (r != asEXECUTION_FINISHED)
    {
        if (r == asEXECUTION_EXCEPTION)
        {
            ErrorMessage(StringToWstring(m_pContext->GetExceptionString()), L"ScriptManager");
        }
    }

    // 登録済みAPIを出力
    WriteConfigToFile(m_pEngine, "AngelScriptAPI.txt");

    return true;
}


//*---------------------------------------------------------------------------------------
//*【?】更新
//*
//* [引数] 
//* _deltaTime : デルタタイム
//* 
//* [返値] 
//* なし
//*----------------------------------------------------------------------------------------
void ScriptManager::Update(float _deltaTime)
{
    int r = 0;

}

//*---------------------------------------------------------------------------------------
//*【?】終了
//*
//* [引数] なし
//* [返値] なし 
//*----------------------------------------------------------------------------------------
void ScriptManager::Term()
{
    // クリーンアップ
    m_pContext->Release();
    m_pEngine->ShutDownAndRelease();
}


//*---------------------------------------------------------------------------------------
//*【?】AngelScriptのスクリプトをロードする
//*
//* [引数] 
//* _moduleName : モジュール名
//* _filePath   : ファイルパス
//* 
//* [返値] 
//* なし
//*----------------------------------------------------------------------------------------
bool ScriptManager::LoadScript(const std::string& _moduleName, const std::string& _filePath)
{
    // =====================================
    // スクリプト読み込み
    // =====================================
    // スクリプトビルダーでモジュール作成
    CScriptBuilder builder;
    int r = builder.StartNewModule(m_pEngine, _moduleName.c_str());
    if (r < 0)
    {
        ErrorMessage(L"モジュール作成失敗\n", L"ScriptManager");
        return false;
    }

    r = builder.AddSectionFromFile(_filePath.c_str());
    if (r < 0)
    {
        ErrorMessage(L"ファイル読み込み失敗\n", L"ScriptManager");
        return false;
    }

    return true;
}


//*---------------------------------------------------------------------------------------
//*【?】
//*
//* [引数] 
//* _moduleName : モジュール名
//* 
//* [返値] 
//* なし
//*----------------------------------------------------------------------------------------
bool ScriptManager::StartScript(const std::string& _moduleName)
{
    return true;
}
//*---------------------------------------------------------------------------------------
//*【?】
//*
//* [引数] 
//* _moduleName : モジュール名
//* deltaTime   : デルタタイム
//* 
//* [返値] 
//* なし
//*----------------------------------------------------------------------------------------
bool ScriptManager::UpdateScript(const std::string& _moduleName, float deltaTime)
{
    return true;
}

//*---------------------------------------------------------------------------------------
//*【?】
//*
//* [引数] 
//* _moduleName : モジュール名
//* 
//* [返値] 
//* なし
//*----------------------------------------------------------------------------------------
void ScriptManager::UnloadScript(const std::string& _moduleName)
{

}

//*---------------------------------------------------------------------------------------
//*【?】コアAPIの登録
//*
//* [引数] 
//* *engine : ASエンジン
//* 
//* [返値] 
//* なし
//*----------------------------------------------------------------------------------------
void ScriptManager::RegisterCoreAPI(asIScriptEngine* engine)
{
    int r = 0;

    // ErrorMesageBox
    engine->RegisterGlobalFunction(
        "void ErrorMesageBox(const string &in  caption, const string &in msg)",
        asFUNCTION(GIGA_Engine::ScriptAPI::Core::ErrorMesageBox),
        asCALL_CDECL
    );
    assert(r >= 0);


    // GetDeltaTime
    engine->RegisterGlobalFunction(
        "float GetDeltaTime()",
        asFUNCTION(GIGA_Engine::ScriptAPI::Core::GetDeltaTime),
        asCALL_CDECL
    );
    assert(r >= 0);
}

//*---------------------------------------------------------------------------------------
//*【?】数学APIの登録
//*
//* [引数] 
//* *engine : ASエンジン
//* 
//* [返値] 
//* なし
//*----------------------------------------------------------------------------------------
void ScriptManager::RegisterMathAPI(asIScriptEngine* engine)
{

}

//*---------------------------------------------------------------------------------------
//*【?】ゲームオブジェクトAPIの登録
//*
//* [引数] 
//* *engine : ASエンジン
//* 
//* [返値] 
//* なし
//*----------------------------------------------------------------------------------------
void ScriptManager::RegisterGameObjectAPI(asIScriptEngine* engine)
{

}

//*---------------------------------------------------------------------------------------
//*【?】オーディオAPIの登録
//*
//* [引数] 
//* *engine : ASエンジン
//* 
//* [返値] 
//* なし
//*----------------------------------------------------------------------------------------
void ScriptManager::RegisterAudioAPI(asIScriptEngine* engine)
{
    
}