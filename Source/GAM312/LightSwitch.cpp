// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitch.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"

// Sets default values
ALightSwitch::ALightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//set default parameters in constructor
	LightIntensity = 3000.0f;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->Intensity = LightIntensity;
	//PointLight->bVisible = true; //looks like bVisible was deprecated
	RootComponent = PointLight;

	//create sphere for overlap
	LightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Component"));
	LightSphere->InitSphereRadius(400.0f);
	//add collision profile trigger
	LightSphere->SetCollisionProfileName(TEXT("Trigger"));
	//attach to root component
	LightSphere->SetupAttachment(RootComponent);
	//on overlap
	LightSphere->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitch::OnOverlapBegin);
	//on end overlap
	LightSphere->OnComponentEndOverlap.AddDynamic(this, &ALightSwitch::OnOverlapEnd);
	
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	//draw debug helper from actor location at 300 radius, don't delete and set size.
	DrawDebugSphere(GetWorld(), GetActorLocation(), 300.0f, 50, FColor::Yellow, true, -1, 0, 2);
	ToggleLight();
}

// Called every frame
void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//overlap begin function; we'll call the togglelight function and turn the light on
void ALightSwitch::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}
//overlap end function; after we leave the overlap area, we'll turn the light back off.
void ALightSwitch::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}
//toggle visibility method; this is the simple method that turns visibility off
void ALightSwitch::ToggleLight()
{
	PointLight->ToggleVisibility();
}