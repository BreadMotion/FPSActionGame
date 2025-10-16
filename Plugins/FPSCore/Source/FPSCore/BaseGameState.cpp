#include "BaseGameState.h"
#include "Net/UnrealNetwork.h"

/**
 * @brief ゲームステートの基底クラス
 * @details
 * - ゲームステートの基本的な状態を管理します。
 */
ABaseGameState::ABaseGameState()
{
    m_score = 0;
    m_currentPhase = TEXT("Init");
}

/**
 * @brief ゲームフェーズを設定します（サーバー側のみで呼び出されるべき）
 * @param _newPhase 新しいゲームフェーズ
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
 * @brief ゲームフェーズ変更のレプリケーション通知関数
 * @details
 * - クライアント側でUIの更新などを行うために呼ばれます。
 */
void ABaseGameState::OnRep_GamePhase()
{
    UE_LOG(LogTemp, Log, TEXT("Game phase changed to: %s"), *m_currentPhase);
}

/**
 * @brief レプリケーション対象プロパティの登録
 * @details
 * - `m_score` と `m_currentPhase` をレプリケートするよう設定します。
 */
void ABaseGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ABaseGameState, m_score);
    DOREPLIFETIME(ABaseGameState, m_currentPhase);
}
