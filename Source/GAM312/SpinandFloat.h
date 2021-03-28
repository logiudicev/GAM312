// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpinandFloat.generated.h"

UCLASS()
class GAM312_API ASpinandFloat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpinandFloat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	//declare FRotator spin variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Settings")
	FRotator spin;
	//declare FVector floater
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Settings")
	FVector floater;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Settings")
	float FloatSpeedMultiplayer;

private:
	//declare variable to tell where actor is at start
	FVector startLocation;


};
