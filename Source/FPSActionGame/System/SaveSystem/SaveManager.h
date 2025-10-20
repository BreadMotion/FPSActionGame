#pragma once
#include "CoreMinimal.h"
#include "SaveDataStructures.h"
#include "LocalSaveHandler.h"
#include "RemoteSaveHandler.h"

/**
 * セーブ処理のファサード
 * - ローカル/リモート両対応（設定で切り替え可）
 * - Subsystemから直接呼ばれる
 */
class FSaveManager
{
public:
	FSaveManager() = default;
	~FSaveManager() = default;

	void Initialize();
	void Shutdown();

	void SaveAll();
	void LoadAll();

private:
	TUniquePtr<FLocalSaveHandler> m_localHandler;
	TUniquePtr<FRemoteSaveHandler> m_remoteHandler;

	bool m_bUseRemote = false; // 将来的にクラウド連携を導入するためのフラグ
};
