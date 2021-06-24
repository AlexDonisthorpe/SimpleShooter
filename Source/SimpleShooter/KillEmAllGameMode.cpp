// @AlexDonisthorpe 2021


#include "KillEmAllGameMode.h"
#include "ShooterPlayerController.h"
#include "EngineUtils.h"
#include "ShooterAIController.h"
#include "GameFramework/Controller.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(PawnKilled->GetController());
	if(PlayerController != nullptr)
	{
		PlayerController->GameHasEnded(nullptr, false);
	}

	for(AController* Controller : TActorRange<AController>(GetWorld()))
	{
		AShooterAIController* ShooterAIController = Cast<AShooterAIController>(Controller);
		if(ShooterAIController == nullptr) return;

		// If any AI controller at all is still alive, we can return early
		if(!ShooterAIController->IsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AKillEmAllGameMode::EndGame(const bool IsPlayerWinner) const
{
	for(AController* Controller : TActorRange<AController>(GetWorld()))
	{
		const bool bIsPlayer = Controller->IsPlayerController();

		if(bIsPlayer ^ IsPlayerWinner)
		{
			Controller->GameHasEnded(Controller->GetPawn(), false);
		}
		else
		{
			Controller->GameHasEnded(Controller->GetPawn(), true);
		}
	}
}
