// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/CharacterBase.h"
#include "Character/MPPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh;
		ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContext;
		ConstructorHelpers::FObjectFinder<UInputAction> MoveAction; 

		FConstructorStatics():
			SkeletalMesh(TEXT("/Game/ControlRig/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple")),
			MappingContext(TEXT("/Game/Input/IMC_Character.IMC_Character")),
			MoveAction(TEXT("/Game/Input/IA_CharacterMove.IA_CharacterMove"))
		{
			check(SkeletalMesh.Succeeded());
			check(MappingContext.Succeeded());
			check(MoveAction.Succeeded());
		}
	};

	static FConstructorStatics ConstructorStatics;
	
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SM_Mesh"));

	SetRootComponent(SkeletalMeshComponent);
	CameraComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetupAttachment(RootComponent);
	
	CapsuleComponent->SetCapsuleHalfHeight(85.0f);
	CapsuleComponent->SetRelativeLocation(FVector(0, 0, 85));
	CameraComponent->SetRelativeLocation(FVector(10, 0, 170));
	SkeletalMeshComponent->SetSkeletalMesh(ConstructorStatics.SkeletalMesh.Object);
	DefaultInputContext = ConstructorStatics.MappingContext.Object;
	MoveAction = ConstructorStatics.MoveAction.Object;

	MoveSpeed = 100.0f;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	AMPPlayerController* PlayerController = CastChecked<AMPPlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultInputContext, 0);
	}
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterBase::Move);
}

void ACharacterBase::Move(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>();
	FVector Position = GetActorLocation();
	Position += GetActorForwardVector() * (Axis.Y * MoveSpeed);
	Position += GetActorRightVector() * (Axis.X * MoveSpeed);
	SetActorLocation(Position);
}
