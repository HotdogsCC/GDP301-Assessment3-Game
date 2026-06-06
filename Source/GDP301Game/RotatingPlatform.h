// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputAction.h"
#include "RotatingPlatform.generated.h"


class AMovementLine;

UCLASS()
class GDP301GAME_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingPlatform();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateRotation(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Speed", meta=(AllowPrivateAccess=true))
	float RotationSpeed = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="Speed", meta=(AllowPrivateAccess=true))
	float Speed = 100.0f;
	
	UPROPERTY(EditInstanceOnly, Category="Movement Line", meta=(AllowPrivateAccess=true))
	AMovementLine* MovementLine;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Mesh;

private:
	UFUNCTION()
	void TickRotation(const float DeltaTime);
	
	UFUNCTION()
	void TickMovement(const float DeltaTime);
	
	//the inputted roll value
	UPROPERTY()
	float RollInput = 0.0f;


};
