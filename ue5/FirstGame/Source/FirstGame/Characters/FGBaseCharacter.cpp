// Fill out your copyright notice in the Description page of Project Settings.


#include "FGBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
