// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SProjectileBase.h"
#include "SMagicProjectile.generated.h"

class USActionEffect;
UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DamageAmount;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
		FGameplayTag ParryTag;
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		TSubclassOf<USActionEffect> BurningActionClass;

	UFUNCTION()
		void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
