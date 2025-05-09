// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/TTBaseWeapon.h"

UStaticMesh* UTTBaseWeapon::GetMesh() const
{
	return Mesh;
}

TSubclassOf<UGameplayAbility> UTTBaseWeapon::GetAbility() const
{
	return Ability;
}

int32 UTTBaseWeapon::GetAmmo() const
{
	return Ammo;
}

int32 UTTBaseWeapon::GetMaxAmmo() const
{
	return MaxAmmo;
}

int32 UTTBaseWeapon::GetAmmoInClip() const
{
	return AmmoInClip;
}

ETTAbilityInputID UTTBaseWeapon::GetInputID() const
{
	return InputID;
}

void UTTBaseWeapon::SetAmmo(int32 InAmmo)
{
	Ammo = InAmmo;
}

void UTTBaseWeapon::SetMaxAmmo(int32 InAmmo)
{
	MaxAmmo = InAmmo;
}
