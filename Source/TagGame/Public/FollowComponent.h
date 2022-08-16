// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FollowComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFollowRequest, bool, IsFarAway);

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

	void Setup(AActor* targetToFollow, const std::function<void()>& addToLine);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Follow)
		float FollowDistance = 100.f;

	UPROPERTY(BlueprintAssignable)
		FOnFollowRequest OnFollow;

	UFUNCTION(BlueprintCallable)
	void StartFollow();

	UPROPERTY(BlueprintReadWrite, Category = Follow)
		AActor* FollowedTarget = nullptr;

private:
	bool isFollowing = false;

	void SetFollowTarget(AActor* TargetToSet);
};
