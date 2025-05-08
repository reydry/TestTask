// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputAction.h" 
#include "EnhancedInputComponent.h"
#include "TTHeroComponent.generated.h"

UENUM()
enum class ETTAbilityInputID
{
	None,
	Fire,
	Interact,
	Sprint,
	Jump,
	Reload,
	Slide,
};

USTRUCT()
struct FTTAbilityInput
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	ETTAbilityInputID AbilityInputID = ETTAbilityInputID::None;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	ETriggerEvent PressedEvent = ETriggerEvent::None;

	UPROPERTY(EditDefaultsOnly)
	ETriggerEvent ReleasedEvent = ETriggerEvent::None;
};

UCLASS(BlueprintType)
class UTTAbilityInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FTTAbilityInput> Inputs;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASK_API UTTHeroComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTTHeroComponent();

	UFUNCTION(BlueprintPure)
	static UTTHeroComponent* GetHeroComponent(const AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void AddAdditionalInputConfig(UTTAbilityInputConfig* InConfig);

	UFUNCTION(BlueprintCallable)
	void RemoveInputConfig(UTTAbilityInputConfig* InConfig);

	void InitializePlayerInput(UInputComponent* PlayerInputComponent);

	void AbilityInputPressed(int32 InputID);
	void AbilityInputReleased(int32 InputID);

	UPROPERTY(EditDefaultsOnly)
	UTTAbilityInputConfig* InputConfig;

protected:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	TArray<FInputBindingHandle> BindAbilityAction(const FTTAbilityInput InInputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, UInputComponent* PlayerInputComponent);


	TMap<ETTAbilityInputID, TArray<FInputBindingHandle>> TemporaryBindings;
};


