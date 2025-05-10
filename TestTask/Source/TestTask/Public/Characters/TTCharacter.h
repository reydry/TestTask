// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TTHeroComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "TTCharacter.generated.h"

class UGameplayAbility;
class UTTInteractComponent;
class UTTInventoryComponent;
class UGameplayEffect;

UCLASS()
class TESTTASK_API ATTCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATTCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PossessedBy(AController* InController) override;

	UStaticMeshComponent* GetItemMesh() const;

	UFUNCTION(BlueprintCallable)
	void GiveAbility(TSubclassOf<UGameplayAbility> InAbility, int32 Level, int32 InputID);

	UFUNCTION(BlueprintCallable)
	void RemoveAbility(TSubclassOf<UGameplayAbility> InAbility);

protected:
	virtual void BeginPlay() override;
	
	void InitAbilitySystem(AController* InController);

	void SetupAbilities();

	void ApplyStartupAttributes();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
	TMap<TSubclassOf<UGameplayAbility>, ETTAbilityInputID> Abilities;

	UPROPERTY(BlueprintReadOnly)
	TMap<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle> GivenAbilities;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> AttributesEffect;

private:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTTInteractComponent* InteractComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTTInventoryComponent* InventoryComponent;
};
