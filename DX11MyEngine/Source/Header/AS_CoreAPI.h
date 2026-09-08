#pragma once

//=========================================================================================
//
//						AngelScript内で使用するコアAPI群
//
//=========================================================================================
namespace GIGA_Engine::ScriptAPI::Core
{
	// エラーメッセージボックスの表示
	void ErrorMesageBox(const std::string& caption, const std::string& msg);

	// デルタタイムの取得
	float GetDeltaTime();
};