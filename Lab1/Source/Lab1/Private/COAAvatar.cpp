// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"




ACOAAvatar::ACOAAvatar():
	RunningSpeed(600.0f),
	MaxStamina(100.0f),
	Stamina(0.0f),
	StaminaGainRate(20.0f),
	StaminaDrainRate(40.0f)

{
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mSpringArm->TargetArmLength = 300.0f;
	mSpringArm->SetupAttachment(RootComponent);

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	mCamera->SetupAttachment(mSpringArm, USpringArmComponent::SocketName);
}

void ACOAAvatar::BeginPlay()
{
	Super::BeginPlay();
	mCamera->bUsePawnControlRotation = false;
	mSpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	bStaminaDrained = false;
}



void ACOAAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* I followed the exact requirements on the class material, but there's one thing I don't understand:
	 * - While walking, we lose stamina. If we stop walking, we regain stamina.
	 * - If our stamina runs out, we can't run but we can still walk.
	 * - In that case, instead of stopping, running, and stopping again, I could just walk forever.
	 *
	 */
	/*bool bWalking = GetCharacterMovement()->MovementMode == EMovementMode::MOVE_None;
	UE_LOG(LogTemp, Display, TEXT(" walking %d"), bWalking);   This is not working; when I start walking, it always stays at 1. I thought it was checking whether I was moving or not*/
	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking) {
		FVector Velocity = GetCharacterMovement()->Velocity;
		if (Velocity.IsNearlyZero()) {

			Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
			UE_LOG(LogTemp, Display, TEXT("stamina reloaded to s %f"), Stamina);
		}
		else{

			Stamina = FMath::Max(0, Stamina - StaminaDrainRate * DeltaTime);
			UE_LOG(LogTemp, Display, TEXT("stamina decreased to s %f"), Stamina);
		}

		if(Stamina == 0.0f) {

			bStaminaDrained = true;
		}
		if (Stamina == 100.0f) {

			bStaminaDrained = false;
	}
	}
	UpdateMovementParams();
	UE_LOG(LogTemp, Display, TEXT("bStaminaDrained %d"), bStaminaDrained);
}


// Called to bind functionality to input
void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	
	PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAvatar::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);

	//PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);


	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACOAAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACOAAvatar::RunReleased);


}

void ACOAAvatar::RunPressed() 
{
	bRunning = true;
}


void ACOAAvatar::RunReleased() 
{
	bRunning = false;	
}

void ACOAAvatar::MoveForward(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection, Amount);
}

void ACOAAvatar::MoveRight(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(RightDirection, Amount);
}



void ACOAAvatar::UpdateMovementParams()
{
	float CurrentSpeed = (bRunning ? (bStaminaDrained ? WalkSpeed : RunningSpeed) : WalkSpeed);
	GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
}