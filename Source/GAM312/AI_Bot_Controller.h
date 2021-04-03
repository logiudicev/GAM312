// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Bot_Controller.generated.h"

/**
 * 
 */
UCLASS()
class GAM312_API AAI_Bot_Controller : public AAIController
{
	GENERATED_BODY()
	
public:
	AAI_Bot_Controller();
			//initialize function overrides
		virtual void BeginPlay() override;

		//Possess is deprecated, use On Possess
		virtual void OnPossess(APawn* InPawn) override;

		virtual void Tick(float DeltaSeconds) override;
		//always point in direction facing in
		virtual FRotator GetControlRotation() const override;

		//detect by detection component
		UFUNCTION()
		void OnPawnDetected(const TArray<AActor*> &DetectedPawns);

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 500.0f;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 10.0f;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightRadius = AISightRadius + 10.0f;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 90.0f;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;


		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool bIsPlayerDetected = false;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistanceToPlayer = 0.0f;
};
