// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupActor_HealthPotion.h"

#include "SPlayerState.h"
#include "ActionRoguelike/SAttributeComponent.h"

void ASPowerupActor_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{
			if (PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
			{
				//if healed successfully
				HideAndCooldownPowerup();
			}
		}
	}
}

ASPowerupActor_HealthPotion::ASPowerupActor_HealthPotion()
{
	CreditCost = 50;
}
