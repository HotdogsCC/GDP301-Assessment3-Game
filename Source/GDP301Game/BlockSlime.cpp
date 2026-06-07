// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockSlime.h"

#include "RotatingPlatform.h"
#include "StackemsGameMode.h"
#include "Kismet/GameplayStatics.h"

void ABlockSlime::OnCollisionWithPlatform(ARotatingPlatform* Platform)
{
	//ignore if this is not falling (already attached)
	if (!GetIsFalling()) return;
	
	Super::OnCollisionWithPlatform(Platform);
	
	AttachToActor(Platform, FAttachmentTransformRules::KeepWorldTransform);
	
	GetStackemsGameMode()->PlaySlimeSound();
	GetStackemsGameMode()->AddPoint();
}

void ABlockSlime::OnCollisionWithBlockSlime(ABlockSlime* BlockSlime)
{
	//ignore if this is not falling (already attached)
	if (!GetIsFalling()) return;
	
	Super::OnCollisionWithBlockSlime(BlockSlime);
	
	AttachToActor(BlockSlime, FAttachmentTransformRules::KeepWorldTransform);
	
	GetStackemsGameMode()->PlaySlimeSound();
	GetStackemsGameMode()->AddPoint();
}
