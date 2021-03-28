// Fill out your copyright notice in the Description page of Project Settings.


#include "MyOnHit.h"
#include "Components/BoxComponent.h" //get the header for boxcomponent.h
#include "kismet/GameplayStatics.h"

// Sets default values
AMyOnHit::AMyOnHit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create default values in init function
	MyComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	//set boolean of simulate physics to true
	MyComp->SetSimulatePhysics(true);
	//Set notify for rigid body collision to true/ interact with other objects with collision
	MyComp->SetNotifyRigidBodyCollision(true);
	//Set the collision profile to block all dynamic collision profile objects
	MyComp->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	//when it hits something else, run the OnCompHit function
	MyComp->OnComponentHit.AddDynamic(this, &AMyOnHit::OnCompHit);
	//Set MyComp to root component
	RootComponent = MyComp;
}

// Called when the game starts or when spawned
void AMyOnHit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyOnHit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//On Component hit function (runs on every frame)
void AMyOnHit::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector
	NormalImpulse, const FHitResult& Hit) {

	//lets do some checks for if the actor hits something; we'll make sure those other actors/components aren't null or ourselves (this)
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (GEngine)
		{
			//Add a debug message for 5 seconds in green with text "I hit: item hit, and name of other actor
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"),
			*OtherActor->GetName()));
				
			//Destroy what it hits, then destory itself; still displays debug text
			OtherActor->Destroy();
			Destroy();
		}
		
	}


}
