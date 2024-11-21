// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COACharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "COAAvatar.generated.h"

/**
 * 
 */
UCLASS()
class LAB1_API ACOAAvatar : public ACOACharacter
{
	GENERATED_BODY()

public:
	ACOAAvatar();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lab1_test")
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lab1_test")
	USpringArmComponent* mSpringArm;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lab1_test")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lab1_test")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lab1_test")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Lab1_test")
	float StaminaGainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lab1_test")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Lab1_test")
	bool bStaminaDrained;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lab1_test")
	bool bRunning;




	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void RunPressed() ;
	void RunReleased() ;
	void UpdateMovementParams();
	
};
