// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Food.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "FoodBread.generated.h"

UCLASS()
class SNAKEGAME_API AFoodBread : public AActor, public IFood, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodBread();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual int GetFoodType() override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};
