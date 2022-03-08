// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionRoguelike/SGameplayInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASPowerupActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;
	FTimerHandle TimerHandle_RespawnTimer;

	void HideAndCooldownPowerup();
	UFUNCTION()
		void OnRep_IsActive();

	UFUNCTION()
		void ShowPowerup();

	UPROPERTY(ReplicatedUsing = "OnRep_IsActive")
	bool bIsActive;

	UPROPERTY(EditAnywhere, Category = "Powerup")
		float RespawnTime;

	void SetPowerupState(bool bNewIsActive);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Interact_Implementation(APawn* InstigatorPawn);
	virtual FText GetInteractText_Implementation(APawn* InstigatorPawn) override;
};
