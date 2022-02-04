// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SActionComponent.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()
	
public:

	USAction();

	/*Action nickname to start/stop without a reference to the object*/
	UPROPERTY(EditDefaultsOnly, Category = "Action")
		FName ActionName;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
		void StopAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		bool CanStart(AActor* Instigator);

	UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, Category = "Action")
		bool IsRunning() const;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
		bool bAutoStart;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer BlockedTags;

	UFUNCTION(BlueprintCallable, Category = "Action")
		USActionComponent* GetOwningComponent() const;

	bool bIsRunning;
};
