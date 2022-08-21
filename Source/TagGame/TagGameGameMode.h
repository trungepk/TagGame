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

	void AddGangMember(AActor* gangMember);

	TArray<AActor*>* GetGangMember();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USkeletalMesh* PlayerSkeletalMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USkeletalMesh* EnemySkeletalMesh = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "Result")
		FGameModeDelegate OnWin;

	void UpdateEnemyCount();
private:
	UPROPERTY()
		TArray<AActor*> GMembers;
};

