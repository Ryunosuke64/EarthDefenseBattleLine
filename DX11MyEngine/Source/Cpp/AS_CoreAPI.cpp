#include "pch.h"
#include "AS_CoreAPI.h"

//=========================================================================================
// エラーメッセージボックスの表示
//=========================================================================================
void GIGA_Engine::ScriptAPI::Core::
ErrorMesageBox(const std::string& caption, const std::string& msg)
{
    // ワイド文字列に変換
    std::wstring wcaption = Tool::StringToWstring(caption);
    std::wstring wmsg = Tool::StringToWstring(msg);

    MessageBoxW(NULL, wmsg.c_str(), wcaption.c_str(), MB_OK);
}

//=========================================================================================
// デルタタイムの取得
//=========================================================================================
float GIGA_Engine::ScriptAPI::Core::
GetDeltaTime()
{
    return Master::m_pTimeManager->get_DeltaTime();
}