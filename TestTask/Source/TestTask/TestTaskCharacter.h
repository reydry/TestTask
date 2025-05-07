// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "TTHeroComponent.h"
#include "TestTaskCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UGameplayAbility;
class UTTHeroComponent;

UCLASS(config=Game)
class ATestTaskCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TPCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ATestTaskCharacter();

	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	class UCameraComponent* GetTPCamera() const { return TPCamera; }
	class UCameraComponent* GetFPCamera() const { return FPCamera; }

	virtual void PossessedBy(AController* InController) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UFUNCTION(BlueprintCallable)
	void GiveAbility(TSubclassOf<UGameplayAbility> InAbility, int32 Level, int32 InputID);
	
	UFUNCTION(BlueprintCallable)
	void RemoveAbility(TSubclassOf<UGameplayAbility> InAbility);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitAbilitySystem(AController* InController);

	void SetupAbilities();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
	TMap<TSubclassOf<UGameplayAbility>, ETTAbilityInputID> Abilities;

	UPROPERTY(BlueprintReadOnly)
	TMap<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle> GivenAbilities;

private:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTTHeroComponent* HeroComponent;
};

