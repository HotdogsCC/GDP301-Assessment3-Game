// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementLine.h"

// Sets default values
AMovementLine::AMovementLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);
	
	ClampLeft = CreateDefaultSubobject<USceneComponent>("Clamp Left");
	ClampLeft->SetupAttachment(Mesh);
	
	ClampRight = CreateDefaultSubobject<USceneComponent>("Clamp Right");
	ClampRight->SetupAttachment(Mesh);

}

FVector AMovementLine::GetClampLeftLocation() const
{
	return ClampLeft->GetComponentLocation();
}

FVector AMovementLine::GetClampRightLocation() const
{
	return ClampRight->GetComponentLocation();
}

bool AMovementLine::IsClamped(const FVector InLocation) const
{
	return InLocation.Y >= GetClampLeftLocation().Y && InLocation.Y <= GetClampRightLocation().Y;
}

FVector AMovementLine::GetClampedLocation(const FVector InLocation) const
{
	//if it is already clamped, return where it is
	if (IsClamped(InLocation)) return InLocation;
	
	FVector ClampedLocation = InLocation;
	
	//otherwise clamp it and return in
	ClampedLocation.Y = FMath::Clamp(InLocation.Y, GetClampLeftLocation().Y, GetClampRightLocation().Y);
	
	return ClampedLocation;
}

// Called when the game starts or when spawned
void AMovementLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovementLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

