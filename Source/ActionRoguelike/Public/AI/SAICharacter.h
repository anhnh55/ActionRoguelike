// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWorldUserWidget.h"
#include "ActionRoguelike/SAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "SAICharacter.generated.h"

class USActionComponent;
UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName TimeToHitParamName;
	UPROPERTY(EditAnywhere, Category = "Effects")
		FColor HitFlashColor;

	UPROPERTY(EditAnywhere, Category = "Effects")
		float HitFlashSpeed;
	UPROPERTY(VisibleAnywhere, Category="Component")
	UPawnSensingComponent* PawnSensingComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USAttributeComponent* AttributeComp;

	UPROPERTY(EditDefaultsOnly, Category= "AI")
		TSubclassOf<UUserWidget> HealthBarWidgetClass;
	UFUNCTION()
		void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
		USActionComponent* ActionComp;

	USWorldUserWidget* ActiveHealthBar;


	void SetTargetActor(AActor* NewTarget);

	virtual void PostInitializeComponents() override;

};
