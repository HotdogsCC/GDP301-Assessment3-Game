// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBase.generated.h"

class ARotatingPlatform;

UCLASS()
class GDP301GAME_API ABlockBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnCollisionWithPlatform(ARotatingPlatform* Platform);
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Mesh;

private:
	UFUNCTION()
	void OnMeshCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	
	UFUNCTION()
	void OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void TickFalling(float DeltaTime);
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	float FallSpeed = 100.0f;
	
	UPROPERTY()
	bool bIsFalling = true;
};
