// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyOnHit.generated.h"

UCLASS()
class GAM312_API AMyOnHit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyOnHit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//set UPROPERTY for Unreal and allow you to view via BP
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* MyComp;

	//Create function used for On Component hit; we'll include the typical properties as recommended by Epic
	//What's being hit, what's been hit, etc.
	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
		const FHitResult& Hit);

};
