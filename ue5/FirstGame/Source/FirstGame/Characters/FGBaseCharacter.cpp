// Fill out your copyright notice in the Description page of Project Settings.


#include "FGBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void AFGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanSprint() && bIsSprintRequested && !bIsSprinting) 
	{
		bIsSprinting = true;
		DefaultMaxMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
	else if (!bIsSprintRequested && bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = DefaultMaxMovementSpeed;
	}
}

void AFGBaseCharacter::ChangeCrouchState()
{
	if (GetCharacterMovement()->IsCrouching())
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void AFGBaseCharacter::StartSprint()
{
	bIsSprintRequested = true;
}

void AFGBaseCharacter::StopSprint()
{
	bIsSprintRequested = false;
}

bool AFGBaseCharacter::IsSprinting() const
{
	return bIsSprinting;
}

bool AFGBaseCharacter::CanSprint()
{
	return true;
}
