// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;
}

void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensureAlways(ProjectileClass))
	{
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation("Muzzle_01");

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(InstigatorCharacter);
		//cast line from camera

		//Viewport Size
		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		
		//Viewport Center!            
		const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);
		FVector CrosshairWorldLocation;
		FVector CrosshairWorldDirection;
		GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(ViewportCenter.X, ViewportCenter.Y, CrosshairWorldLocation, CrosshairWorldDirection);

		UE_LOG(LogTemp, Warning, TEXT("CenterX %f, CenterY %f,  Loc %s, Dir %s"), ViewportCenter.X, ViewportCenter.Y, *CrosshairWorldLocation.ToString(), *CrosshairWorldDirection.ToString());
		//FVector TraceStart = CameraComp->GetComponentLocation();

		//FVector TraceEnd = CameraComp->GetComponentLocation() + CameraComp->GetComponentRotation().Vector() * 5000.0f;
		FVector TraceStart = CrosshairWorldLocation;
		FVector TraceEnd = CrosshairWorldLocation + CrosshairWorldDirection * 1000.0f;

		FHitResult Hit;
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

		
		//GetActorEyesViewPoint(CameraLocation, CameraRotation);
		if (GetWorld()->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, ObjectQueryParams, QueryParams))
		{
			TraceEnd = Hit.ImpactPoint;
		}


		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}

	StopAction(InstigatorCharacter);
}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if(Character)
	{
		Character->PlayAnimMontage(AttackAnim);
		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector,
			FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
	}
	
}
