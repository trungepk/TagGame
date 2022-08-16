// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TagGameGameMode.generated.h"

UCLASS(minimalapi)
class ATagGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATagGameGameMode();

	void AddGangMember(AActor* gangMember);

	TArray<AActor*>* GetGangMember();

private:
	UPROPERTY()
		TArray<AActor*> GMembers;
};

