// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionEffect.h"
#include "ActionRoguelike/SAttributeComponent.h"
#include "SActionEffect_Thorn.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USActionEffect_Thorn : public USActionEffect
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Thorns")
		float ReflectFraction;

	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

public:

	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;

	USActionEffect_Thorn();
};
