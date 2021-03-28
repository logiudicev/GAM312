// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitch.generated.h"

UCLASS()
class GAM312_API ALightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	class UPointLightComponent* PointLight; //declare the pointlight

	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	class USphereComponent* LightSphere; //declare the sphere component

	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	float LightIntensity; //declare the light intensity variable

	UFUNCTION()
	void ToggleLight(); //declare toggle light function

	// declare overlap begin function (when we enter overlap)
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* 
			OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function (when we exit overlap)
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* 
			OtherComp, int32 OtherBodyIndex);
};
