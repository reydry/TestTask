// Fill out your copyright notice in the Description page of Project Settings.


#include "TTHeroComponent.h"
#include "AbilitySystemComponent.h"
#include "Characters/TTCharacter.h"

UTTHeroComponent::UTTHeroComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

UTTHeroComponent* UTTHeroComponent::GetHeroComponent(const AActor* Actor)
{
	return Actor ? Actor->FindComponentByClass<UTTHeroComponent>() : nullptr;
}

void UTTHeroComponent::AddAdditionalInputConfig(UTTAbilityInputConfig* InConfig)
{
	if (APawn* Pawn = GetOwner<APawn>())
	{
		for (FTTAbilityInput& Input : InConfig->Inputs)
		{
			TArray<FInputBindingHandle> BindingHandles = BindAbilityAction(Input, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased, Pawn->InputComponent);
			TemporaryBindings.Add(Input.AbilityInputID, BindingHandles);
		}
	}
}

void UTTHeroComponent::RemoveInputConfig(UTTAbilityInputConfig* InConfig)
{
	if (APawn* Pawn = GetOwner<APawn>())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent))
		{
			for (FTTAbilityInput& Input : InConfig->Inputs)
			{
				TArray<FInputBindingHandle>* BindingHandles = TemporaryBindings.Find(Input.AbilityInputID);

				if (BindingHandles)
				{
					for (FInputBindingHandle Handle : *BindingHandles)
					{
						EnhancedInputComponent->RemoveBinding(Handle);
					}

					TemporaryBindings.Remove(Input.AbilityInputID);
				}
			}
		}
	}
}

void UTTHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	if (!IsValid(InputConfig))
	{
		return;
	}

	for (FTTAbilityInput& Input : InputConfig->Inputs)
	{
		BindAbilityAction(Input, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased, PlayerInputComponent);
	}
}

void UTTHeroComponent::AbilityInputPressed(int32 InputID)
{
	if (ATTCharacter* Character = GetOwner<ATTCharacter>())
	{
		if (UAbilitySystemComponent* AbilitySystem = Character->GetAbilitySystemComponent())
		{
			AbilitySystem->PressInputID(InputID);
		}
	}
}

void UTTHeroComponent::AbilityInputReleased(int32 InputID)
{
	if (ATTCharacter* Character = GetOwner<ATTCharacter>())
	{
		if (UAbilitySystemComponent* AbilitySystem = Character->GetAbilitySystemComponent())
		{
			AbilitySystem->ReleaseInputID(InputID);
		}
	}
}

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
TArray<FInputBindingHandle> UTTHeroComponent::BindAbilityAction(const FTTAbilityInput InInputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!IsValid(EnhancedInputComponent))
	{
		return TArray<FInputBindingHandle>();
	}

	TArray<FInputBindingHandle> BindingHandles;

	if (ReleasedFunc)
	{
		BindingHandles.Add(EnhancedInputComponent->BindAction(InInputConfig.InputAction, InInputConfig.ReleasedEvent, this, &ThisClass::AbilityInputReleased, static_cast<int32>(InInputConfig.AbilityInputID)));
	}

	if (PressedFunc)
	{
		BindingHandles.Add(EnhancedInputComponent->BindAction(InInputConfig.InputAction, InInputConfig.PressedEvent, this, &ThisClass::AbilityInputPressed, static_cast<int32>(InInputConfig.AbilityInputID)));
	}

	return BindingHandles;
}