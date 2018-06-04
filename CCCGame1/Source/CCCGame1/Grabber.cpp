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

	setPhysicsHandleComponent();
	setInputComponent();
	
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (phyHandle->GetGrabbedComponent())
	{
		phyHandle->SetTargetLocationAndRotation(getLineEndPoint(), FRotator(0.0f,0.0f,0.0f));
	}
	
}

//����������
FVector UGrabber::getLineStartPoint()
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotator;
	//��ȡ��ɫλ�ú���ת����
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotator);

	return PlayerViewLocation;
}

//��������յ�
FVector UGrabber::getLineEndPoint()
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotator;
	//��ȡ��ɫλ�ú���ת����
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotator);

	FVector lineTraceEndLocation = PlayerViewLocation + PlayerViewRotator.Vector()*reach;

	return lineTraceEndLocation;
}

//������ߵ�һ������������
FHitResult UGrabber::getLineFirstReachObject()
{
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByObjectType(
		hitResult,
		getLineStartPoint(),
		getLineEndPoint(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams("", false, GetOwner())//��������
	);

	return hitResult;
}

//�������������
bool UGrabber::setPhysicsHandleComponent()
{
	phyHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!phyHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("physics handle is missing!"));
		return false;
	}
	return true;
}

//�����������
bool UGrabber::setInputComponent()
{
	input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!input)
	{
		UE_LOG(LogTemp, Error, TEXT("input handle is missing!"));
		return false;
	}
	else
	{
		input->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::grab);
		input->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::release);
		return true;
	}
	
}

void UGrabber::grab()
{
	FHitResult hitResult = getLineFirstReachObject();
	if (!hitResult.GetActor())
		return;
	UPrimitiveComponent *component = hitResult.GetComponent();
	phyHandle->GrabComponentAtLocationWithRotation(
		component,
		NAME_None,
		hitResult.GetActor()->GetActorLocation(),
		hitResult.GetActor()->GetActorRotation()
	);
}

void UGrabber::release()
{
	if (!phyHandle->GetGrabbedComponent())
		return;
	phyHandle->ReleaseComponent();
}

