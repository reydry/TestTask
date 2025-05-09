// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTInventoryComponent.generated.h"

class UTTBaseWeapon;
class ATestTaskCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASK_API UTTInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTTInventoryComponent();

	UFUNCTION(BlueprintCallable)
	void AddWeapon(UObject* InWeapon);

	UFUNCTION(BlueprintCallable)
	void SetCurrentWeapon(UTTBaseWeapon* InWeapon);

	UFUNCTION(BlueprintPure)
	TArray<UTTBaseWeapon*> GetWeapons();

	UFUNCTION(BlueprintPure)
	UTTBaseWeapon* GetCurrentWeapon() const;

	UFUNCTION(BlueprintPure)
	static UTTInventoryComponent* GetInventoryComponentFromActor(AActor* InActor);

protected:
	ATestTaskCharacter* GetTTCharacter() const;

private:
	UPROPERTY()
	UTTBaseWeapon* CurrentWeapon;

	UPROPERTY()
	TArray<UTTBaseWeapon*> Weapons;
};
