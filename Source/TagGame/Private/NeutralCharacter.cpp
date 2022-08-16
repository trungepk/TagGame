// Fill out your copyright notice in the Description page of Project Settings.


#include "NeutralCharacter.h"
#include "EnemyCharacter.h"
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
	ChangeMesh(PlayerSkeletalMesh);

	if (Leader == LineLeader::None)
	{
		UE_LOG(LogTemp, Warning, TEXT("First change"));
	}
	else if (Leader == LineLeader::Enemy)
	{
		if (HitEnemyCharacter)
		{
			HitEnemyCharacter->GetGangMember()->Remove(this);
		}
	}

	if (FollowComponent)
	{
		ATagGameGameMode* MyMode = Cast<ATagGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		AActor* lastMember = MyMode->GetGangMember()->Last();
		auto callback = [&]() {MyMode->AddGangMember(this); };
		FollowComponent->Setup(lastMember, callback);
	}

	Leader = LineLeader::Player;
}

void ANeutralCharacter::HitEnemy(AEnemyCharacter* Enemy)
{
	if (!Enemy) { return; }

	HitEnemyCharacter = Enemy;

	ChangeMesh(EnemySkeletalMesh);

	if (Leader == LineLeader::None)
	{
	}
	else if (Leader == LineLeader::Player)
	{
		ATagGameGameMode* MyMode = Cast<ATagGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		MyMode->GetGangMember()->Remove(this);
	}

	if (FollowComponent)
	{
		AActor* lastMember = Enemy->GetGangMember()->Last();
		auto callback = [&]() {Enemy->AddGangMember(this); };
		FollowComponent->Setup(lastMember, callback);
	}

	Leader = LineLeader::Enemy;
}

void ANeutralCharacter::ChangeMesh(USkeletalMesh* MeshToChange)
{
	if (!SkeletalMesh) { return; }

	if (MeshToChange)
	{
		SkeletalMesh->SetSkeletalMesh(MeshToChange);
	}
}
