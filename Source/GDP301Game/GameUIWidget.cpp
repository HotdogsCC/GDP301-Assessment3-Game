// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUIWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UGameUIWidget::UpdateScore(int32 Score)
{
	FString ScoreString = FString::FromInt(Score);
	ScoreString.Append(" Points");
	
	ScoreText->SetText(FText::FromString(ScoreString));
}

void UGameUIWidget::GameOver()
{
	WidgetSwitcher->SetActiveWidgetIndex(1);
	
	
}

void UGameUIWidget::ShowCircle(const FVector2D& Location)
{
	Circle->SetVisibility(ESlateVisibility::Visible);
	
	//convert from -1.0f <-> 1.0f to 0 <-> 1920
	FVector2D ScreenLocation;
	ScreenLocation.X = (Location.X + 1.0f) * 1920.0f * 0.5f;
	ScreenLocation.Y = ((Location.Y * -1.0f) + 1.0f) * 1080.0f * 0.5f;
	
	Cast<UCanvasPanelSlot>(Circle->Slot)->SetPosition(ScreenLocation);
}

void UGameUIWidget::HideCircle()
{
	Circle->SetVisibility(ESlateVisibility::Collapsed);
}

void UGameUIWidget::ShowOverlappingWarning(float Progress)
{
	OverlappingCanvas->SetVisibility(ESlateVisibility::Visible);
	
	WarningProgress->SetPercent(Progress);
}

void UGameUIWidget::HideOverlappingWarning()
{
	OverlappingCanvas->SetVisibility(ESlateVisibility::Collapsed);
}
