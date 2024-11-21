// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "COACharacter.generated.h"

UCLASS()
class LAB1_API ACOACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACOACharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lab1_test")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Lab1_test")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere,Category = "Lab1_test")
	float HealingRate;
	
	UPROPERTY(EditAnywhere,Category = "Lab1_test")
	float WalkSpeed;
	
	UPROPERTY(VisibleAnywhere, Category = "Lab1_test")
	bool bDead;


};
