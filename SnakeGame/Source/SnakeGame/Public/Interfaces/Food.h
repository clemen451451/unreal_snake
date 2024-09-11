// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Food.generated.h"

UINTERFACE(MinimalAPI)
class UFood : public UInterface
{
	GENERATED_BODY()
};

class SNAKEGAME_API IFood
{
	GENERATED_BODY()

public:
	virtual int GetFoodType() = 0;
};
