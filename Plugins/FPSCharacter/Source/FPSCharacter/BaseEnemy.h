// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseEnemy.generated.h"

/**
 *
 */
UCLASS()
class FPSCHARACTER_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	~ABaseEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void TakeDamage(int amount) override;
	virtual void Die() override;

protected:
	void MoveForward(float v);
	void MoveRight(float v);
	void LookYaw(float v);
	void LookPitch(float v);
};
