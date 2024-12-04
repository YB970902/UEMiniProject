// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MPAnimInstance.h"
#include "Character/CharacterBase.h"

void UMPAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacterBase>(GetOwningActor());
	
	if (Owner)
	{
		Owner->OnMoveSpeedChanged.BindUObject(this, &UMPAnimInstance::MoveSpeedChanged);
	}
}

void UMPAnimInstance::MoveSpeedChanged(float MoveSpeed)
{
	CurrentMoveSpeed = MoveSpeed;
}
