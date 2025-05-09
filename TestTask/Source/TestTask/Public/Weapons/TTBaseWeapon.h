// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TTHeroComponent.h"
#include "TTBaseWeapon.generated.h"

class UGameplayAbility;

UCLASS(Blueprintable)
class TESTTASK_API UTTBaseWeapon : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	UStaticMesh* GetMesh() const;

	UFUNCTION(BlueprintPure)
	TSubclassOf<UGameplayAbility> GetAbility() const;

	UFUNCTION(BlueprintPure)
	int32 GetAmmo() const;

	UFUNCTION(BlueprintPure)
	int32 GetMaxAmmo() const;

	UFUNCTION(BlueprintPure)
	int32 GetAmmoInClip() const;

	UFUNCTION(BlueprintPure)
	ETTAbilityInputID GetInputID() const;

	UFUNCTION(BlueprintCallable)
	void SetAmmo(int32 InAmmo);

	UFUNCTION(BlueprintCallable)
	void SetMaxAmmo(int32 InAmmo);

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly)
	int32 Ammo;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly)
	int32 AmmoInClip;

	UPROPERTY(EditDefaultsOnly)
	ETTAbilityInputID InputID;
};
