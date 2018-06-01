// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewLocation;
	FRotator PlayerViewRotator;
	//获取角色位置和旋转方向
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotator);

	FVector lineTraceEndLocation = PlayerViewLocation + PlayerViewRotator.Vector()*reach;

	//绘制线条
	/*DrawDebugLine(
		GetWorld(),
		PlayerViewLocation,
		lineTraceEndLocation,
		FColor::Red,
		false,
		0.0f,
		0,
		10
	);*/
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByObjectType(
		hitResult,
		PlayerViewLocation,
		lineTraceEndLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams("", false, GetOwner())//忽略自身
	);
	AActor *actHit = hitResult.GetActor();
	if (!actHit)
		return;

	UE_LOG(LogTemp, Log, TEXT("Hit name: %s"), *(actHit->GetName()));

}

