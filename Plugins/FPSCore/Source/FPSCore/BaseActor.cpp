#include "BaseActor.h"

ABaseActor::ABaseActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ABaseActor::BeginPlay()
{
    Super::BeginPlay();
    Log(TEXT("Spawned"));
}

void ABaseActor::EndPlay(const EEndPlayReason::Type _endPlayReason)
{
    Log(TEXT("Destroyed"));
    Super::EndPlay(_endPlayReason);
}

void ABaseActor::Log(const FString& _message) const
{
    UE_LOG(LogTemp, Log, TEXT("[%s] %s"), *GetName(), *_message);
}

bool ABaseActor::HasActorTag(FName TagName) const
{
    return Tags.Contains(TagName);
}