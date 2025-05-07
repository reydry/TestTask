// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility/TTGameplayAbility.h"

void UTTGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
}
