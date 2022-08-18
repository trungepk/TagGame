// Fill out your copyright notice in the Description page of Project Settings.


#include "NeutralCharacter.h"
#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TagGame/TagGameGameMode.h"
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

}

void ANeutralCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANeutralCharacter::HitPlayer(AActor* Player)
{
	ChangeMesh(PlayerSkeletalMesh);

	bool bSwitchTeam = false;

	if (Leader == LineLeader::None)
	{
		bSwitchTeam = true;
	}
	else if (Leader == LineLeader::Enemy)
	{
		if (HitEnemyCharacter)
		{
			HitEnemyCharacter->GetGangMember()->Remove(this);
			bSwitchTeam = true;
		}
	}

	if (bSwitchTeam)
	{
		if (FollowComponent)
		{
			ATagGameGameMode* MyMode = Cast<ATagGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			AActor* lastMember = MyMode->GetGangMember()->Last();
			auto callback = [&]() {MyMode->AddGangMember(this); };
			FollowComponent->Setup(lastMember, callback);
		}
	}

	Leader = LineLeader::Player;
}

void ANeutralCharacter::HitEnemy(AEnemyCharacter* Enemy)
{
	if (!Enemy) { return; }

	//Abort if hit enemy is a member of player
	if (Enemy->GetLeaderType() == LineLeader::Player)
	{
		return;
	}

	HitEnemyCharacter = Enemy;

	ChangeMesh(EnemySkeletalMesh);

	bool bSwitchTeam = false;

	if (Leader == LineLeader::None)
	{
		bSwitchTeam = true;
	}
	else if (Leader == LineLeader::Player)
	{
		ATagGameGameMode* MyMode = Cast<ATagGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		MyMode->GetGangMember()->Remove(this);
		bSwitchTeam = true;
	}

	Leader = LineLeader::Enemy;

	if (bSwitchTeam)
	{
		if (FollowComponent)
		{
			AActor* lastMember = Enemy->GetGangMember()->Last();
			auto callback = [&]() {Enemy->AddGangMember(this); };
			FollowComponent->Setup(lastMember, callback);
		}
	}
}

void ANeutralCharacter::ChangeMesh(USkeletalMesh* MeshToChange)
{
	Super::ChangeMesh(MeshToChange);
}
