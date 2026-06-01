// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPlatform.h"

#include "MovementLine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARotatingPlatform::ARotatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARotatingPlatform::TickRotation(const float DeltaTime)
{
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
	
	FRotator ThisRotation = FRotator::ZeroRotator;
	
	float ThisRoll = Tilt.X;
	ThisRoll = FMath::Clamp(ThisRoll, -0.6f, 0.6f);
	
	//flip the sign if the phone is held the other way
	if (Tilt.Y < 0.5) ThisRoll *= -1.0f;
	
	//convert from radians to degrees
	ThisRoll = FMath::RadiansToDegrees(ThisRoll);
	
	ThisRotation.Roll = ThisRoll;
	
	SetActorRotation(ThisRotation);
	
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

void ARotatingPlatform::TickMovement(const float DeltaTime)
{
	if (!MovementLine)
	{
		UE_LOG(LogTemp, Warning, TEXT("No movement line set in rotating platform"));
		return;
	}
	
	FVector Location = GetActorLocation();
	Location.Y += GetActorRotation().Roll * DeltaTime * Speed;
	Location = MovementLine->GetClampedLocation(Location);
	SetActorLocation(Location);
	
}

// Called every frame
void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickRotation(DeltaTime);
	TickMovement(DeltaTime);
}

