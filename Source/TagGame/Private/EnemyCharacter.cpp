// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "NeutralCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TagGame/TagGameGameMode.h"
#include "TagGame/TagGameCharacter.h"
#include "FollowComponent.h"
#include "EnemyAIController.h"


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OverlapBeginMesh);

	AddGangMember(this);
}

void AEnemyCharacter::HitPlayer(AActor* Player)
{
	//Compare total members to player's, if less or equal then get turn to player's member along with all its member, else lose game
	if (Leader != LineLeader::Player)
	{
		ATagGameGameMode* MyMode = Cast<ATagGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (GetMembersCount() <= MyMode->GetGangMember()->Num())
		{
			//Stop AI behaviour and destroy UI widget
			OnCaptured.Broadcast();

			ChangeMesh(PlayerSkeletalMesh);

			//Follow player
			if (FollowComponent)
			{
				auto callback = [&]() {MyMode->AddGangMember(this); };
				FollowComponent->Setup(Player, callback);
			}
		}
		else
		{
			//Lose game
			auto PlayerCharacter = Cast<ATagGameCharacter>(Player);
			
			if (ensure(PlayerCharacter))
			{
				PlayerCharacter->KillPlayer();
			}
		}

		Leader = LineLeader::Player;
	}
}

void AEnemyCharacter::OverlapBeginMesh(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANeutralCharacter* NeutralCharacter = Cast<ANeutralCharacter>(OtherActor);
	if (NeutralCharacter)
	{
		NeutralCharacter->HitEnemy(this);
	}
}

void AEnemyCharacter::AddGangMember(AActor* gangMember)
{
	GMembers.Add(gangMember);
}

TArray<AActor*>* AEnemyCharacter::GetGangMember()
{
	return &GMembers;
}

void AEnemyCharacter::PopGangMember()
{

}

int32 AEnemyCharacter::GetMembersCount() const
{
	return GMembers.Num();
}

void AEnemyCharacter::ChangeMesh(USkeletalMesh* MeshToChange)
{
	Super::ChangeMesh(MeshToChange);
}

LineLeader AEnemyCharacter::GetLeaderType() const
{
	return Leader;
}