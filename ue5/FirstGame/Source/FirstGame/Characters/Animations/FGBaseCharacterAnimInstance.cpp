// Fill out your copyright notice in the Description page of Project Settings.


#include "FGBaseCharacterAnimInstance.h"
#include "../FGBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFGBaseCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	checkf(TryGetPawnOwner()->IsA<AFGBaseCharacter>(), TEXT("UFGBaseAnimInstance::NativeBeginPlay() UFGBaseAnimInstance can be used only with AFGBaseCharacter"));

	CachedBaseCharacter = StaticCast<AFGBaseCharacter*>(TryGetPawnOwner()); // Статический каст так как не подразумевается использование других типов
}

void UFGBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!CachedBaseCharacter.IsValid())
	{
		return;
	}

	UCharacterMovementComponent* CharacterMovement = CachedBaseCharacter->GetCharacterMovement();
	Speed = CharacterMovement->Velocity.Size();
	bIsFalling = CharacterMovement->IsFalling();
	bIsCrouching = CharacterMovement->IsCrouching();
}