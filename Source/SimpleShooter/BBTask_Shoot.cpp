// @AlexDonisthorpe 2021


#include "BBTask_Shoot.h"

#include "AIController.h"
#include "Characters/ShooterCharacter.h"

UBBTask_Shoot::UBBTask_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBBTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	
	AICharacter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(!AICharacter) return EBTNodeResult::Failed;
	
	AICharacter->Shoot();

	return EBTNodeResult::Succeeded;
}
