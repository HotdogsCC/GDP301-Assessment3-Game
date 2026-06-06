// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockSlime.h"

#include "RotatingPlatform.h"

void ABlockSlime::OnCollisionWithPlatform(ARotatingPlatform* Platform)
{
	Super::OnCollisionWithPlatform(Platform);
	
	UE_LOG(LogTemp, Warning, TEXT("slime block hit platform"));
	
	AttachToActor(Platform, FAttachmentTransformRules::KeepWorldTransform);
}
