// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "GameFramework/GameModeBase.h"
#include "GAM312Character.h"
#include "GAM312GameMode.generated.h"

UENUM()
enum class EGamePlayState
{
	EPlaying,
	EGameOver,
	EUnknown
};

UCLASS(minimalapi)
class AGAM312GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGAM312GameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//set GAM312Character as instanced MyCharacter
	AGAM312Character* MyCharacter;

	UFUNCTION(BlueprintPure, category = "Health")
	EGamePlayState GetCurrentState() const;

	//declare SetCurrentState function with var type EGamePlayState named newState to pass in
	void SetCurrentState(EGamePlayState NewState);

private:
	EGamePlayState CurrentState;

	void HandleNewState(EGamePlayState NewState);

};



