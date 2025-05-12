// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TTGameplayAbility.generated.h"

class ATTCharacter;
class UCharacterMovementComponent;

UCLASS()
class TESTTASK_API UTTGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo);
	
	UFUNCTION(BlueprintPure)
	ATTCharacter* GetTTCharacter() const;
	
	UFUNCTION(BlueprintPure)
	UCharacterMovementComponent* GetCharacterMovementComponent();
};
