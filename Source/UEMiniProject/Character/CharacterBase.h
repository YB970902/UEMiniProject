// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "CharacterBase.generated.h"

DECLARE_DELEGATE_OneParam(FMoveSpeedDelegate, float);

UCLASS()
class UEMINIPROJECT_API ACharacterBase : public APawn
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, Category=Character)
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere, Category=Character)
	TObjectPtr<class UCameraComponent> CameraComponent;
	UPROPERTY(VisibleAnywhere, Category=Character)
	TObjectPtr<class USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category=Character)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY()
	TObjectPtr<class UInputMappingContext> DefaultInputContext;
	UPROPERTY()
	TObjectPtr<class UInputAction> MoveAction;

public:
	FMoveSpeedDelegate OnMoveSpeedChanged;
protected:

	UPROPERTY(EditAnywhere, Category="Status")
	float MoveSpeed;
};
