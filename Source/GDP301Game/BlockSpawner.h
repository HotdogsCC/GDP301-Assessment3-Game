// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockSpawner.generated.h"

class AMovementLine;
class ABlockSlime;

UCLASS()
class GDP301GAME_API ABlockSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockSpawner();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Speed", meta=(AllowPrivateAccess=true))
	float TimeBetweenSpawns = 3.0f;
	
	UPROPERTY()
	float ElapsedTimeSinceLastSpawn = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="Blueprints", meta=(AllowPrivateAccess=true))
	TSubclassOf<ABlockSlime> SlimeBlockBlueprint;
	
	UPROPERTY(EditInstanceOnly, Category="Scene References", meta=(AllowPrivateAccess=true))
	AMovementLine* MovementLine;
	

};
