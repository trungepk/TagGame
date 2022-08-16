// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Constants.generated.h"

/**
 *
 */
UCLASS()
class TAGGAME_API UConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

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