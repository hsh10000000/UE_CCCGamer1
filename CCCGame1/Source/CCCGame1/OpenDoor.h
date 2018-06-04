// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "OutputDeviceDebug.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FControlDoor);

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
	float weight2Open = 25.0f;

	UFUNCTION(BlueprintCallable, Category = "OpenDoor")
	void CFunction();

	UPROPERTY(BlueprintAssignable)
	FControlDoor onOpenDoor;

	UPROPERTY(BlueprintAssignable)
	FControlDoor onCloseDoor;

private:
	//Control door
	void controlDoor(DOORSTATE state);

	//获取重量
	float getWeightInArea();


	
};
