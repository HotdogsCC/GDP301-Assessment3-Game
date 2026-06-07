// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUIWidget.generated.h"

class UWidgetSwitcher;
class UTextBlock;
/**
 * 
 */
UCLASS()
class GDP301GAME_API UGameUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void UpdateScore(int32 Score);
	
	UFUNCTION()
	void GameOver();
	
private:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreText;
	
	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher;
	
};
