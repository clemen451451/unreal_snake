// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StartElementsAmount = 4;
	MovementSpeed = 5.0f;
	MovementSpeedTail = 4.0f;
	ElementSize = 100.f;
	LastMoveDirection = EMovementDirection::DOWN;
	SnakeHeadElement = nullptr;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();

	AddSnakeElement(StartElementsAmount, true);
}

// Called every frame

void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void ASnakeBase::AddSnakeElement(int ElementsSum, bool SnakeInit)
{
	if (!IsValid(SnakeElementClass))
		return;

	for (int i = 0; i < ElementsSum; ++i)
	{
		FVector NewLocation(!SnakeInit ? -1000.0f : SnakeElements.Num() * ElementSize, 0, !SnakeInit ? 500.0f : 0);
		FTransform NewTransform(NewLocation);

		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);

		NewSnakeElem->SnakeOwner = this;

		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		int32 LastSnakeElementIndex = SnakeElements.Num() - 1;

		bool bIsLastElement = LastSnakeElementIndex == ElemIndex ? true : false;

		if (StartElementsAmount > ElemIndex)
			bIsLastElement = false;

		if (ElemIndex == 1 || bIsLastElement)
			NewSnakeElem->MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if(bIsLastElement)
			NewSnakeElem->SetActorScale3D(FVector(1.5f));

		if (ElemIndex == 0)
		{
			SnakeHeadElement = NewSnakeElem;

			NewSnakeElem->SetFirstElementType();
		}
	}
}

void ASnakeBase::Move(float DeltaTime)
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
			CurrentElement->SetActorLocation
			(
				FMath::VInterpTo(CurrentElement->GetActorLocation(), PrevElement->GetActorLocation(), DeltaTime, MovementSpeedTail),
				false
			);

			if(i >= StartElementsAmount)
				CurrentElement->SetActorScale3D(FMath::VInterpTo(CurrentElement->GetActorScale3D(), FVector(0.5f), DeltaTime, 4.0f));
		}
	}

	FVector MoveDirection(FMath::VInterpTo(SnakeElements[0]->GetActorLocation(), SnakeElements[0]->GetActorLocation() + MovementVector, DeltaTime, MovementSpeed));

	SnakeElements[0]->SetActorLocation(MoveDirection, false);
	SnakeElements[0]->ToggleCollision();
}


void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);

		bool isFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);

		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, isFirst);
		}
	}
}

void ASnakeBase::AddSnakeSpeed(float Speed)
{
	MovementSpeed += Speed;
	MovementSpeedTail += Speed;
}

