// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TagGame/TagGameGameMode.h"

// Sets default values for this component's properties
UFollowComponent::UFollowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFollowComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UFollowComponent::Setup(AActor* targetToFollow, const std::function<void()>& addToLine)
{
	if (targetToFollow)
	{
		SetFollowTarget(targetToFollow);
		addToLine();
		StartFollow();
	}
}

void UFollowComponent::SetFollowTarget(AActor* TargetToSet)
{
	FollowedTarget = TargetToSet;
}

void UFollowComponent::StartFollow()
{
	if (FollowedTarget)
	{
		float DistanceToTarget = FollowedTarget->GetDistanceTo(GetOwner());

		//Move to target if far enough 
		OnFollow.Broadcast(DistanceToTarget >= FollowDistance);
	}
}

