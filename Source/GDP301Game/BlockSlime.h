// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockBase.h"
#include "BlockSlime.generated.h"

/**
 * 
 */
UCLASS()
class GDP301GAME_API ABlockSlime : public ABlockBase
{
	GENERATED_BODY()
	
protected:
	virtual void OnCollisionWithPlatform(ARotatingPlatform* Platform) override;
	
	virtual void OnCollisionWithBlockSlime(ABlockSlime* BlockSlime) override;
};
