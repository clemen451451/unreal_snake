// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodApple.h"
#include "SnakeBase.h"

// Sets default values
AFoodApple::AFoodApple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoodApple::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoodApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AFoodApple::GetFoodType()
{
	UE_LOG(LogTemp, Warning, TEXT("AFoodApple::GetFoodType"));
	return 111;
}

void AFoodApple::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			this->Destroy();
			Snake->AddSnakeElement();
		}
	}
}