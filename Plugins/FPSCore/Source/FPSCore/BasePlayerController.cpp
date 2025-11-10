#include "BasePlayerController.h"
#include "BasePlayerInputComponent.h"

ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ABasePlayerController::~ABasePlayerController()
{
	// 親の生成をスキップし、自前型で生成
	InputComponent = NewObject<UBasePlayerInputComponent>(this, UBasePlayerInputComponent::StaticClass());
	check(InputComponent);
	InputComponent->RegisterComponent();

	// PlayerController に有効化
	PushInputComponent(InputComponent);

	// 共通アクションのバインド（任意）
	if (UBasePlayerInputComponent* Typed = Cast<UBasePlayerInputComponent>(InputComponent))
	{
		Typed->BindCommonActions(this);
	}

	// 追加で Controller 側のバインドがあればここに書く
	// InputComponent->BindAxis("Turn", this, &ABasePlayerController::AddYawInput);
}
