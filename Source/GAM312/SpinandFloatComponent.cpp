// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinandFloatComponent.h"

// Sets default values for this component's properties
USpinandFloatComponent::USpinandFloatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpinandFloatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	startLocation = GetOwner()->GetActorLocation();//initialize variable startLocation with get the location of it's actual location at start.
}


// Called every frame
void USpinandFloatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//Spin the actor
	GetOwner()->AddActorWorldRotation(spin * DeltaTime);

	//get time elapsed since level loaded
	float time = GetOwner()->GetWorld()->GetRealTimeSeconds();
	//set sine to calcutlate up and down locations
	float sine = FMath::Sin(time * FloatSpeedMultiplayer);
	GetOwner()->SetActorLocation(startLocation + (floater * sine));
}

