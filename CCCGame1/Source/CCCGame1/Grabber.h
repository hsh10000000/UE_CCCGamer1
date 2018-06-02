// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CCCGAME1_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//射线长度
	UPROPERTY(EditAnywhere)
	float reach = 100.0f;
	
	//获得射线起点
	FVector getLineStartPoint();

	//获得射线终点
	FVector getLineEndPoint();

	//获得射线第一个碰到的物体
	FHitResult getLineFirstReachObject();

	//输入组件
	UInputComponent *input = nullptr;

	//物理句柄组件
	UPhysicsHandleComponent *phyHandle = nullptr;
	
	//设置物理句柄组件
	bool setPhysicsHandleComponent();

	//设置输入组件
	bool setInputComponent();

	//拿起和放开事件
	void grab();
	void release();
};
