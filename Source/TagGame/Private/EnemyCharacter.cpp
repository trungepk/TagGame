// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "NeutralCharacter.h"
#include "Components/CapsuleComponent.h"


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OverlapBeginMesh);
	/*SkeletalMesh = FindComponentByClass<USkeletalMeshComponent>();
	FollowComponent = FindComponentByClass<UFollowComponent>();*/
	AddGangMember(this);
}

void AEnemyCharacter::HitPlayer(AActor* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Hit enemy character"));
	//ChangeMesh(PlayerSkeletalMesh);

	//////Follow player
	//if (FollowComponent)
	//{
	//	FollowComponent->Setup();
	//}
	Leader = LineLeader::Player;
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

void AEnemyCharacter::PopGangMember(FString memberName)
{
	int32 indexToRemove = -1;

	for (int32 i = 0; i != GMembers.Num(); ++i)
	{
		if (GMembers[i]->GetFName().ToString() == memberName)
		{
			indexToRemove = i;
		}
	}
	GMembers.RemoveAt(indexToRemove);
}

int32 AEnemyCharacter::GetMembersCount() const
{
	return GMembers.Num();
}