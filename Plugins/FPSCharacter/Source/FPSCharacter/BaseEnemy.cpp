#include "BaseEnemy.h"

ABaseEnemy::ABaseEnemy()
{
}

ABaseEnemy::~ABaseEnemy()
{
}


void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}


void ABaseEnemy::TakeDamage(int amount)
{

}

void ABaseEnemy::Die()
{

}

void ABaseEnemy::MoveForward(float v) { if (v != 0) AddMovementInput(GetActorForwardVector(), v); }
void ABaseEnemy::MoveRight(float v) { if (v != 0) AddMovementInput(GetActorRightVector(), v); }
void ABaseEnemy::LookYaw(float v) { AddControllerYawInput(v); }
void ABaseEnemy::LookPitch(float v) { AddControllerPitchInput(v); }