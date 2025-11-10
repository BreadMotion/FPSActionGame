#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * @class ABaseGameMode
 * @brief 基本的なゲームモードの基底クラスです。
 * @details
 * - ゲームの基本的な処理を行うために使用します。
 * - 主にゲームの開始処理やプレイヤーのログイン/ログアウト処理を担当します。
 * - `ABaseGameState` と連携してゲーム状態の管理も行います。
 *
 * @see ABaseGameState
 * @see UBaseGameManager
 */
UCLASS(Blueprintable)
class FPSCORE_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** @brief コンストラクタ */
	ABaseGameMode();

	/**
	 * @brief ゲーム開始時の処理
	 * @details
	 * - ゲーム開始時に呼ばれます。
	 * - `UBaseGameManager` の初期化もここで行います。
	 *
	 * @note 通常はここをオーバーライドして独自の開始処理を書きます。
	 */
	virtual void StartPlay() override;

	/**
	 * @brief プレイヤーがログインしたときの処理
	 * @param _newPlayer 新しくログインしたプレイヤーのコントローラー
	 * @details
	 * - 新規プレイヤーが参加した際に呼ばれます。
	 * - プレイヤーの初期設定や通知処理をここで行います。
	 */
	virtual void PostLogin(APlayerController* _newPlayer) override;

	/**
	 * @brief プレイヤーがログアウトしたときの処理
	 * @param _exiting ログアウトするプレイヤーのコントローラー
	 * @details
	 * - プレイヤーが退出した際に呼ばれます。
	 * - 退出に伴う後処理をここで行います。
	 */
	virtual void Logout(AController* _exiting) override;

protected:
	virtual void SetupGameStateClass();
	virtual void SetupDefaultPawnClass();
	virtual void SetupDefaultPlayerControllerClass();
	virtual void SetupDefaultPlayerStateClass();
	virtual void SetupDefaultSpectatorPawnClass();
	virtual void SetupDefaultHUDClass();

protected:
	/** @brief キャッシュされたゲームステートの参照 */
	UPROPERTY()
	class ABaseGameState* m_cachedGameState;
};
