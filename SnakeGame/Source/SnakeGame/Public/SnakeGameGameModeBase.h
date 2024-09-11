// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API ASnakeGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	int Scores = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bool Info")
	bool bIsFinish = false;
};
