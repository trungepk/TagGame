// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Constants.h"
#include "InteractableCharacter.generated.h"

class UFollowComponent;

UCLASS()
class TAGGAME_API AInteractableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInteractableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		USkeletalMeshComponent* SkeletalMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
		USkeletalMesh* EnemySkeletalMesh = nullptr;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HitPlayer(AActor* Player);

	virtual void ChangeMesh(USkeletalMesh* MeshToChange);

	UPROPERTY(EditDefaultsOnly)
		USkeletalMesh* PlayerSkeletalMesh = nullptr;

	UPROPERTY()
		UFollowComponent* FollowComponent = nullptr;

	LineLeader Leader = LineLeader::None;

	UFUNCTION(BlueprintPure, Category = Line)
		virtual LineLeader GetLeaderType() const;
};
