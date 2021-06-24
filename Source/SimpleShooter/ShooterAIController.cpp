// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if(AIBehaviorTree)
	{
		RunBehaviorTree(AIBehaviorTree);

		BlackboardComponent = GetBlackboardComponent();
		
		BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

/*void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(PlayerPawn)
	{
		if(LineOfSightTo(PlayerPawn))
		{
			FVector PlayerLocation = PlayerPawn->GetActorLocation();
			
			BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerLocation);
			BlackboardComponent->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerLocation);
		}
		else
		{
			BlackboardComponent->ClearValue(TEXT("PlayerLocation"));
		}
	}
}*/
