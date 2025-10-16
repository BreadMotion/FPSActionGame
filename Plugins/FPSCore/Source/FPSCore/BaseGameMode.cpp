#include "BaseGameMode.h"
#include "BaseGameState.h"
#include "BaseGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

/**
 * @brief �Q�[�����[�h�̃R���X�g���N�^
 * @details
 * - `GameStateClass` �� `ABaseGameState` ��ݒ肷��
 */
ABaseGameMode::ABaseGameMode()
{
	GameStateClass = ABaseGameState::StaticClass();
}

/**
 * @brief �Q�[���J�n���̏���
 * @details
 * - `ABaseGameState` �̃L���b�V����ێ����A�Q�[���}�l�[�W���[�ɒʒm����
 * - `UBaseGameManager` �ɃQ�[���J�n�̃u���[�h�L���X�g�𑗂�
 */
void ABaseGameMode::StartPlay()
{
	Super::StartPlay();

	m_cachedGameState = GetGameState<ABaseGameState>();

	if (UBaseGameManager* GameManager = Cast<UBaseGameManager>(GetGameInstance()))
	{
		GameManager->BroadcastGameStateChanged(TEXT("StartPlay"));
	}

	UE_LOG(LogTemp, Log, TEXT("GameMode: StartPlay called."));
}

/**
 * @brief �v���C���[�����O�C���������̏���
 * @param NewPlayer ���O�C�������v���C���[�R���g���[���[
 */
void ABaseGameMode::PostLogin(APlayerController* _newPlayer)
{
	Super::PostLogin(_newPlayer);
	UE_LOG(LogTemp, Log, TEXT("Player joined: %s"), *_newPlayer->GetName());
}

/**
 * @brief �v���C���[�����O�A�E�g�������̏���
 * @param Exiting ���O�A�E�g����v���C���[�R���g���[���[
 */
void ABaseGameMode::Logout(AController* _exiting)
{
	Super::Logout(_exiting);
	UE_LOG(LogTemp, Log, TEXT("Player left: %s"), *_exiting->GetName());
}
