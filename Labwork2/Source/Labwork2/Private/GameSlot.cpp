// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSlot.h"
#include "TBPlayerController.h"

// Sets default values
AGameSlot::AGameSlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
	Box->SetBoxExtent(FVector(50, 50, 2));
	Box->SetCollisionResponseToAllChannels(ECR_Block);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultSlotMesh(TEXT("/Engine/BasicShapes/Plane"));

	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	Plane->SetupAttachment(RootComponent);
	Plane->SetStaticMesh(DefaultSlotMesh.Object);

	SetState(GS_Default);
}



// Called when the game starts or when spawned
void AGameSlot::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddUniqueDynamic(this,&AGameSlot::OnGridClicked);	
}

// Called every frame
void AGameSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGameSlot::OnGridClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	if (auto PlayerController = GWorld->GetFirstPlayerController<ATBPlayerController>())
	{
		PlayerController->OnActorClicked(this,ButtonPressed);
	}
}


void AGameSlot::SpawnUnitHere(TSubclassOf<AUnitBase>& UnitClass)
{
	FVector Location = GetActorLocation();
	AUnitBase* NewUnit = Cast<AUnitBase>(GWorld->SpawnActor(UnitClass, &Location));
	if (NewUnit)
	{
		NewUnit->AssignToSlot(this);
	}

}

void AGameSlot::SetState(EGridState NewState)
{
	GridState = NewState;
	DefaultSlotMaterial(TEXT("/Material'/Game/Materials/MAT_GridSlot.MAT_GridSlot'"));
	DefaultSlotMaterial_H (TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MAT_GridSlot_Highlighted.MAT_GridSlot_Highlighted'"));
	DefaultSlotMaterial_O (TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MAT_GridSlot_Offensive.MAT_GridSlot_Offensive'"));
	DefaultSlotMaterial_S (TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MAT_GridSlot_Supportive.MAT_GridSlot_Supportive'"));

	switch (NewState)
	{
	case GS_Default:
		Plane->SetMaterial(0, DefaultSlotMaterial.Object);
		break;
	case GS_Highlighted:
		Plane->SetMaterial(0, DefaultSlotMaterial_H.Object);
		break;
	case GS_Offensive:
		Plane->SetMaterial(0, DefaultSlotMaterial_O.Object);
		break;
	case GS_Supportive:
		Plane->SetMaterial(0, DefaultSlotMaterial_S.Object);
		break;
	}
}
