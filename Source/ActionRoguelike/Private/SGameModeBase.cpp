// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "EngineUtils.h"
#include "ActionRoguelike/SAttributeComponent.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                      EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query failed"));
		return;
	}

	int32 NrOfAliveBots = 0;
	for(TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;

		USAttributeComponent* AttributeComp= Cast <USAttributeComponent>(Bot->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(AttributeComp && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	float MaxBotCount = 10.0f;

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if(NrOfAliveBots >= MaxBotCount)
	{
		return;
	}



	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if(Locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if(QueryInstance)
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryCompleted);
	}
	
}
