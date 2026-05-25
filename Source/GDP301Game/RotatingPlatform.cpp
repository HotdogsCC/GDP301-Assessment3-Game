// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPlatform.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ARotatingPlatform::ARotatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get the player controller"));
		return;
	}
	
	FVector Tilt;
	FVector RotationRate;
	FVector Gravity;
	FVector Acceleration;
	PlayerController->GetInputMotionState(Tilt, RotationRate, Gravity, Acceleration);
	
	
	
	UE_LOG(LogTemp, Warning, TEXT("Tilt | X:%f, Y:%f, Z:%f"), Tilt.X, Tilt.Y, Tilt.Z);
	UE_LOG(LogTemp, Warning, TEXT("RotationRate | X:%f, Y:%f, Z:%f"), RotationRate.X, RotationRate.Y, RotationRate.Z);
	UE_LOG(LogTemp, Warning, TEXT("Gravity | X:%f, Y:%f, Z:%f"), Gravity.X, Gravity.Y, Gravity.Z);
	UE_LOG(LogTemp, Warning, TEXT("Acceleration | X:%f, Y:%f, Z:%f"), Acceleration.X, Acceleration.Y, Acceleration.Z);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, 
			FString::Printf(TEXT("Tilt | X:%f, Y:%f, Z:%f"), Tilt.X, Tilt.Y, Tilt.Z));
		
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, 
			FString::Printf(TEXT("RotationRate | X:%f, Y:%f, Z:%f"), RotationRate.X, RotationRate.Y, RotationRate.Z));
		
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, 
			FString::Printf(TEXT("Gravity | X:%f, Y:%f, Z:%f"), Gravity.X, Gravity.Y, Gravity.Z));
		
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, 
			FString::Printf(TEXT("Acceleration | X:%f, Y:%f, Z:%f"), Acceleration.X, Acceleration.Y, Acceleration.Z));
		
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, 
			FString::Printf(TEXT("-------------")));
	}
}

