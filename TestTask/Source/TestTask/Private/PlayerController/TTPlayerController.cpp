// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerController/TTPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

ATTPlayerController::ATTPlayerController()
{

}

void ATTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(Movement, ETriggerEvent::Triggered, this, &ThisClass::MoveInput);
		EnhancedInputComponent->BindAction(Look, ETriggerEvent::Triggered, this, &ThisClass::LookInput);
	}
}

void ATTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATTPlayerController::MoveInput(const FInputActionValue& InputActionValue)
{
	APawn* PlayerPawn = GetPawn<APawn>();

	if (!IsValid(PlayerPawn))
	{
		return;
	}

	FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	PlayerPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	PlayerPawn->AddMovementInput(RightDirection, MovementVector.X);
	
}

void ATTPlayerController::LookInput(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	APawn* PlayerPawn = GetPawn<APawn>();

	if (!IsValid(PlayerPawn))
	{
		return;
	}

	PlayerPawn->AddControllerYawInput(LookAxisVector.X);
	PlayerPawn->AddControllerPitchInput(LookAxisVector.Y);
}
