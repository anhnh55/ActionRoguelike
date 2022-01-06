// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if(BlackboardComp)
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
		if(TargetActor)
		{
			AAIController* AIController = OwnerComp.GetAIOwner();
			if(AIController)
			{
				APawn* AIPawn = AIController->GetPawn();
				if(AIPawn)
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithinAtkRange = DistanceTo < 2000.0f;
					bool hasLOS = false;
					if(bWithinAtkRange)
					{
						hasLOS = AIController->LineOfSightTo(TargetActor);
					}

					BlackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinAtkRange && hasLOS));
				}
			}
		}
	}
}
