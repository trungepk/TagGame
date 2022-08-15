// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "NeutralCharacter.h"



void AEnemyCharacter::HitPlayer(AActor* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit enemy character"));
	//ChangeMesh(PlayerSkeletalMesh);

	//////Follow player
	//if (FollowComponent)
	//{
	//	FollowComponent->Setup();
	//}
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

TArray<AActor*> AEnemyCharacter::GetGangMember()
{
	return GMembers;
}