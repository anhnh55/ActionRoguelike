// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "SWorldUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	

public:
	UPROPERTY(meta = (BindWidget))
		USizeBox* ParentSizeBox;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
		AActor* AttachedActor;

	UPROPERTY(EditAnywhere, Category = "UI")
		FVector WorldOffset;
};
