// @AlexDonisthorpe 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

	private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WinScreenClass;

	FTimerHandle RestartTimer;
		
	public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;


};
