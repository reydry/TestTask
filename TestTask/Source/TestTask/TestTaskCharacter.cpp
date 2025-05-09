// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTaskCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "PlayerState/TTPlayerState.h"
#include "Interacts/TTInteractComponent.h"
#include "Components/TTInventoryComponent.h"

ATestTaskCharacter::ATestTaskCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	TPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPCamera"));
	TPCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	TPCamera->bUsePawnControlRotation = false; 

	HeroComponent = CreateDefaultSubobject<UTTHeroComponent>(TEXT("HeroComponent"));
	InteractComponent = CreateDefaultSubobject<UTTInteractComponent>(TEXT("InteractComponent"));

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(GetMesh(), FName(TEXT("LeftHandSocket")));

	InventoryComponent = CreateDefaultSubobject<UTTInventoryComponent>(TEXT("InventoryComponent"));
}

void ATestTaskCharacter::PossessedBy(AController* InController)
{
	Super::PossessedBy(InController);

	InitAbilitySystem(InController);

	SetupAbilities();
}

UAbilitySystemComponent* ATestTaskCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATestTaskCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (IsValid(HeroComponent))
	{
		HeroComponent->InitializePlayerInput(PlayerInputComponent);
	}
}

void ATestTaskCharacter::InitAbilitySystem(AController* InController)
{
	ATTPlayerState* State = InController->GetPlayerState<ATTPlayerState>();

	if (!IsValid(State))
	{
		return;
	}

	AbilitySystemComponent = State->GetAbilitySystemComponent();

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ATestTaskCharacter::SetupAbilities()
{
	for (TPair<TSubclassOf<UGameplayAbility>, ETTAbilityInputID>& Ability : Abilities)
	{
		
		GiveAbility(Ability.Key, 0, static_cast<int32>(Ability.Value));
	}
}

void ATestTaskCharacter::GiveAbility(TSubclassOf<UGameplayAbility> InAbility, int32 Level, int32 InputID)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InAbility))
	{
		FGameplayAbilitySpec AbilitySpec(InAbility, Level, InputID);
		FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
		GivenAbilities.Add(InAbility, AbilitySpecHandle);
	}
}

void ATestTaskCharacter::RemoveAbility(TSubclassOf<UGameplayAbility> InAbility)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InAbility))
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = *GivenAbilities.Find(InAbility);
		AbilitySystemComponent->ClearAbility(AbilitySpecHandle);
		GivenAbilities.Remove(InAbility);
	}
}

UStaticMeshComponent* ATestTaskCharacter::GetItemMesh() const
{
	return ItemMesh;
}
