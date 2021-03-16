// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//two floats that set time between and time of blend in camera action
	const float TimeBetweenCameraChange = 15.0f;
	const float SmoothBlendTime = 5.75f;

	TimeToNextCameraChange -= DeltaTime;
	//when the time comes to change over, we do a quick check that TimeToNextCamera
	//Change is <=0, then we add to TimeBetweenCameraChange to keep the ball rolling
	//We assign our player controller (this was not mentioned in the video; however, the 
	//original UE4 tutorial discusses it.
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChange;

		//Find the actor that handles control for the local player.
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		//we check if OurPlayerController is valid, and if it is, if CameraTwo is valid, and the PC
		//is set to getviewTarget function is == CameraOne set here.
		if (OurPlayerController)
		{
			if (CameraTwo && (OurPlayerController->GetViewTarget() == CameraOne))
			{
				//Blend smoothly to camera two. Exactly so.
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
			else if (CameraOne)
			{
				//Cut instantly to camera one. Back to One
				OurPlayerController->SetViewTarget(CameraOne);
			}
		}
	}
}
