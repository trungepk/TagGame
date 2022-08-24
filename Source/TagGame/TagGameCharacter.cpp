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
#include "InteractableCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PickableObject.h"

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
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATagGameCharacter::OverlapBeginMesh);
	ATagGameGameMode* MyMode = Cast<ATagGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	MyMode->AddGangMember(this);
	//SetGangMember(this);
}

void ATagGameCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

void ATagGameCharacter::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	APickableObject* PickableObject = Cast<APickableObject>(OtherActor);

	if (PickableObject)
	{
		PickableObject->PickedUp(HitComponent->GetOwner());
	}
}

void ATagGameCharacter::OverlapBeginMesh(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	AInteractableCharacter* InteractableCharacter = Cast<AInteractableCharacter>(OtherActor);

	if (InteractableCharacter)
	{
		InteractableCharacter->HitPlayer(OverlappedComponent->GetOwner());
	}
}

int32 ATagGameCharacter::GetMembersCount() const
{
	ATagGameGameMode* MyMode = Cast<ATagGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	return MyMode->GetGangMember()->Num();
}

void ATagGameCharacter::KillPlayer()
{
	OnDead.Broadcast();
}
