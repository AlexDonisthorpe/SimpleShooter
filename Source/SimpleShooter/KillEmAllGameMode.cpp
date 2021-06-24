// @AlexDonisthorpe 2021


#include "KillEmAllGameMode.h"
#include "ShooterPlayerController.h"
#include "EngineUtils.h"
#include "ShooterAIController.h"
#include "GameFramework/Controller.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	UE_LOG(LogTemp, Warning, TEXT("PawnIsKilled"));
	Super::PawnKilled(PawnKilled);

	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(PawnKilled->GetController());
	if(PlayerController != nullptr)
	{
		EndGame(false);
	}

	for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		// If any AI controller at all is still alive, we can return early
		if(!Controller->IsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AKillEmAllGameMode::EndGame(const bool bIsPlayerWinner) const
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}

}
