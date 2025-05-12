// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TTHeroComponent.h"
#include "Characters/TTCharacter.h"
#include "TestTaskCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UTTHeroComponent;

UCLASS(config=Game)
class ATestTaskCharacter : public ATTCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TPCamera;

public:
	ATestTaskCharacter();

	USpringArmComponent* GetCameraBoom() const;

	UCameraComponent* GetTPCamera() const;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTTHeroComponent* HeroComponent;
};

