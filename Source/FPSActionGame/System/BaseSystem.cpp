#include "BaseSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

void UBaseSystem::Initialize(FSubsystemCollectionBase& _collection)
{
    Super::Initialize(_collection);
    m_gameStartTime = FDateTime::UtcNow();
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem initialized at %s"), *m_gameStartTime.ToString());
}

void UBaseSystem::Deinitialize()
{
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem  deinitialized."));
    Super::Deinitialize();
}

float UBaseSystem::GetPlayTimeSeconds() const
{
    return (FDateTime::UtcNow() - m_gameStartTime).GetTotalSeconds();
}

void UBaseSystem::SaveData()
{
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem : SaveData() called. Implement your save logic here."));
    // TODO: SaveGameクラスを継承したオブジェクトを作り、セーブ処理を記述
}

void UBaseSystem::LoadData()
{
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem : LoadData() called. Implement your load logic here."));
    // TODO: SaveGameオブジェクトをロードしてデータを復元
}

void UBaseSystem::PrintDebugMessage(const FString& _message) const
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("[Subsystem] %s"), *_message));
    UE_LOG(LogTemp, Log, TEXT("[Subsystem] %s"), *_message);
}
