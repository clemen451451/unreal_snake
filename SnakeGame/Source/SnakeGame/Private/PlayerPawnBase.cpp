// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Food.h"
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
	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor();
	GenerateMapPositions();
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

	float SpawnIntervalSize = 250.0;

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

		MapPositions.Add(FVector(CurrentX, CurrentY, 0));
	
		APlayerPawnBase::SpawnElementRandom(MapPositions[i]);
	}
}

void APlayerPawnBase::SpawnElementRandom(FVector Location)
{
	auto let = GetWorld()->SpawnActor<AFood>(FoodActorClass, Location, FRotator());

	if (IsValid(let))
	{
		UE_LOG(LogTemp, Warning, TEXT("VALID %s"), *let->GetName());
	}
	else UE_LOG(LogTemp, Warning, TEXT("NO VALID"));
}

