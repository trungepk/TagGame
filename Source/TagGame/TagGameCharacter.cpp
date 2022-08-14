// Copyright Epic Games, Inc. All Rights Reserved.

#include "TagGameCharacter.h"
#include "TagGameGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "InteractableAgent.h"
#include "Kismet/GameplayStatics.h"

ATagGameCharacter::ATagGameCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATagGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ATagGameCharacter::HitMesh);
	ATagGameGameMode* MyMode = Cast<ATagGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	MyMode->AddGangMember(this);
	//SetGangMember(this);
}

void ATagGameCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	SetIsMoving();
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GMembers.Last()->GetActorLocation().ToString());
}

void ATagGameCharacter::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AInteractableAgent* InteractableAgent = Cast<AInteractableAgent>(OtherActor);
	if (InteractableAgent)
	{
		InteractableAgent->HitPlayer(HitComponent->GetOwner());
	}
}

void ATagGameCharacter::SetIsMoving()
{
	IsMoving = GetMovementComponent()->Velocity.Length() > 0;
}

bool ATagGameCharacter::GetIsMoving()
{
	return IsMoving;
}

void ATagGameCharacter::SetGangMember(AActor* gangMember)
{
	GMembers.Add(gangMember);
}

TArray<AActor*> ATagGameCharacter::GetGangMember()
{
	return GMembers;
}
