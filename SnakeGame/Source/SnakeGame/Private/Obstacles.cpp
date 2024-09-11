// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles.h"
#include "SnakeBase.h"
#include "SnakeGameGameModeBase.h"

AObstacles::AObstacles()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AObstacles::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstacles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacles::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->Destroy();

			auto GameMode = Cast<ASnakeGameGameModeBase>(GetWorld()->GetAuthGameMode());

			if (IsValid(GameMode))
			{
				GameMode->bIsFinish = true;
			}
		}
	}
}
