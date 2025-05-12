// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTInteractComponent.generated.h"

class UTTAbilityInputConfig;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASK_API UTTInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTTInteractComponent();

	UFUNCTION(BlueprintPure)
	static UTTInteractComponent* GetInteractionComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintPure)
	TArray<AActor*> GetInteractionObjectsArray();

	UFUNCTION(BlueprintCallable)
	void AddInteractionObject(AActor* InObject);
	
	UFUNCTION(BlueprintCallable)
	void RemoveInteractionObject(AActor* InObject);

private:
	UPROPERTY()
	TArray<AActor*> InteractionObjects;
	
};
