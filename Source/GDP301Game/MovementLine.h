// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovementLine.generated.h"

UCLASS()
class GDP301GAME_API AMovementLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovementLine();
	
	UFUNCTION(BlueprintCallable)
	FVector GetClampLeftLocation() const;
	
	UFUNCTION(BlueprintCallable)
	FVector GetClampRightLocation() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsClamped(const FVector InLocation) const;
	
	UFUNCTION(BlueprintCallable)
	FVector GetClampedLocation(const FVector InLocation) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	USceneComponent* ClampLeft;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	USceneComponent* ClampRight;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
