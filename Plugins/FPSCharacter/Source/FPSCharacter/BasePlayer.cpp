#include "BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"

ABasePlayer::ABasePlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	m_cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_cameraBoom->SetupAttachment(GetRootComponent());
	m_cameraBoom->TargetArmLength = 0.f;
	m_cameraBoom->bUsePawnControlRotation = true;

	m_followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	m_followCamera->SetupAttachment(m_cameraBoom);
	m_followCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

ABasePlayer::~ABasePlayer()
{
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* ic) {
	Super::SetupPlayerInputComponent(ic);
	ic->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	ic->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);
	ic->BindAxis("Turn", this, &ABasePlayer::LookYaw);
	ic->BindAxis("LookUp", this, &ABasePlayer::LookPitch);
}

void ABasePlayer::TakeDamage(int amount)
{

}

void ABasePlayer::Die()
{

}

void ABasePlayer::MoveForward(float v) { if (v != 0) AddMovementInput(GetActorForwardVector(), v); }
void ABasePlayer::MoveRight(float v) { if (v != 0) AddMovementInput(GetActorRightVector(), v); }
void ABasePlayer::LookYaw(float v) { AddControllerYawInput(v); }
void ABasePlayer::LookPitch(float v) { AddControllerPitchInput(v); }