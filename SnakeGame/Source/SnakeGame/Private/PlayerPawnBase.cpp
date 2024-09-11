// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "MapElement.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"

APlayerPawnBase::APlayerPawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;
}

void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();

	CountdownTime = 3;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &APlayerPawnBase::AdvanceTimer, 1.0f, true);

	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor();
	GenerateMapPositions();
	SpawnFoods(50);
}

void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCamera(DeltaTime);
}

void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontalInput);
}

void APlayerPawnBase::AdvanceTimer()
{
	--CountdownTime;
	if (CountdownTime < 1)
	{
		SpawnFoods(2);
		CountdownTime = 10;
	}
}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
}

void APlayerPawnBase::HandlePlayerVerticalInput(float value)
{
	if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::DOWN)
	{
		SnakeActor->LastMoveDirection = EMovementDirection::UP;
	}
	else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::UP)
	{
		SnakeActor->LastMoveDirection = EMovementDirection::DOWN;
	}
}

void APlayerPawnBase::HandlePlayerHorizontalInput(float value)
{
	if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::LEFT)
	{
		SnakeActor->LastMoveDirection = EMovementDirection::RIGHT;
	}
	else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::RIGHT)
	{
		SnakeActor->LastMoveDirection = EMovementDirection::LEFT;
	}
}

void APlayerPawnBase::MoveCamera(float DeltaTime)
{
	FVector CurrentLocation(RootComponent->GetComponentTransform().GetLocation());
	FVector CurrentSnakeLocation(SnakeActor->SnakeHeadElement->GetActorLocation());

	RootComponent->SetWorldLocation
	(
		FVector
		(
			FMath::FInterpTo(CurrentLocation.X, CurrentSnakeLocation.X, DeltaTime, 0.8f),
			FMath::FInterpTo(CurrentLocation.Y, CurrentSnakeLocation.Y, DeltaTime, 0.8f), 
			1350.0f
		),
		false
	);
}

void APlayerPawnBase::GenerateMapPositions()
{
	float MapMinX = 1993.0f;
	float MapMaxX = -2435.0f;

	float MapMinY = 2500.0f;
	float MapMaxY = -2500.0f;

	float CurrentX = MapMinX;
	float CurrentY = MapMinY;

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

int32 APlayerPawnBase::GetRandomFreePosition()
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

void APlayerPawnBase::SpawnFoods(int32 amount)
{
	for (int i = 0; i < amount; i++)
	{
		int32 randomPosition = APlayerPawnBase::GetRandomFreePosition();

		if (APlayerPawnBase::GetDistance(SnakeActor->GetActorLocation(), MapElements[randomPosition].Position) < SpawnIntervalSize)
			continue;

		MapElements[randomPosition].bIsUsed = true;

		auto randomType = FMath::RandRange(0, 3);

		switch (randomType)
		{
			case 0: GetWorld()->SpawnActor<AFoodApple>(FoodAppleClass, MapElements[randomPosition].Position, FRotator());
				break;
			default: GetWorld()->SpawnActor<AFoodBread>(FoodBreadClass, MapElements[randomPosition].Position, FRotator());
				break;
		}
	}
}

float APlayerPawnBase::GetDistance(FVector firstLocation, FVector secondLocation)
{
	return (firstLocation - secondLocation).Size();
}

