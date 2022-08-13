// Fill out your copyright notice in the Description page of Project Settings.


#include "Neutral.h"
#include "TagGame/TagGameCharacter.h"

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
}

// Called every frame
void ANeutral::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Follow();
}

void ANeutral::HitPlayer(AActor* Player)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hit neutral"));
	ChangeMesh(PlayerSkeletalMesh);

	//Follow player
	SetupFollow(Player);
}

void ANeutral::ChangeMesh(USkeletalMesh* Mesh)
{
	if (!SkeletalMesh) { return; }

	if (PlayerSkeletalMesh)
	{
		SkeletalMesh->SetSkeletalMesh(Mesh);
	}
}

void ANeutral::SetupFollow(AActor* TargetToFollow)
{
	if (!isFollowing)
	{
		isFollowing = true;
		player = Cast<ATagGameCharacter>(TargetToFollow);
		if (player)
		{
			AActor* lastMember = player->GetGangMember().Last();
			//UE_LOG(LogTemp, Warning, TEXT("%d"), player->GMembers.Num());
			//SetFollowTarget(TargetToFollow);
			SetFollowTarget(lastMember);

			player->SetGangMember(this);
			//UE_LOG(LogTemp, Warning, TEXT("%d"), player->GMembers.Num());
		}

	}
}

void ANeutral::SetFollowTarget(AActor* TargetToSet)
{
	FollowedTarget = TargetToSet;

}

void ANeutral::Follow()
{
	if (!FollowedTarget) { return; }

	//UE_LOG(LogTemp, Warning, TEXT("Follow %s"), *FollowedTarget->GetName());

	FVector TargetForwardVec = FollowedTarget->GetActorForwardVector();
	FVector TargetLocation = FollowedTarget->GetActorLocation();
	FVector MoveToOffet = TargetForwardVec * FollowDistance + TargetLocation;

	//AddMovementInput(MoveToOffet.GetSafeNormal(), 1.f, false);
	float Alpha = 0.5f;
	MoveToOffet = FMath::Lerp(GetActorLocation(), MoveToOffet, Alpha);
	SetActorLocation(MoveToOffet);
	SetActorRotation(FollowedTarget->GetActorRotation());

	PlayAnim();
}

void ANeutral::PlayAnim()
{
	//ACrowdRoadCharacter* player = Cast<ATagGameCharacter>(FollowedTarget);
	//player = Cast<ATagGameCharacter>(FollowedTarget);
	if (player)
	{
		if (player->GetIsMoving())
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
}
