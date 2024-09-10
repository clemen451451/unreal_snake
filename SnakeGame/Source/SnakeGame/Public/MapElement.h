// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SNAKEGAME_API MapElement
{
public:
	MapElement(FVector _location, bool _bIsUsed);
	~MapElement();

	FVector Position;
	bool bIsUsed;
};
