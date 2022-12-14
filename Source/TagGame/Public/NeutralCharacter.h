// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableCharacter.h"
#include "NeutralCharacter.generated.h"

class UFollowComponent;
class AEnemyCharacter;

/**
 * 
 */
UCLASS()
class TAGGAME_API ANeutralCharacter : public AInteractableCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANeutralCharacter();

	void HitEnemy(AEnemyCharacter* Enemy);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
private:
	void HitPlayer(AActor* Player) override;

	USkeletalMesh* PlayerSkeletalMesh = nullptr;

	UFollowComponent* FollowComponent = nullptr;

	void ChangeMesh(USkeletalMesh* MeshToChange);
};
