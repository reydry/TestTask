// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/TTPlayerState.h"
#include "AbilitySystemComponent.h"

ATTPlayerState::ATTPlayerState(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
}

UAbilitySystemComponent* ATTPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATTPlayerState::BeginPlay()
{
	Super::BeginPlay();
}
