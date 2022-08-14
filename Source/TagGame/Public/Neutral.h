// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableAgent.h"
#include "Neutral.generated.h"

enum Anims { Idle, Run };

class ATagGameCharacter;
class UFollowComponent;

/**
 * 
 */
UCLASS()
class TAGGAME_API ANeutral : public AInteractableAgent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ANeutral();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = Anim)
		UAnimSequence* RunAnim;

	UPROPERTY(EditDefaultsOnly, Category = Anim)
		UAnimSequence* IdleAnim;

private:
	void HitPlayer(AActor* Player) override;

	void ChangeMesh(USkeletalMesh* SkeletalMesh);

	void PlayAnim();

	USkeletalMesh* PlayerSkeletalMesh = nullptr;

	Anims curAnim = Anims::Idle;

	UFollowComponent* FollowComponent = nullptr;
};
