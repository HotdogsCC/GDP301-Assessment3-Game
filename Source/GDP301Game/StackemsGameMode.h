// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StackemsGameMode.generated.h"

class UGameUIWidget;
/**
 * 
 */
UCLASS()
class GDP301GAME_API AStackemsGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void PlaySlimeSound();
	
	void AddPoint();
	
	void GameOver();
	
	UGameUIWidget* GetGameUIWidget() const;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	void UpdateScore();
	
	UPROPERTY(EditDefaultsOnly, Category="UI", meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameUIWidget> GameUIWidgetBlueprint;
	
	UPROPERTY()
	UGameUIWidget* GameUIWidget;
	
	UPROPERTY(EditDefaultsOnly, Category="Sounds", meta=(AllowPrivateAccess=true))
	USoundCue* SlimeSoundCue;
	
	UPROPERTY()
	int32 Points = 0;
};
