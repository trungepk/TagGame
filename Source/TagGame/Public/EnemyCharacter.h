// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableCharacter.h"
#include "Constants.h"
#include "EnemyCharacter.generated.h"

class ATagGameGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemyCharacterDelegate);
/**
 * 
 */
UCLASS()
class TAGGAME_API AEnemyCharacter : public AInteractableCharacter
{
	GENERATED_BODY()

public:
	void AddGangMember(AActor* gangMember);

	//Kick the last member out
	void PopGangMember();

	TArray<AActor*>* GetGangMember();

	UFUNCTION(BlueprintPure, Category = UI)
		int32 GetMembersCount() const;

	UPROPERTY(BlueprintAssignable)
		FEnemyCharacterDelegate OnCaptured;

	//LineLeader GetLeaderType() const override;

protected:
	virtual void BeginPlay() override;

private:
	void HitPlayer(AActor* Player) override;

	void KilledByPlayer(ATagGameGameMode* MyMode, AActor* Player);

	UFUNCTION()
		void OverlapBeginMesh(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
		TArray<AActor*> GMembers;

	void ChangeMesh(USkeletalMesh* MeshToChange) override;
};
