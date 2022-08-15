// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TAGGAME_API AEnemyCharacter : public AInteractableCharacter
{
	GENERATED_BODY()

public:
	void AddGangMember(AActor* gangMember);

	TArray<AActor*> GetGangMember();

private:
	void HitPlayer(AActor* Player) override;

	UFUNCTION()
		void OverlapBeginMesh(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
		TArray<AActor*> GMembers;
};
