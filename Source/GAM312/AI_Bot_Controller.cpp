// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Bot_Controller.h"
#include "AI_Bot_Character.h"
#include "Waypoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GAM312Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
AAI_Bot_Controller::AAI_Bot_Controller()
{
	//set tick to true
	PrimaryActorTick.bCanEverTick = true;
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	//Sight Settings
	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;


	//Give perception component all settings from sight

	//Give dominant sense, sight
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAI_Bot_Controller::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AAI_Bot_Controller::BeginPlay()
{
	//calling super function from derived class
	Super::BeginPlay();

	

	if (GetPerceptionComponent() != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("So far, so good!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Something went wrong"));
	}
}

//possess is deprecated; use OnPossess
void AAI_Bot_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AAI_Bot_Controller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (DistanceToPlayer > AISightRadius)
	{
		bIsPlayerDetected = false;
	}

	AAI_Bot_Character* BotCharacter = Cast<AAI_Bot_Character>(GetPawn());
	if (BotCharacter->NextWaypoint != nullptr && bIsPlayerDetected == false) 
	{
		MoveToActor(BotCharacter->NextWaypoint, 5.0f);
	}
	else if (bIsPlayerDetected == true)
	{
		AGAM312Character* Player = Cast<AGAM312Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		MoveToActor(Player, 5.0f);
	}
}

FRotator AAI_Bot_Controller::GetControlRotation() const
{
	if (GetPawn() == nullptr) {
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AAI_Bot_Controller::OnPawnDetected(const TArray<AActor*> &DetectedPawns)
{
	for (size_t i = 0; i < DetectedPawns.Num(); i++)
	{
		DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
		UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), DistanceToPlayer);
	}
	bIsPlayerDetected = true;
}




