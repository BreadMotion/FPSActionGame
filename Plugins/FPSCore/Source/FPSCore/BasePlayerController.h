#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UBasePlayerInputComponent;

/**
 * @class FBasePlayerController
 * @brief プレイヤー操作を管理するコントローラーの基底クラス
 * @details
 *  - プレイヤーの入力処理や視点制御などを担当します。
 */
UCLASS()
class FPSCORE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	~ABasePlayerController();

protected:
	/**
	* @brief 入力コンポーネントの初期化
	* @details ここで UBasePlayerInputComponent を生成し push する
	*/
	virtual void SetupInputComponent() override;
};
