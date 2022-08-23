// Copyright Epic Games, Inc. All Rights Reserved.

#include "TagGameGameMode.h"
#include "TagGamePlayerController.h"
#include "TagGameCharacter.h"
#include "EnemyCharacter.h"
#include "Constants.h"
#include "UObject/ConstructorHelpers.h"

ATagGameGameMode::ATagGameGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	
	// use our custom PlayerController class
	PlayerControllerClass = ATagGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void ATagGameGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool CanSpawn = FPlatformTime::Seconds() - LastSpawnTime > SpawnRate;

	if (CanSpawn)
	{
		LastSpawnTime = FPlatformTime::Seconds();

		OnSpawnRequest.Broadcast();
	}
}

void ATagGameGameMode::AddGangMember(AActor* gangMember)
{
	GMembers.Add(gangMember);
}

TArray<AActor*>* ATagGameGameMode::GetGangMember()
{
	return &GMembers;
}

void ATagGameGameMode::UpdateEnemyCount()
{
	//Count every enemies in level
	TArray<AEnemyCharacter*> Out_Enemies;
	UConstants::FindAllActors(GetWorld(), Out_Enemies);

	//Determine if enemy which doesn't have line leader, if 0 then win game
	for (auto* enemy : Out_Enemies)
	{
		if (enemy->GetLeaderType() == LineLeader::None)
		{
			return;
		}
	}

	//Reach here means there're no enemy which has no leader
	OnWin.Broadcast();
}