// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUIWidget.generated.h"

class UProgressBar;
class UCanvasPanel;
class UImage;
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
	
	UFUNCTION()
	void ShowCircle(const FVector2D& Location);
	
	UFUNCTION()
	void HideCircle();
	
	UFUNCTION()
	void ShowOverlappingWarning(float Progress);
	
	UFUNCTION()
	void HideOverlappingWarning();
	
private:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreText;
	
	UPROPERTY(meta=(BindWidget))
	UImage* Circle;
	
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* OverlappingCanvas;
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* WarningProgress;
	
	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher;
	
};
