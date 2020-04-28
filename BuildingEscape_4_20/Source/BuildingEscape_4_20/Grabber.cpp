// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	SetupInputComponent();

	FindPhysicsHandleComponent();
	
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

/// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" %s missing handle physics component"), *(GetOwner()->GetName()));
	}
}

/// Look for attached InputComponent (only appears at run time)
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" %s has Pawn Movement Component"), *(GetOwner()->GetName()));
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{

	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);


	FHitResult Hit;
	FCollisionQueryParams TraceParameters(FName(""), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(Hit,
											PlayerViewPointLocation,
											LineTraceEnd,
											FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
											TraceParameters);

	if (Hit.GetActor() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Hit: %s"), *Hit.GetActor()->GetName());
	}
	return FHitResult();
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Press grab button"));
	GetFirstPhysicsBodyInReach();
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release grab button"));
}
