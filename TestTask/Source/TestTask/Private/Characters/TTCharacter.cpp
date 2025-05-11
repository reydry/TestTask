// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TTCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "AbilitySystemComponent.h"
#include "PlayerState/TTPlayerState.h"
#include "Interacts/TTInteractComponent.h"
#include "Components/TTInventoryComponent.h"

ATTCharacter::ATTCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	InteractComponent = CreateDefaultSubobject<UTTInteractComponent>(TEXT("InteractComponent"));

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(GetMesh(), FName(TEXT("LeftHandSocket")));

	InventoryComponent = CreateDefaultSubobject<UTTInventoryComponent>(TEXT("InventoryComponent"));
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATTCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATTCharacter::InitAbilitySystem(AController* InController)
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

void ATTCharacter::SetupAbilities()
{
	for (TPair<TSubclassOf<UGameplayAbility>, ETTAbilityInputID>& Ability : Abilities)
	{
		GiveAbility(Ability.Key, 0, static_cast<int32>(Ability.Value));
	}
}

void ATTCharacter::ApplyStartupAttributes()
{
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->ApplyGameplayEffectToSelf(AttributesEffect.GetDefaultObject(), 1, FGameplayEffectContextHandle());
	}
}

UAbilitySystemComponent* ATTCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATTCharacter::PossessedBy(AController* InController)
{
	Super::PossessedBy(InController);

	InitAbilitySystem(InController);

	SetupAbilities();

	ApplyStartupAttributes();
}

UStaticMeshComponent* ATTCharacter::GetItemMesh() const
{
	return ItemMesh;
}

void ATTCharacter::GiveAbility(TSubclassOf<UGameplayAbility> InAbility, int32 Level, int32 InputID)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InAbility))
	{
		FGameplayAbilitySpec AbilitySpec(InAbility, Level, InputID);
		FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
		GivenAbilities.Add(InAbility, AbilitySpecHandle);
	}
}

void ATTCharacter::RemoveAbility(TSubclassOf<UGameplayAbility> InAbility)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InAbility))
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = *GivenAbilities.Find(InAbility);
		AbilitySystemComponent->ClearAbility(AbilitySpecHandle);
		GivenAbilities.Remove(InAbility);
	}
}

void ATTCharacter::OnDeath()
{
	AController* TTController = GetController();
	
	if (IsValid(TTController))
	{
		TTController->UnPossess();
	}

	Destroy();
}

