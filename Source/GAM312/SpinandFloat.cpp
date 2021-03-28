// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinandFloat.h"
#include "GameFramework/Actor.h" //needed for GetOwner functionality

// Sets default values
ASpinandFloat::ASpinandFloat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpinandFloat::BeginPlay()
{
	Super::BeginPlay();
	//initialize variable startLocation with get the location of it's actual location at start.
	startLocation = GetOwner()->GetActorLocation();
}

// Called every frame
void ASpinandFloat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Spin the actor
	GetOwner()->AddActorWorldRotation(spin * DeltaTime);
	
	//get time elapsed since level loaded
	float time = GetOwner()->GetWorld()->GetRealTimeSeconds();
	//set sine to calcutlate up and down locations
	float sine = FMath::Sin(time * FloatSpeedMultiplayer);
	GetOwner()->SetActorLocation(startLocation + (floater * sine));
}

