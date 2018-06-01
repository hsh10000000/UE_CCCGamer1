// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h"

enum DOORSTATE {
	OPEN,
	CLOSE,
	HALF,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CCCGAME1_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Area to open door
	UPROPERTY(EditAnywhere)
	ATriggerVolume *tvArea = nullptr;

	//A thing to open door
	UPROPERTY(EditAnywhere)
	AActor *actor2OpenDoor = nullptr;


private:
	//Control door
	void controlDoor(DOORSTATE state);
};