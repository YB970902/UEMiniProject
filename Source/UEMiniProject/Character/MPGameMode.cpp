// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MPGameMode.h"
#include "Character/MPPlayerController.h"
#include "Character/CharacterBase.h"

AMPGameMode::AMPGameMode()
{
/*
	struct FConstructorStatics
	{
		ConstructorHelpers::FClassFinder<ACharacterBase> CharacterBase;
		FConstructorStatics() :
			CharacterBase(TEXT("/Game/Model/BP_CharacterBase.BP_CharacterBase_C"))
		{
			check(CharacterBase.Succeeded());
		}
	};

	static FConstructorStatics ConstructorStatics;*/
	
	PlayerControllerClass = AMPPlayerController::StaticClass();
	DefaultPawnClass = ACharacterBase::StaticClass();
}
