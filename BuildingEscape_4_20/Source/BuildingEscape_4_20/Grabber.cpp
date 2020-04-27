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

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" %s has Pawn Movement Component"), *(GetOwner()->GetName()));
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{

	}

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle != nullptr)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" %s missing handle physics component"), *(GetOwner()->GetName()));
	}
	
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	


	
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
	
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

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
	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Press grab button"));
}