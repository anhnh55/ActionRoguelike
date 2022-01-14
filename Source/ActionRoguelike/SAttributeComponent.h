// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp,
											float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		float HealthMax;
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
		bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category= "Attributes")
	bool ApplyHealthChange(float delta);

	UPROPERTY(BlueprintAssignable)
		FOnHealthChanged OnHealthChanged;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		static USAttributeComponent* GetAttributes(AActor* FromActor);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool IsFullHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealthMax() const;
};
