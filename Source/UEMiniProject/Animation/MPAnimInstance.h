// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MPAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEMINIPROJECT_API UMPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION()
	void MoveSpeedChanged(float MoveSpeed);

protected:
	TObjectPtr<class ACharacterBase> Owner;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentMoveSpeed;
};
