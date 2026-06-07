// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBase.h"

#include "BlockSlime.h"
#include "RotatingPlatform.h"

// Sets default values
ABlockBase::ABlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void ABlockBase::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABlockBase::OnMeshOverlap);
	UE_LOG(LogTemp, Warning, TEXT("bound"));
	
}

void ABlockBase::OnCollisionWithPlatform(ARotatingPlatform* Platform)
{
	bIsFalling = false;
}

void ABlockBase::OnCollisionWithBlockSlime(ABlockSlime* BlockSlime)
{
	bIsFalling = false;
}

bool ABlockBase::GetIsFalling() const
{
	return bIsFalling;
}

// Called every frame
void ABlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickFalling(DeltaTime);
}

void ABlockBase::OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//was it a platform?
	if (!OtherActor) return;
	
	if (ARotatingPlatform* Platform = Cast<ARotatingPlatform>(OtherActor)) OnCollisionWithPlatform(Platform);
	else if (ABlockSlime* BlockSlime = Cast<ABlockSlime>(OtherActor)) OnCollisionWithBlockSlime(BlockSlime);
}

void ABlockBase::TickFalling(float DeltaTime)
{
	if (!bIsFalling) return;
	
	FVector Location = GetActorLocation();
	Location.Z -= FallSpeed * DeltaTime;
	SetActorLocation(Location);
}

