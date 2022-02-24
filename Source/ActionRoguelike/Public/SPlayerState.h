// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

class ASPlayerState; // Forward declared to satisfy the delegate macros below

// Event Handler for Credits
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int32, NewCredits, int32, Delta);

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing = "OnRep_Credits", Category = "Credits")
		int32 Credits;
	// OnRep_ can use a parameter containing the 'old value' of the variable it is bound to. Very useful in this case to figure out the 'delta'.
	UFUNCTION()
		void OnRep_Credits(int32 OldCredits);
public:

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnCreditsChanged OnCreditsChanged;

	UFUNCTION(BlueprintCallable, Category = "Credits")
		int32 GetCredits() const;

	UFUNCTION(BlueprintCallable, Category = "Credits")
		void AddCredits(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Credits")
		bool RemoveCredits(int32 Delta);

};
