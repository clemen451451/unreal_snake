// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovementDirection::DOWN;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);

	AddSnakeElement(4);
}

// Called every frame

void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsSum)
{
	if (!IsValid(SnakeElementClass))
		return;

	for (int i = 0; i < ElementsSum; ++i)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);

		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);

		NewSnakeElem->SnakeOwner = this;

		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);

		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType();
		}
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector(ForceInitToZero);
	float speed = ElementSize;

	switch(LastMoveDirection)
	{
		case EMovementDirection::UP:
			MovementVector.X += speed;
			break;
		case EMovementDirection::DOWN:
			MovementVector.X -= speed;
			break;
		case EMovementDirection::LEFT:
			MovementVector.Y += speed;
			break;
		case EMovementDirection::RIGHT:
			MovementVector.Y -= speed;
			break;
	}

	if (!IsValid(SnakeElementClass))
		return;

	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];

		if (IsValid(PrevElement))
		{
			FVector PrevLocation = PrevElement->GetActorLocation();
			CurrentElement->SetActorLocation(PrevLocation);
		}
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		UE_LOG(LogTemp, Warning, TEXT("SnakeElementOverlap 1"));

		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool isFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);

		if (InteractableInterface)
		{
			UE_LOG(LogTemp, Warning, TEXT("SnakeElementOverlap 2"));

			InteractableInterface->Interact(this, isFirst);
		}
	}
}

