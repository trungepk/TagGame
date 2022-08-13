// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableAgent.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class TAGGAME_API AEnemy : public AInteractableAgent
{
	GENERATED_BODY()

private:
	void HitPlayer(AActor* Player) override;
};
