// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InteractableAgent.generated.h"

UCLASS()
class TAGGAME_API AInteractableAgent : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInteractableAgent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USkeletalMeshComponent* SkeletalMesh = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HitPlayer(AActor* Player);
};
