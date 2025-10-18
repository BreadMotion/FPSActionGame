#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::TakeDamage(int _amount)
{
    m_health = FMath::Clamp(m_health - _amount, 0.f, m_maxHealth);
    if (IsDead()) Die();
}

void ABaseCharacter::Die()
{
    UE_LOG(LogTemp, Warning, TEXT("%s has died."), *GetName());
    Destroy();
}
