// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EngineUtils.h"
#include "Constants.generated.h"

/**
 *
 */
UCLASS()
class TAGGAME_API UConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template<typename T>
	static void FindAllActors(UWorld* World, TArray<T*> &Out)
	{
		for (TActorIterator<T> It(World); It; ++It)
		{
			Out.Add(*It);
		}
	}

};

#pragma region ENUMS

UENUM(BlueprintType)
enum LineLeader
{
	None,
	Player,
	Enemy
};

#pragma endregion ENUMS