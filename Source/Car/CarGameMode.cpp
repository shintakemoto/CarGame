// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CarGameMode.h"
#include "CarPawn.h"
#include "CarHud.h"

ACarGameMode::ACarGameMode()
{
	//DefaultPawnClass = ACarPawn::StaticClass();
	HUDClass = ACarHud::StaticClass();
}
