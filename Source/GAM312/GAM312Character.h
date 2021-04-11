// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "GAM312Character.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AGAM312Character : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

public:
	AGAM312Character();

protected:
	virtual void BeginPlay();
	//override tick function declaration
	virtual void Tick(float DeltaTime) override;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AGAM312Projectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

	//Pointer for Camera ; This was omitted from the tutorial. You must specify the pointer for Camera Director.
	UPROPERTY(EditAnywhere)
	AActor* CameraDirector;

	//void SetCanBeDamaged(bool bInCanBeDamaged);
	UPROPERTY()
	bool bInCanBeDamaged;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);
	
	
	

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	//declare variables for UI/HUD functionality
	//declare float variable FullHealth, HealthPercentage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float FullHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthPercentage;
	//declare Magic Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	float FullMagic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	float Magic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	float MagicPercentage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	float PreviousMagic;
	//float Magic for how much we're using
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	float MagicValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool redFlash;
	//smoothly transition between two values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	UCurveFloat *MagicCurve;
	//Timeline
	UPROPERTY(EditAnywhere, Category = "Magic")
	UTimelineComponent* MyTimeline;
	//Declare timer handle to clear/stop referenced timers (2 seconds to determine interval when you can shoot)
	UPROPERTY(EditAnywhere, Category = "Magic")
	struct FTimerHandle MemberTimerHandle;
	//Will be used for 5 seconds wait time before magic bar refills
	UPROPERTY(EditAnywhere, Category = "Magic")
	struct FTimerHandle MagicTimerHandle;

	float CurveFloatValue;
	float TimelineValue;
	UPROPERTY(EditAnywhere, Category = "Magic")
	bool bCanUseMagic;

	//what we bind to our UI Element to determine how percent health is shown in health bar
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth();
	
	//return percentage of number of text value so UI can read it
	UFUNCTION(BlueprintPure, Category = "Health")
	FText GetHealthIntText();

	//what we bind to our UI Element to determine how percent Magic is shown in health bar
	UFUNCTION(BlueprintPure, Category = "Magic")
	float GetMagic();

	//return percentage of number of text value so UI can read it in Magic
	UFUNCTION(BlueprintPure, Category = "Magic")
	FText GetMagicIntText();
	
	//2 second start for invincibility
	UFUNCTION()
	void DamageTimer();
	
	//declare setters for DamgeState and MagicValue, MagicState
	UFUNCTION()
	void SetDamageState();
	UFUNCTION()
	void SetMagicValue();
	UFUNCTION()
	void SetMagicState();
	
	//SET MagicValue of MagicValue being passed through
	UFUNCTION()
	void SetMagicChange(float MagicChange);

	UFUNCTION()
	void UpdateMagic();

	//function to determine whether or not to play red flash animation
	UFUNCTION(BlueprintPure, Category = "Health")
	bool PlayFlash();
	
	//declare classes for GunDefault material and GunOverheat material
	UPROPERTY(EditAnyWhere, Category = "Magic")
	class UMaterialInterface* GunDefaultMaterial;

	UPROPERTY(EditAnyWhere, Category = "Magic")
	class UMaterialInterface* GunOverheatMaterial;

	//Receive point damage function declaration
	//UFUNCTION()
	//void TakePointDamage(float Damage, const UDamageType* DamageType, FVector HitLocation,
		//FVector HitNormal, UPrimitiveComponent* HitComponent, FName BoneNAme, FVector ShotFromDirection,
		//AController	* InstigatedBy, AActor* DamageCauser, const FHitResult& HitInfo);

	// void ReceivePointDamage(float Damage, const class UDamageType * DamageType, FVector HitLocation, FVector HitNormal, class UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, class AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo);
	UFUNCTION(BlueprintCallable, Category = "Power")
	void UpdateHealth(float HealthChange);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

private:
	void DisplayRaycast();

};

