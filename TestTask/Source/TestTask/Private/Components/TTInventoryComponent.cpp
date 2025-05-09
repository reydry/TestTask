// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TTInventoryComponent.h"
#include "Weapons/TTBaseWeapon.h"
#include "TestTask/TestTaskCharacter.h"

UTTInventoryComponent::UTTInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTTInventoryComponent::AddWeapon(UObject* InWeapon)
{
	UTTBaseWeapon* Weapon = Cast<UTTBaseWeapon>(InWeapon);
	
	if (IsValid(Weapon))
	{
		Weapons.Add(Weapon);
		SetCurrentWeapon(Weapon);
	}
}

void UTTInventoryComponent::SetCurrentWeapon(UTTBaseWeapon* InWeapon)
{
	ATestTaskCharacter* Character = GetTTCharacter();

	if (!IsValid(InWeapon) || !IsValid(Character))
	{
		return;
	}

	if (IsValid(CurrentWeapon))
	{
		TSubclassOf<UGameplayAbility> Ability = CurrentWeapon->GetAbility();
		Character->RemoveAbility(Ability);
	}

	CurrentWeapon = InWeapon;
	UStaticMeshComponent* ItemMesh = Character->GetItemMesh();

	if (IsValid(ItemMesh))
	{
		ItemMesh->SetStaticMesh(CurrentWeapon->GetMesh());
	}

	Character->GiveAbility(CurrentWeapon->GetAbility(), 0, static_cast<int32>(CurrentWeapon->GetInputID()));
}

TArray<UTTBaseWeapon*> UTTInventoryComponent::GetWeapons()
{
	return Weapons;
}

UTTBaseWeapon* UTTInventoryComponent::GetCurrentWeapon() const
{
	return CurrentWeapon;
}

UTTInventoryComponent* UTTInventoryComponent::GetInventoryComponentFromActor(AActor* InActor)
{
	return (InActor ? InActor->FindComponentByClass<UTTInventoryComponent>() : nullptr);
}

ATestTaskCharacter* UTTInventoryComponent::GetTTCharacter() const
{
	return (GetOwner() ? Cast<ATestTaskCharacter>(GetOwner()) : nullptr);
}

