// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedUpObject.h"
#include "TagGame/TagGameCharacter.h"

void ASpeedUpObject::PickedUp(AActor* Picker)
{
	ATagGameCharacter* Character = Cast<ATagGameCharacter>(Picker);
	if (Character)
	{
		Character->AddSpeed(AddedSpeed, Duration);
	}

	Super::PickedUp(Picker);
}