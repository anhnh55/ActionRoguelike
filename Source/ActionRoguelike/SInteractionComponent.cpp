// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	FHitResult Hit;

	AActor* MyOwner = GetOwner();

	

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector()*200.0f);
	GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, QueryParams);

	AActor* HitActor = Hit.GetActor();
	if(HitActor)
	{
		if(HitActor->Implements<USGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 2.0f,0, 2.0f);
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

