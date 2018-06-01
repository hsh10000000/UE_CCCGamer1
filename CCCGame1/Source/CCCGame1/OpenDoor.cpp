// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	actor2OpenDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (tvArea == nullptr || actor2OpenDoor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Opendoor tick empty point error!"));
		return;
	}
	if (tvArea->IsOverlappingActor(actor2OpenDoor))
	{
		controlDoor(HALF);
	}
	else
	{
		controlDoor(CLOSE);
	}
}

void UOpenDoor::controlDoor(DOORSTATE state)
{
	switch (state)
	{
	case OPEN:
		GetOwner()->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
		break;
	case CLOSE:
		GetOwner()->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		break;
	case HALF:
		GetOwner()->SetActorRotation(FRotator(0.0f, -60.0f, 0.0f));
		break;
	default:
		GetOwner()->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

