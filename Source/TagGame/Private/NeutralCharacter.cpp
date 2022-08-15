// Fill out your copyright notice in the Description page of Project Settings.


#include "NeutralCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TagGame/TagGameGameMode.h"
#include "Tasks/AITask_MoveTo.h"
#include "FollowComponent.h"

ANeutralCharacter::ANeutralCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerSkeletalMeshFinder(TEXT("/Game/TopDown/Characters/SKM_Quinn_Player"));
	if (PlayerSkeletalMeshFinder.Succeeded())
	{
		PlayerSkeletalMesh = PlayerSkeletalMeshFinder.Object;
	}
}

void ANeutralCharacter::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMesh = FindComponentByClass<USkeletalMeshComponent>();
	FollowComponent = FindComponentByClass<UFollowComponent>();
}

void ANeutralCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANeutralCharacter::HitPlayer(AActor* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit neutral character"));
	ChangeMesh(PlayerSkeletalMesh);

	////Follow player
	if (FollowComponent)
	{
		FollowComponent->Setup();
	}
}

void ANeutralCharacter::HitEnemy(AEnemyCharacter* Enemy)
{

}

void ANeutralCharacter::ChangeMesh(USkeletalMesh* MeshToChange)
{
	if (!SkeletalMesh) { return; }

	if (PlayerSkeletalMesh)
	{
		SkeletalMesh->SetSkeletalMesh(MeshToChange);
	}
}
