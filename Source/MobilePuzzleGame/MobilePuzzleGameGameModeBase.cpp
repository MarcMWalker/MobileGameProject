// Fill out your copyright notice in the Description page of Project Settings.

#include "MobilePuzzleGameGameModeBase.h"
#include "UObject/ConstructorHelpers.h"


AMobilePuzzleGameGameModeBase::AMobilePuzzleGameGameModeBase ()
{
	static ConstructorHelpers::FClassFinder <APawn> PawnClass (TEXT ("Class'/Script/MobilePuzzleGame.SphericalCameraDirector'"));

	if (PawnClass.Class)
	{
		DefaultPawnClass = PawnClass.Class;
	}
}