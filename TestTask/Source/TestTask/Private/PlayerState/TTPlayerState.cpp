// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/TTPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Components/TTAttributeSet.h"

ATTPlayerState::ATTPlayerState(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UTTAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ATTPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UTTAttributeSet* ATTPlayerState::GetAttributeSet()
{
	return AttributeSet;
}

void ATTPlayerState::BeginPlay()
{
	Super::BeginPlay();
}
