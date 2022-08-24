// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableObject.h"
#include "SpeedUpObject.generated.h"

/**
 * 
 */
UCLASS()
class TAGGAME_API ASpeedUpObject : public APickableObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float AddedSpeed = 50.f;

	UPROPERTY(EditDefaultsOnly)
	float Duration = 5.f;
	
private:
	void PickedUp(AActor* Picker) override;

	float LastPickedTime = 0.f;
};
