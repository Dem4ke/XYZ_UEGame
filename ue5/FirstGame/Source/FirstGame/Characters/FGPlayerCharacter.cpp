// Fill out your copyright notice in the Description page of Project Settings.


#include "FGPlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AFGPlayerCharacter::AFGPlayerCharacter()
{
	// Описание начальных значений объектов данного класса для задания грамотной работы камеры и движений персонажа
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = 1;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
}

void AFGPlayerCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotator(0.f, GetControlRotation().Yaw, 0.f);
		FVector ForwardVector = YawRotator.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardVector, Value);
	}
}

void AFGPlayerCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotator(0.f, GetControlRotation().Yaw, 0.f);
		FVector RightVector = YawRotator.RotateVector(FVector::RightVector);
		AddMovementInput(RightVector, Value);
	}
}

void AFGPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AFGPlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AFGPlayerCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFGPlayerCharacter::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFGPlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaleHalfHeightAdjuts)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaleHalfHeightAdjuts);
	SpringArmComponent->TargetOffset += FVector(0.f, 0.f, HalfHeightAdjust);
}

void AFGPlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaleHalfHeightAdjuts)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaleHalfHeightAdjuts);
	SpringArmComponent->TargetOffset -= FVector(0.f, 0.f, HalfHeightAdjust);
}

bool AFGPlayerCharacter::CanJumpInternal_Implementation() const
{
	return bIsCrouched || Super::CanJumpInternal_Implementation();
}

void AFGPlayerCharacter::OnJumped_Implementation()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
}