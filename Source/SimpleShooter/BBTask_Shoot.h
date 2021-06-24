// @AlexDonisthorpe 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "BBTask_Shoot.generated.h"

class AShooterCharacter;
UCLASS()
class SIMPLESHOOTER_API UBBTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()

	public:
	UBBTask_Shoot();

	AShooterCharacter* AICharacter;
	
	private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
