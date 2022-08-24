// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedUpObject.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASpeedUpObject::PickedUp(AActor* Picker)
{
	UE_LOG(LogTemp, Warning, TEXT("PickedUp"));
	ACharacter* Character = Cast<ACharacter>(Picker);
	if (Character)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed += AddedSpeed;

		/*bool TimeUp = FPlatformTime::Seconds() - LastPickedTime > Duration;

		if (TimeUp)
		{
			LastPickedTime = FPlatformTime::Seconds();


		}*/
	}

	Super::PickedUp(Picker);
}