// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpinandFloatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAM312_API USpinandFloatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpinandFloatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
