// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTaskCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

ATestTaskCharacter::ATestTaskCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	TPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPCamera"));
	TPCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	TPCamera->bUsePawnControlRotation = false; 

	HeroComponent = CreateDefaultSubobject<UTTHeroComponent>(TEXT("HeroComponent"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

USpringArmComponent* ATestTaskCharacter::GetCameraBoom() const
{
	return CameraBoom;
}

UCameraComponent* ATestTaskCharacter::GetTPCamera() const
{
	return TPCamera;
}

void ATestTaskCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (IsValid(HeroComponent))
	{
		HeroComponent->InitializePlayerInput(PlayerInputComponent);
	}
}
