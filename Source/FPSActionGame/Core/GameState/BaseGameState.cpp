#include "GameState/BaseGameState.h"
#include "Net/UnrealNetwork.h"

/**
 * @brief コンストラクタ。
 * @details
 * - 初期スコアとフェーズを設定します。
 */
ABaseGameState::ABaseGameState()
{
    m_score = 0;
    m_currentPhase = TEXT("Init");
}

/**
 * @brief ゲームフェーズを変更します（サーバーのみ実行）。
 * @param _newPhase 新しいフェーズ名。
 */
void ABaseGameState::SetGamePhase(const FString& _newPhase)
{
    if (HasAuthority())
    {
        m_currentPhase = _newPhase;
        OnRep_GamePhase();
    }
}

/**
 * @brief フェーズ変更時のイベント。
 * @details
 * - クライアント側でのみ呼ばれ、UI更新などに利用できます。
 */
void ABaseGameState::OnRep_GamePhase()
{
    UE_LOG(LogTemp, Log, TEXT("Game phase changed to: %s"), *m_currentPhase);
}

/**
 * @brief レプリケーション設定。
 * @details
 * - `Score` と `CurrentPhase` をクライアントへ同期します。
 */
void ABaseGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ABaseGameState, m_score);
    DOREPLIFETIME(ABaseGameState, m_currentPhase);
}
