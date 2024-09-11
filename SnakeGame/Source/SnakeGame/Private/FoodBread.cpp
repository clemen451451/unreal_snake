// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodBread.h"
#include "SnakeBase.h"

// Sets default values
AFoodBread::AFoodBread()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoodBread::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoodBread::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AFoodBread::GetFoodType()
{
	return 1;
}

void AFoodBread::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			this->Destroy();
			Snake->AddSnakeElement();
			Snake->AddSnakeSpeed(0.5f);
		}
	}
}