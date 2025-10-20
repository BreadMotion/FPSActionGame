#pragma once
#include "CoreMinimal.h"

/**
 * @class UBaseGameManager
 * @brief ゲーム全体のシステム統括クラス。
 * @details
 * - UBaseSystem を継承し、Subsystem 群の初期化・終了・レベル変更を統合管理します。
 * - ゲーム開始時にすべての UBaseSystem を自動検出して登録。
 * - レベル遷移時に全システムへ通知をブロードキャストします。
 * - ゲーム終了時に各システムの終了処理を一括実行します。
 */
class FGameManager
{
public:
	FGameManager() = default;
	~FGameManager() = default;


};
