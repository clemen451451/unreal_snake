// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapElement.h"
#include "FoodApple.h"
#include "FoodBread.h"
#include "Obstacles.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"

class UCameraComponent;
class ASnakeBase;

UCLASS()
class SNAKEGAME_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* PawnCamera;

	UPROPERTY(BlueprintReadWrite)
	ASnakeBase* SnakeActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeBase> SnakeActorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFoodApple> FoodAppleClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFoodBread> FoodBreadClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AObstacles> ObstaclesClass;

	TArray<MapElement> MapElements;

	IFood* Food;

	int32 MaxPositions = 359;

	float SpawnIntervalSize = 250.0f;

	FTimerHandle CountdownTimerHandle;

	int32 CountdownTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CreateSnakeActor();
	void MoveCamera(float DeltaTime);

	UFUNCTION()
	void HandlePlayerVerticalInput(float value);

	UFUNCTION()
	void HandlePlayerHorizontalInput(float value);

	void GenerateMapPositions();
	void SpawnFoods(int32 amount);
	void SpawnObstacles(int32 amount);
	int32 GetRandomFreePosition();
	float GetDistance(FVector firstLocation, FVector secondLocation);
	void AdvanceTimer();
};
