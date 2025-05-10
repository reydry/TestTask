// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASK_API UTTHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTTHealthComponent();

protected:
	virtual void BeginPlay() override;	
	
};
