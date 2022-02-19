// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"

#include "ActionRoguelike/ActionRoguelike.h"
#include "Net/UnrealNetwork.h"

void USAction::StartAction_Implementation(AActor* Instigator)
{
	//UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::Green);

	USActionComponent* Comp = GetOwningComponent();

	Comp->ActiveGameplayTags.AppendTags(GrantsTags);
	RepData.bIsRunning = true;
	RepData.Instigator = Instigator;
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	//UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Stopped: %s"), *ActionName.ToString()), FColor::White);
	//ensureAlways(bIsRunning);
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	RepData.bIsRunning = false;
	RepData.Instigator = Instigator;
}

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	USActionComponent* Comp = GetOwningComponent();

	if(Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	return true;
}


USAction::USAction()
{
	RepData.bIsRunning = false;
}

UWorld* USAction::GetWorld() const
{
	//UActorComponent* ActorComp = Cast<UActorComponent>(GetOuter());
	AActor* ActorComp = Cast<AActor>(GetOuter());

	if(ActorComp)
	{
		return ActorComp->GetWorld();
	}

	return nullptr;
}

bool USAction::IsRunning() const
{
	return RepData.bIsRunning;
}

void USAction::Initialize(USActionComponent* NewActionComponent)
{
	ActionComp = NewActionComponent;
}

USActionComponent* USAction::GetOwningComponent() const
{
	//return Cast<USActionComponent>(GetOuter());
	return ActionComp;
}

void USAction::OnRep_RepData()
{
	if(RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	}
	else
	{
		StopAction(RepData.Instigator);
	}
}

bool USAction::IsSupportedForNetworking() const
{
	return true;
}

void USAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(USAction, bIsRunning);
	DOREPLIFETIME(USAction, RepData);
	DOREPLIFETIME(USAction, ActionComp);
}
