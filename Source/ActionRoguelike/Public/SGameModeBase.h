// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASGameModeBase();
	virtual void StartPlay() override;

	UFUNCTION(Exec)
		void KillAllAI();
	virtual void OnActorKill(AActor* VictimActor, AActor* Killer);
protected:
	UFUNCTION()
		void RespawnPlayerElapsed(AController* Controller);
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		TSubclassOf<AActor> MinionClass;

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* EnvQueryInstanceBlueprintWrapper, EEnvQueryStatus::Type Arg);

	UFUNCTION()
		void SpawnBotTimerElapsed();
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FTimerHandle TimerHandle_SpawnBots;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category="AI")
		UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UCurveFloat* DifficultyCurve;
};
