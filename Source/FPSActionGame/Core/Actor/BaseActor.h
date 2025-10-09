#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

UCLASS()
class FPSACTIONGAME_API ABaseActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseActor();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type _endPlayReason) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Debug")
	void Log(const FString& _message) const;

	UFUNCTION(BlueprintCallable, Category = "Tags")
	bool HasActorTag(FName _tagName) const;
};
