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
	
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (tvArea == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Opendoor tick empty point error!"));
		return;
	}
	if (getWeightInArea()>= weight2Open)
	{
		controlDoor(OPEN);
	}
	else
	{
		controlDoor(CLOSE);
	}
}

void UOpenDoor::CFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("this is a c++ function."));
}

void UOpenDoor::controlDoor(DOORSTATE state)
{
	switch (state)
	{
	case OPEN:
		onOpenDoor.Broadcast();
		break;
	case CLOSE:
		onCloseDoor.Broadcast();
		break;
	default:
		GetOwner()->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

float UOpenDoor::getWeightInArea()
{
	//获取与判定区域重合的数组
	TArray<AActor*> overLappingActors;
	tvArea->GetOverlappingActors(overLappingActors);

	float totalWeight = 0.0f;
	for (int i=0;i<overLappingActors.Num();++i)
	{
		totalWeight += overLappingActors[i]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return totalWeight;
}

