// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockSpawner.h"

#include "BlockSlime.h"
#include "MovementLine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABlockSpawner::ABlockSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlockSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//increase how long it has been since the last spawn
	ElapsedTimeSinceLastSpawn += DeltaTime;
	
	//has it been long enough
	if (ElapsedTimeSinceLastSpawn >= TimeBetweenSpawns)
	{
		ElapsedTimeSinceLastSpawn = 0.0f;
		
		if (!MovementLine)
		{
			UE_LOG(LogTemp, Warning, TEXT("no movement line set in block spawner"));
			return;
		}
		
		const FVector LeftLocation = MovementLine->GetClampLeftLocation();
		const FVector RightLocation = MovementLine->GetClampRightLocation();
		
		FVector SpawnLocation;
		SpawnLocation.X = FMath::RandRange(LeftLocation.X, RightLocation.X);
		SpawnLocation.Y = FMath::RandRange(LeftLocation.Y, RightLocation.Y);
		SpawnLocation.Z = GetActorLocation().Z;
		
		GetWorld()->SpawnActor(SlimeBlockBlueprint, &SpawnLocation);
	}

}

