// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class GAM312_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame 
	// These are the actual functions that are called every frame which are called from CPP; we declare a Time
	//to next Camera Change float as well.
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = Cameras)
	AActor* CameraOne;

	UPROPERTY(EditAnywhere, Category = Cameras)
	AActor* CameraTwo;

	float TimeToNextCameraChange;
};
