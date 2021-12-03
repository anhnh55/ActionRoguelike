// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMeshComp->SetRelativeRotation(FRotator(targetPitch, 0, 0));
}

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComp");
	RootComponent = BaseMeshComp;
	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("LidMeshComp");
	LidMeshComp->SetupAttachment(BaseMeshComp);
	targetPitch = 110;
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

