#pragma once
#include "CoreMinimal.h"
#include "BaseGameManager.generated.h"

/**
 * @class UBaseGameManager
 * @brief ゲーム全体のライフサイクルとサブシステムを統括管理するクラス。
 * @details
 * - ゲーム全体で唯一存在する `UGameInstance` 派生クラスです。
 * - 各種 `UBaseSystem`（サブシステム）との連携・イベント通知を行います。
 * - レベル遷移、ゲーム状態変更、セーブ／ロード、設定永続化など、
 *   ゲーム全般の中核的な管理機能を提供します。
 *
 * @see UBaseSystem
 */
UCLASS(Blueprintable)
class FPSACTIONGAME_API UBaseGameManager : public UGameInstance
{
    GENERATED_BODY()

public:
    /**
     * @brief ゲームインスタンス初期化処理。
     * @details
     * - Unreal Engine のゲームインスタンス生成時に自動的に呼ばれます。
     * - サブシステムの初期化は Unreal によって自動的に行われるため、
     *   本関数では主に内部状態やレベル情報の初期化を行います。
     *
     * @note `UGameInstance::Init()` のオーバーライドです。
     * @see OnStart()
     */
    virtual void Init() override;
    
    /**
     * @brief ゲーム開始時の処理。
     * @details
     * - 実際にプレイが開始されるタイミングで呼び出されます。
     * - 現在のレベル名を取得し、ゲーム開始時の状態を確定します。
     *
     * @note `UGameInstance::OnStart()` のオーバーライドです。
     * @see Init()
     */
    virtual void OnStart() override;

    /**
     * @brief レベル遷移イベントを全サブシステムに通知します。
     * @param OldLevel 遷移前のレベル名。
     * @param NewLevel 遷移後のレベル名。
     *
     * @details
     * - 登録済みの全 `UBaseSystem` 継承クラスに対して
     *   `OnLevelChanged()` を呼び出し、レベル変更を通知します。
     * - サブシステムはこのイベントを利用して、
     *   データリロードやステート更新などを行うことができます。
     *
     * @see BroadcastGameStateChanged()
     * @see UBaseSystem::OnLevelChanged()
     */
    void BroadcastLevelChanged(const FString& OldLevel, const FString& NewLevel);

    /**
     * @brief ゲーム状態の変化を全サブシステムに通知します。
     * @param StateName 状態名（例："Pause"、"Resume"、"GameOver"など）。
     *
     * @details
     * - 全 `UBaseSystem` 継承クラスに対して `OnGameStateChanged()` を呼び出します。
     * - 各サブシステムはこのイベントを契機に、一時停止や再開、
     *   統計ログ送信などの個別処理を行うことができます。
     *
     * @see BroadcastLevelChanged()
     * @see UBaseSystem::OnGameStateChanged()
     */
    void BroadcastGameStateChanged(const FString& StateName);

private:
    /**
     * @brief 現在のアクティブレベル名。
     * @details
     * - `OnStart()` 時に初期化され、レベル遷移時に更新されます。
     * - デバッグやセーブデータ参照など、各種システムで利用可能です。
     */
    FString m_currentLevel;
};