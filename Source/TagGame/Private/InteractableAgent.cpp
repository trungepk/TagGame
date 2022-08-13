// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableAgent.h"

// Sets default values
AInteractableAgent::AInteractableAgent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableAgent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInteractableAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AInteractableAgent::HitPlayer(AActor* Player)
{
}

