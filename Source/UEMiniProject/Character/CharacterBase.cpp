// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SM_Mesh"));

	SetRootComponent(SkeletalMeshComponent);
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/ControlRig/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple"));
	if (SkeletalMesh.Succeeded())
	{
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh.Object);
	}
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}