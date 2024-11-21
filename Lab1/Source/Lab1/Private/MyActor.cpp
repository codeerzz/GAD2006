// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor() :
	Health(100)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	Count = 1;
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Count++; 
	
	
	// Yarina Not Can degiskeni eklencek ve blueprintler enginede acilip variablelara eriselecek.




	/*
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Cyan,FString::Printf(TEXT("Count: %d"), Count));
	*/
}

void AMyActor::DamagePlayer(float Damage)
{
	Health -= Damage;

	if(Health < 0){
	UE_LOG(LogTemp, Display, TEXT("gg easy peasy "));
        }
	else
	{
		UE_LOG(LogTemp, Display, TEXT("remaing health %f"),Health);
	}
}

