// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBase.generated.h"

class AStackemsGameMode;
class ABlockSlime;
class ARotatingPlatform;

UENUM(Blueprintable)
enum class EBlockColour : uint8
{
	Red,
	Yellow,
	Green,
	Blue
};

UCLASS()
class GDP301GAME_API ABlockBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	bool GetIsFalling() const;
	
	UFUNCTION()
	EBlockColour GetBlockColour() const;
	
	UFUNCTION()
	void StopFalling();
	
	UFUNCTION()
	void UnattachAndStartFalling();
	
	UFUNCTION()
	void MakeAttachedBlocksFall();
	
	UFUNCTION()
	void SetFallSpeed(float InSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnCollisionWithPlatform(ARotatingPlatform* Platform);
	
	virtual void OnCollisionWithBlockSlime(ABlockSlime* BlockSlime);
	
	AStackemsGameMode* GetStackemsGameMode() const;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Mesh;

private:
	UFUNCTION()
	void OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void TickFalling(float DeltaTime);
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	float FallSpeed = 100.0f;
	
	UPROPERTY()
	bool bIsFalling = true;
	
	UPROPERTY(EditDefaultsOnly, Category="Colour", meta=(AllowPrivateAccess=true));
	EBlockColour BlockColour = EBlockColour::Red;
	
	UPROPERTY()
	AStackemsGameMode* StackemsGameMode;
};
