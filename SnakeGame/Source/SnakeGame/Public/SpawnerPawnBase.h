// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawnBase.h"
#include "SpawnerPawnBase.generated.h"

UCLASS()
class SNAKEGAME_API ASpawnerPawnBase : public APlayerPawnBase
{
	GENERATED_BODY()
	

public:
	TArray<MapElement> MapElements;

	int32 MaxPositions = 359;

	float SpawnIntervalSize = 250.0f;

	APlayerPawnBase* PawnInstance;

public:
	void InitSpawner(APlayerPawnBase* instance);
	void GenerateMapPositions();
	void SpawnFoods(int32 amount);
	int32 GetRandomFreePosition();
	float GetDistance(FVector firstLocation, FVector secondLocation);
};
