// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "CharacterBase.generated.h"

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

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> CameraComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY()
	TObjectPtr<class UInputMappingContext> DefaultInputContext;
	UPROPERTY()
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Status")
	float MoveSpeed;
};
