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

	Follow();
}

void UFollowComponent::Setup()
{
	if (!isFollowing)
	{
		isFollowing = true;
		ATagGameGameMode* MyMode = Cast<ATagGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		AActor* lastMember = MyMode->GetGangMember().Last();
		if (lastMember)
		{
			SetFollowTarget(lastMember);
			MyMode->AddGangMember(GetOwner());
		}
	}
}

void UFollowComponent::SetFollowTarget(AActor* TargetToSet)
{
	FollowedTarget = TargetToSet;

}

void UFollowComponent::Follow()
{
	if (!FollowedTarget) { return; }

	UE_LOG(LogTemp, Warning, TEXT("Follow in component"));

	FVector TargetForwardVec = FollowedTarget->GetActorForwardVector();
	FVector TargetLocation = FollowedTarget->GetActorLocation();
	FVector MoveToOffet = TargetForwardVec * (-FollowDistance) + TargetLocation;

	float distanceBetween = (TargetLocation - GetOwner()->GetActorLocation()).Length();

	if (distanceBetween <= FollowDistance + 5)
	{
		SetIsMoving(false);
		return;
	}

	SetIsMoving(true);
	float Alpha = 0.5f;
	MoveToOffet = FMath::Lerp(GetOwner()->GetActorLocation(), MoveToOffet, Alpha);
	GetOwner()->SetActorLocation(MoveToOffet);
	GetOwner()->SetActorRotation(FollowedTarget->GetActorRotation());
}

void UFollowComponent::SetIsMoving(bool bIsMoving)
{
	IsMoving = bIsMoving;
}

bool UFollowComponent::GetIsMoving()
{
	return IsMoving;
}

