// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "CampFire.generated.h"

UCLASS()
class GAM312_API ACampFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACampFire();


	

public:	
	
	//Declare an instance of UParticleSystemComponent pointer called fire
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* Fire;
	
	//declare pointer for UBoxComponent
	UPROPERTY(EditAnywhere)
	UBoxComponent* MyBoxComponent;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> FireDamageType;

	UPROPERTY(EditAnywhere)
	AActor* MyCharacter;

	UPROPERTY(EditAnywhere)
	FHitResult MyHit;

	bool bCanApplyDamage;
	FTimerHandle FireTimerHandle;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare component overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ApplyFireDamage();
};
