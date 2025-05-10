// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TTAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"

UTTAttributeSet::UTTAttributeSet()
{
}

void UTTAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		FGameplayEffectContextHandle EffectContextHandle = Data.EffectSpec.GetEffectContext();
		AActor* Instigator = EffectContextHandle.GetInstigator();

		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		OnHealthChangedDelegate.Broadcast(Instigator, GetHealth(), GetMaxHealth());
	}
}

UWorld* UTTAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();

	if (!IsValid(Outer))
	{
		return nullptr;
	}

	return Outer->GetWorld();
}
