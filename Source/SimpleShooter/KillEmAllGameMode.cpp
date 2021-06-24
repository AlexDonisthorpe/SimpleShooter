// @AlexDonisthorpe 2021


#include "KillEmAllGameMode.h"
#include "ShooterPlayerController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(PawnKilled->GetController());
	if(PlayerController != nullptr)
	{
		PlayerController->GameHasEnded(nullptr, false);
	}

	
}
