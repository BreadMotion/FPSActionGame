#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class FPSCHARACTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Param")
	int m_health = -1;

	UPROPERTY(BlueprintReadWrite, Category = "Param")
	int m_maxHealth = -1;

public:
	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void TakeDamage(int _amount);

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "Character")
	bool IsDead() const { return m_health <= 0; }
};