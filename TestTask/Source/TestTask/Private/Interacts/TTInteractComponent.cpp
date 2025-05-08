// Fill out your copyright notice in the Description page of Project Settings.


#include "Interacts/TTInteractComponent.h"
#include "Interacts/TTInteractInterface.h"

UTTInteractComponent::UTTInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UTTInteractComponent* UTTInteractComponent::GetInteractionComponentFromActor(AActor* InActor)
{
	return InActor ? InActor->FindComponentByClass<UTTInteractComponent>() : nullptr;
}

TArray<AActor*> UTTInteractComponent::GetInteractionObjectsArray()
{
	return InteractionObjects;
}

void UTTInteractComponent::AddInteractionObject(AActor* InObject)
{
	if (InObject->Implements<UTTInteractInterface>())
	{
		InteractionObjects.AddUnique(InObject);
	}
}

void UTTInteractComponent::RemoveInteractionObject(AActor* InObject)
{
	if (InObject->Implements<UTTInteractInterface>())
	{
		InteractionObjects.Remove(InObject);
	}
}


