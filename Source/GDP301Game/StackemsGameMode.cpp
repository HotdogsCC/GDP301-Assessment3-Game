// Fill out your copyright notice in the Description page of Project Settings.


#include "StackemsGameMode.h"

#include "BlockBase.h"
#include "BlockSpawner.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameUIWidget.h"
#include "RotatingPlatform.h"
#include "Sound/SoundCue.h"

void AStackemsGameMode::PlaySlimeSound()
{
	if (!SlimeSoundCue)
	{
		UE_LOG(LogTemp, Warning, TEXT("No slime sound cue set in game mode"));
		return;
	}
	
	UGameplayStatics::PlaySound2D(this, SlimeSoundCue);
}

void AStackemsGameMode::AddPoint()
{
	Points++;
	
	UpdateScore();
}

void AStackemsGameMode::GameOver()
{
	if (GameUIWidget) GameUIWidget->GameOver();
	
	TArray<AActor*> Blocks;
	UGameplayStatics::GetAllActorsOfClass(this, ABlockBase::StaticClass(), Blocks);

	for (auto Block : Blocks)
	{
		if (!Block) continue;
		
		Cast<ABlockBase>(Block)->StopFalling();
	}
	
	AActor* RotatingPlatformActor = UGameplayStatics::GetActorOfClass(this, ARotatingPlatform::StaticClass());
	if (!RotatingPlatformActor) return;
	Cast<ARotatingPlatform>(RotatingPlatformActor)->SetActorTickEnabled(false);
	
	AActor* BlockSpawnerActor = UGameplayStatics::GetActorOfClass(this, ABlockSpawner::StaticClass());
	if (!BlockSpawnerActor) return;
	Cast<ABlockSpawner>(BlockSpawnerActor)->SetActorTickEnabled(false);
}

void AStackemsGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (!GameUIWidgetBlueprint)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Ui Widget Blueprint not set in stackems game mode"));
		return;
	}
	
	GameUIWidget = CreateWidget<UGameUIWidget>(GetWorld(), GameUIWidgetBlueprint);
	
	if (!GameUIWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create game ui widget in stakcems game mode"));
		return;
	}
	
	GameUIWidget->AddToViewport();
	UpdateScore();
}

void AStackemsGameMode::UpdateScore()
{
	if (!GameUIWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create game ui widget in stakcems game mode"));
		return;
	}
	
	GameUIWidget->UpdateScore(Points);
}
