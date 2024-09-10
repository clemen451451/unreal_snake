// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerPawnBase.h"
#include "PlayerPawnBase.h"
#include "SnakeBase.h"
#include "MapElement.h"
#include "SnakeElementBase.h"

void ASpawnerPawnBase::InitSpawner(APlayerPawnBase* instance)
{
	UE_LOG(LogTemp, Warning, TEXT("InitSpawner"));

	PawnInstance = instance;

	GenerateMapPositions();
	SpawnFoods(300);
}

void ASpawnerPawnBase::GenerateMapPositions()
{
	float MapMinX = 1993.0f;
	float MapMaxX = -2435.0f;

	float MapMinY = 2500.0f;
	float MapMaxY = -2500.0f;

	float CurrentX = MapMinX;
	float CurrentY = MapMinY;

	UE_LOG(LogTemp, Warning, TEXT("GenerateMapPositions"));

	for (int i = 0; i < MaxPositions; i++)
	{
		CurrentY = CurrentY - SpawnIntervalSize;

		if (CurrentY <= MapMaxY)
		{
			CurrentY = MapMinY;
			CurrentX = CurrentX - SpawnIntervalSize;
		}

		MapElements.Add(MapElement(FVector(CurrentX, CurrentY, 0), false));
	}
}

int32 ASpawnerPawnBase::GetRandomFreePosition()
{
	TArray<int32> freeElements;
	int32 count = 0;

	for (int i = 0; i < MaxPositions; i++)
	{
		if (MapElements[i].bIsUsed == false)
		{
			freeElements.Add(i);
			count++;
		}
	}

	auto randomInt = FMath::RandRange(0, count - 1);
	return freeElements[randomInt];
}

void ASpawnerPawnBase::SpawnFoods(int32 amount)
{
	UE_LOG(LogTemp, Warning, TEXT("SPAWNFOODS"));

	for (int i = 0; i < amount; i++)
	{
		int32 randomPosition = ASpawnerPawnBase::GetRandomFreePosition();

		//if (AMapSpawnerPawn::GetDistance(SnakeActor->GetActorLocation(), MapElements[randomPosition].Position) < SpawnIntervalSize)
		//	continue;

		//GetWorld()->SpawnActor<AFood>(FoodActorClass, MapElements[randomPosition].Position, FRotator());

		if(IsValid(FoodActorClass->GetClass()))
			GetWorld()->SpawnActor<AFood>(FoodActorClass->GetClass(), FTransform());
	}
}

float ASpawnerPawnBase::GetDistance(FVector firstLocation, FVector secondLocation)
{
	return (firstLocation - secondLocation).Size();
}

