// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUIWidget.h"

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
