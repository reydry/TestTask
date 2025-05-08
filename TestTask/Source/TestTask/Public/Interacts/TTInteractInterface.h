// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "TTInteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UTTInteractInterface : public UInterface
{
	GENERATED_BODY()
};


class TESTTASK_API ITTInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Interact();
	
};
