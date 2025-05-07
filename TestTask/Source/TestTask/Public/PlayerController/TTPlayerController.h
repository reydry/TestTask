// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TTPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class TESTTASK_API ATTPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATTPlayerController();

protected:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	void MoveInput(const FInputActionValue& InputActionValue);

	void LookInput(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Look;
	
};
