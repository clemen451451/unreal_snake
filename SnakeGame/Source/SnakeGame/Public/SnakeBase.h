// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawnBase.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class SNAKEGAME_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY()
	EMovementDirection LastMoveDirection = EMovementDirection::UP;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;
	
	UPROPERTY(EditDefaultsOnly)
	float MovementSpeedTail;

	UPROPERTY(EditDefaultsOnly)
	int32 StartElementsAmount;

	UPROPERTY(BlueprintReadWrite)
	ASnakeElementBase* SnakeHeadElement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddSnakeElement(int ElementsSum = 1, bool SnakeInit = false);
	void AddSnakeSpeed(float Speed);
	void AddSnakeScore(int Score);
	void Move(float DeltaTime);

	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);
};
