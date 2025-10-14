#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * @class ABaseGameMode
 * @brief ゲーム全体のルールや進行を管理する基本GameModeクラス。
 * @details
 * - サーバー側でのみ動作します（クライアントには存在しません）。
 * - プレイヤーの参加／退出、ラウンド制御、開始・終了処理などを担当します。
 * - `ABaseGameState` と連携し、ゲームの状態を同期します。
 *
 * @see ABaseGameState
 * @see UBaseGameManager
 */
UCLASS(Blueprintable)
class FPSACTIONGAME_API ABaseGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    /** @brief コンストラクタ */
    ABaseGameMode();

    /**
     * @brief ゲーム開始処理。
     * @details
     * - レベルがロードされ、全てのアクターが初期化された後に呼ばれます。
     * - `UBaseGameManager` へゲーム開始を通知します。
     *
     * @note サーバー側のみ呼ばれます。
     */
    virtual void StartPlay() override;

    /**
     * @brief プレイヤー参加時イベント。
     * @param NewPlayer 参加したプレイヤーのコントローラ。
     * @details
     * - 新規プレイヤーがログインしたタイミングで呼ばれます。
     * - 必要に応じてプレイヤー固有の初期化処理を行います。
     */
    virtual void PostLogin(APlayerController* NewPlayer) override;

    /**
     * @brief プレイヤー退出時イベント。
     * @param Exiting 退出するプレイヤーのコントローラ。
     * @details
     * - プレイヤーがゲームから離脱した際に呼ばれます。
     */
    virtual void Logout(AController* Exiting) override;

protected:
    /** @brief 現在のゲームステート（キャッシュ）。 */
    UPROPERTY()
    class ABaseGameState* CachedGameState;
};
