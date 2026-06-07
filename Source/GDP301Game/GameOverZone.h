// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GameOverZone.generated.h"

class ABlockBase;
/**
 * 
 */
UCLASS()
class GDP301GAME_API AGameOverZone : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY()
	TArray<ABlockBase*> OverlappingBlocks;
	
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess=true))
	bool bIsVoid = false;
};
