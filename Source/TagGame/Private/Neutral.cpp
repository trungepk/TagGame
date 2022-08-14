// Fill out your copyright notice in the Description page of Project Settings.


#include "Neutral.h"
#include "TagGame/TagGameCharacter.h"
#include "FollowComponent.h"

ANeutral::ANeutral()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerSkeletalMeshFinder(TEXT("/Game/TopDown/Characters/SKM_Quinn_Player"));
	if (PlayerSkeletalMeshFinder.Succeeded())
	{
		PlayerSkeletalMesh = PlayerSkeletalMeshFinder.Object;
	}
}

void ANeutral::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMesh = FindComponentByClass<USkeletalMeshComponent>();
	FollowComponent = FindComponentByClass<UFollowComponent>();
}

// Called every frame
void ANeutral::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayAnim();
}

void ANeutral::HitPlayer(AActor* Player)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hit neutral"));
	ChangeMesh(PlayerSkeletalMesh);

	//Follow player
	if (FollowComponent) 
	{
		FollowComponent->Setup();
	}
}

void ANeutral::ChangeMesh(USkeletalMesh* Mesh)
{
	if (!SkeletalMesh) { return; }

	if (PlayerSkeletalMesh)
	{
		SkeletalMesh->SetSkeletalMesh(Mesh);
	}
}

void ANeutral::PlayAnim()
{
	if (!FollowComponent) { return; }
	
	if (FollowComponent->GetIsMoving())
	{
		if (curAnim != Anims::Run)
		{
			SkeletalMesh->PlayAnimation(RunAnim, true);
		}
		curAnim = Anims::Run;
	}
	else
	{
		if (curAnim != Anims::Idle)
		{
			SkeletalMesh->PlayAnimation(IdleAnim, true);
		}
		curAnim = Anims::Idle;
	}
}
