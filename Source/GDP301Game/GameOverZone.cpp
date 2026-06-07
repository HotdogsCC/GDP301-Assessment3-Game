// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverZone.h"

#include "BlockBase.h"
#include "StackemsGameMode.h"
#include "Kismet/GameplayStatics.h"

void AGameOverZone::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (ABlockBase* Block : OverlappingBlocks)
	{
		if (!Block->GetIsFalling())
		{
			AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);
			if (!GameModeBase)
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to find game mode base in block slime"));
				return;
			}
	
			AStackemsGameMode* StackemsGameMode = Cast<AStackemsGameMode>(GameModeBase);
			if (!StackemsGameMode)
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to cast tp stackems game mode base in block slime"));
				return;
			}
			
			StackemsGameMode->GameOver();
		}
	}
}

void AGameOverZone::BeginPlay()
{
	Super::BeginPlay();
	
	PrimaryActorTick.bCanEverTick = true;
	
	GetStaticMeshComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGameOverZone::OnOverlap);
	GetStaticMeshComponent()->OnComponentEndOverlap.AddDynamic(this, &AGameOverZone::OnOverlapEnd);
}

void AGameOverZone::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	
	//did this touch a block?
	if (ABlockBase* Block = Cast<ABlockBase>(OtherActor))
	{
		if (bIsVoid)
		{
			AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);
			if (!GameModeBase)
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to find game mode base in block slime"));
				return;
			}
	
			AStackemsGameMode* StackemsGameMode = Cast<AStackemsGameMode>(GameModeBase);
			if (!StackemsGameMode)
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to cast tp stackems game mode base in block slime"));
				return;
			}
			
			StackemsGameMode->GameOver();
		}
		
		//dont do anything if we are already tracking this block?
		if (OverlappingBlocks.Contains(Block)) return;
		
		//otherwise, add it to the list of blocks to watch
		OverlappingBlocks.Add(Block);
	}
}

void AGameOverZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;
	
	//did this touch a block?
	if (ABlockBase* Block = Cast<ABlockBase>(OtherActor))
	{
		//dont do anything if we aren't tracking this block
		if (!OverlappingBlocks.Contains(Block)) return;
		
		//otherwise, remove it 
		OverlappingBlocks.Remove(Block);
	}
}
