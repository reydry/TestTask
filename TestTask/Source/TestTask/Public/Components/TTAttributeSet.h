// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TTAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChangedDelegateSignature, AActor*, Instigator, float, NewValue, float, MaxValue);

UCLASS()
class TESTTASK_API UTTAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UTTAttributeSet();

	ATTRIBUTE_ACCESSORS(UTTAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UTTAttributeSet, MaxHealth);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnHealthChangedDelegateSignature OnHealthChangedDelegate;

	virtual UWorld* GetWorld() const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	
};
