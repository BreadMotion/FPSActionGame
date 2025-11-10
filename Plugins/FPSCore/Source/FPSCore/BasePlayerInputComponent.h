#pragma once
#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "BasePlayerInputComponent.generated.h"

/**
 * @class UBasePlayerInputComponent
 * @brief プレイヤー用の入力コンポーネント拡張。
 * @details UInputComponent の薄いラッパ。共通バインドやヘルパを集約する。
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FPSCORE_API UBasePlayerInputComponent : public UInputComponent
{
	GENERATED_BODY()
public:
	/** @brief デフォルトコンストラクタ */
	UBasePlayerInputComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** @brief 共通アクションをまとめてバインドするヘルパ */
	void BindCommonActions(AActor* OwnerActor);
};