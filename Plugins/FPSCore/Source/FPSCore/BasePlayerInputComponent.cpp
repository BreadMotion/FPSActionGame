#include "BasePlayerInputComponent.h"
#include "GameFramework/Actor.h"

UBasePlayerInputComponent::UBasePlayerInputComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// •K—v‚È‚ç‰Šúİ’è
}

void UBasePlayerInputComponent::BindCommonActions(AActor* OwnerActor)
{
	check(this);
	// —á:
	// BindAction("Pause", IE_Pressed, OwnerActor, &AOwnerType::OnPausePressed);
}