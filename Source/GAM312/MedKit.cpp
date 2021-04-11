// Fill out your copyright notice in the Description page of Project Settings.


#include "MedKit.h"
#include "GAM312Character.h"

// Sets default values
AMedKit::AMedKit()
{
	//fires when beginoverlap with other actor
	OnActorBeginOverlap.AddDynamic(this, &AMedKit::OnOverlap);

}

void AMedKit::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	//if otherActor isn't null and other actor isn't itself (medkit)
	if (OtherActor != nullptr && OtherActor != this)
	{
		//Set GAM312Character pointer to MyCharacter ref; cast to GAM312Character
		class AGAM312Character* MyCharacter = Cast<AGAM312Character>(OtherActor);

		if (MyCharacter && MyCharacter->GetHealth() < 1.0f)
		{
			//update health to 100 on character is character health is less than 1.0f
			MyCharacter->UpdateHealth(100.0f);
			//destroy medkit on use
			Destroy();
		}
	}
}

