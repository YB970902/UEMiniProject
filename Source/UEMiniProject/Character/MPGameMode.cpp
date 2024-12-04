// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MPGameMode.h"
#include "Character/MPPlayerController.h"
#include "Character/CharacterBase.h"

AMPGameMode::AMPGameMode()
{
	PlayerControllerClass = AMPPlayerController::StaticClass();
	DefaultPawnClass = ACharacterBase::StaticClass();
}
