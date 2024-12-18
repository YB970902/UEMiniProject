// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/CharacterBase.h"
#include "Character/MPPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh;
		ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContext;
		ConstructorHelpers::FObjectFinder<UInputAction> MoveAction;
		ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstance;

		FConstructorStatics():
			SkeletalMesh(TEXT("/Game/ControlRig/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple")),
			MappingContext(TEXT("/Game/Input/IMC_Character.IMC_Character")),
			MoveAction(TEXT("/Game/Input/IA_CharacterMove.IA_CharacterMove")),
			AnimInstance(TEXT("/Game/Animation/ABP_Character.ABP_Character_C"))
		{
			check(SkeletalMesh.Succeeded());
			check(MappingContext.Succeeded());
			check(MoveAction.Succeeded());
			check(AnimInstance.Succeeded());
		}
	};

	static FConstructorStatics ConstructorStatics;
	
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAMERA_ARM"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SM_Mesh"));

	RootComponent = CapsuleComponent;
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	
	CapsuleComponent->SetCapsuleHalfHeight(85.0f);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 85.0f));
	CameraComponent->bUsePawnControlRotation = true;
	SkeletalMeshComponent->SetSkeletalMesh(ConstructorStatics.SkeletalMesh.Object);
	SkeletalMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -85.0f));
	SkeletalMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SkeletalMeshComponent->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
	SkeletalMeshComponent->SetAnimInstanceClass(ConstructorStatics.AnimInstance.Class);
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
	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();
	Forward.Z = 0;
	Right.Z = 0;
	Position += Forward * (Axis.Y * MoveSpeed);
	Position += Right * (Axis.X * MoveSpeed);
	SetActorLocation(Position);
	OnMoveSpeedChanged.Execute(MoveSpeed);
}
