// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverZone.h"

#include "BlockBase.h"
#include "GameUIWidget.h"
#include "StackemsGameMode.h"
#include "Kismet/GameplayStatics.h"

bool GetActorPosInScreenSpace(const APlayerController* Player, const AActor* Actor, FVector2D& OutScreenPos)
{
	FVector WorldPosition = Actor->GetActorLocation();
	ULocalPlayer* const LP = Player ? Player->GetLocalPlayer() : nullptr;
	if (LP && LP->ViewportClient)
	{
		// get the projection data
		FSceneViewProjectionData ProjectionData;
		//if (LP->GetProjectionData(LP->ViewportClient->Viewport, eSSP_FULL, /*out*/ ProjectionData))
		if (LP->GetProjectionData(LP->ViewportClient->Viewport, ProjectionData))
		{
			FMatrix const ViewProjectionMatrix = ProjectionData.ComputeViewProjectionMatrix();
			const bool bResult = FSceneView::ProjectWorldToScreen(WorldPosition, ProjectionData.GetConstrainedViewRect(), ViewProjectionMatrix, OutScreenPos);

			FPlane Result = ViewProjectionMatrix.TransformFVector4(FVector4(WorldPosition, 1.f));
			if (Result.W > 0.0f)
			{
				// the result of this will be x and y coords in -1..1 projection space
				const float RHW = 1.0f / Result.W;
				FPlane PosInScreenSpace = FPlane(Result.X * RHW, Result.Y * RHW, Result.Z * RHW, Result.W);

				OutScreenPos = FVector2D{ PosInScreenSpace.X, PosInScreenSpace.Y };
				return true;
			}
		}
	}
	OutScreenPos = FVector2D::ZeroVector;
	return false;
}

void AGameOverZone::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	bool bHasBadBlocks = false;

	for (ABlockBase* Block : OverlappingBlocks)
	{
		if (!Block->GetIsFalling())
		{
			bHasBadBlocks = true;
			MercyTime += DeltaSeconds;
			
			if (MercyTime > 1.0f)
			{
				StackemsGameMode->GameOver();
			}
			
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			
			FVector2D Location;
			GetActorPosInScreenSpace(PlayerController, Block, Location);
			
			StackemsGameMode->GetGameUIWidget()->ShowCircle(Location);
			StackemsGameMode->GetGameUIWidget()->ShowOverlappingWarning(MercyTime);
			
			//todo remove
			return;
			
			
			
			StackemsGameMode->GameOver();
		}
	}
	
	if (!bHasBadBlocks)
	{
		StackemsGameMode->GetGameUIWidget()->HideCircle();
		StackemsGameMode->GetGameUIWidget()->HideOverlappingWarning();
		
		MercyTime = 0.0f;
	}
}

void AGameOverZone::BeginPlay()
{
	Super::BeginPlay();
	
	PrimaryActorTick.bCanEverTick = true;
	
	GetStaticMeshComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGameOverZone::OnOverlap);
	GetStaticMeshComponent()->OnComponentEndOverlap.AddDynamic(this, &AGameOverZone::OnOverlapEnd);
	
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);
	if (!GameModeBase)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find game mode base in block slime"));
		return;
	}
	
	StackemsGameMode = Cast<AStackemsGameMode>(GameModeBase);
	if (!StackemsGameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast tp stackems game mode base in block slime"));
		return;
	}
}

void AGameOverZone::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	
	//did this touch a block?
	if (ABlockBase* Block = Cast<ABlockBase>(OtherActor))
	{
		if (bIsVoid) StackemsGameMode->GameOver();
		
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

