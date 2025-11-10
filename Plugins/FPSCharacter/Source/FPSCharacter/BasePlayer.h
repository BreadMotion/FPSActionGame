// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 *
 */
UCLASS()
class FPSCHARACTER_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABasePlayer();
	~ABasePlayer();

protected:
	UPROPERTY(VisibleAnywhere) class USpringArmComponent* m_cameraBoom;
	UPROPERTY(VisibleAnywhere) class UCameraComponent* m_followCamera;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* ic) override;
	virtual void TakeDamage(int amount) override;
	virtual void Die() override;

protected:
	void MoveForward(float v);
	void MoveRight(float v);
	void LookYaw(float v);
	void LookPitch(float v);
};
