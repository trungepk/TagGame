// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"



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