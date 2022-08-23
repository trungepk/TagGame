// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TagGameGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameModeDelegate);

UCLASS(minimalapi)
class ATagGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATagGameGameMode();

	virtual void Tick(float DeltaTime) override;

	void AddGangMember(AActor* gangMember);

	TArray<AActor*>* GetGangMember();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USkeletalMesh* PlayerSkeletalMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USkeletalMesh* EnemySkeletalMesh = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "Result")
		FGameModeDelegate OnWin;

	void UpdateEnemyCount();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float SpawnRate = 3.0f;

	UPROPERTY(BlueprintAssignable, Category = "Spawning")
		FGameModeDelegate OnSpawnRequest;
private:
	UPROPERTY()
		TArray<AActor*> GMembers;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<ACharacter> NeutralCharacterBlueprint;

	double LastSpawnTime = 0;
};

