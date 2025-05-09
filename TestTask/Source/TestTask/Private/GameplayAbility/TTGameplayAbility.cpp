// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility/TTGameplayAbility.h"
#include "TestTask/TestTaskCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTTGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
}

ATestTaskCharacter* UTTGameplayAbility::GetTTCharacter() const
{
	return 	(CurrentActorInfo ? Cast<ATestTaskCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}

UCharacterMovementComponent* UTTGameplayAbility::GetCharacterMovementComponent()
{
	return (CurrentActorInfo ? Cast<UCharacterMovementComponent>(CurrentActorInfo->MovementComponent.Get()) : nullptr);
}
