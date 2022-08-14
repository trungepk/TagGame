// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FollowComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TAGGAME_API UFollowComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFollowComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Setup();

	UPROPERTY(EditDefaultsOnly, Category = Follow)
		float FollowDistance = 100.f;

	void SetIsMoving(bool bIsMoving);

	bool GetIsMoving();

private:
	bool isFollowing = false;

	void SetFollowTarget(AActor* TargetToSet);

	void Follow();

	UPROPERTY()
		AActor* FollowedTarget = nullptr;

	bool IsMoving = false;
};
