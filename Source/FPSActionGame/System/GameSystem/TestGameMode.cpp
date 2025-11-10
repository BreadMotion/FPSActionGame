#include "TestGameMode.h"
#include "FPSCore/BaseGameState.h"
#include "FPSCharacter/BasePlayer.h"
#include "UObject/ConstructorHelpers.h"

ATestGameMode::ATestGameMode()
	: Super() 
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerBPClass(
		TEXT("/Character/Player/BP_Player")
	);
	if (PlayerBPClass.Succeeded())
		DefaultPawnClass = PlayerBPClass.Class;
	else
		DefaultPawnClass = ABasePlayer::StaticClass();
	
	GameStateClass = ABaseGameState::StaticClass();
}
