// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp,
	//										float, NewHealth, float, Delta);

// Alternative: Share the same signature with generic names
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewValue, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
		float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
		float HealthMax;

	/* Resource used to power certain Actions */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
		float Rage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
		float RageMax;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Reliable)
		void MulticastHealthChanged(AActor* Instigator, float NewHealth, float Delta);

	UFUNCTION(NetMulticast, Unreliable) // Used for cosmetic changes only
		void MulticastRageChanged(AActor* InstigatorActor, float NewRage, float Delta);

public:
	UFUNCTION(BlueprintCallable)
		bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable)
		bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category= "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float delta);

	UPROPERTY(BlueprintAssignable)
		FOnAttributeChanged OnHealthChanged;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		static bool IsActorAlive(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool IsFullHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealthMax() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetRage() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool ApplyRage(AActor* InstigatorActor, float Delta);

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnAttributeChanged OnRageChanged;
};
