#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseGameState.generated.h"

/**
 * @class ABaseGameState
 * @brief ゲーム全体の進行状態を保持・同期する基本クラス。
 * @details
 * - スコア、フェーズ、残り時間などの進行情報を管理します。
 * - サーバーと全クライアント間で同期されます。
 * - `ABaseGameMode` と連携して状態遷移を制御します。
 *
 * @see ABaseGameMode
 * @see UBaseGameManager
 */
UCLASS(Blueprintable)
class FPSACTIONGAME_API ABaseGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    /** @brief コンストラクタ */
    ABaseGameState();

    /** @brief 現在のスコア（同期されます） */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameState")
    int32 Score;

    /** @brief 現在のゲームフェーズ（例："Init"、"InGame"、"Result"） */
    UPROPERTY(ReplicatedUsing = OnRep_GamePhase, BlueprintReadOnly, Category = "GameState")
    FString CurrentPhase;

    /**
     * @brief サーバーでゲームフェーズを変更します。
     * @param NewPhase 新しいフェーズ名。
     */
    UFUNCTION(BlueprintCallable, Category = "GameState")
    void SetGamePhase(const FString& NewPhase);

protected:
    /** @brief フェーズ変更時に呼ばれるイベント（クライアント側で発火）。 */
    UFUNCTION()
    void OnRep_GamePhase();

    /** @brief 変数のレプリケーション設定。 */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
