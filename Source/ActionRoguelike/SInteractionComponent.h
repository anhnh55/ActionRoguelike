// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWorldUserWidget.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USInteractionComponent();
	void PrimaryInteract();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void FindBestInteractable();

	UPROPERTY()
		AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<USWorldUserWidget> DefaultWidgetClass;

	UPROPERTY()
		USWorldUserWidget* DefaultWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "trace")
		float TraceDistance;
	UPROPERTY(EditDefaultsOnly, Category = "trace")
		TEnumAsByte<ECollisionChannel> CollisionChannel;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



};
