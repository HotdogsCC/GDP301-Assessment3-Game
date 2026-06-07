// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBase.h"

#include "BlockSlime.h"
#include "RotatingPlatform.h"
#include "StackemsGameMode.h"
#include "Kismet/GameplayStatics.h"

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
	
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);
	if (!GameModeBase)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find game mode base in block slime"));
		return;
	}
	
	StackemsGameMode = Cast<AStackemsGameMode>(GameModeBase);
	if (!StackemsGameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast tp stackems game mode base in block slime"));
		return;
	}
}

void ABlockBase::OnCollisionWithPlatform(ARotatingPlatform* Platform)
{
	bIsFalling = false;
}

void ABlockBase::OnCollisionWithBlockSlime(ABlockSlime* BlockSlime)
{
	bIsFalling = false;
	
	//is this other block the same colour as me?
	if (BlockColour == BlockSlime->GetBlockColour())
	{
		//award two points
		GetStackemsGameMode()->AddPoint();
		GetStackemsGameMode()->AddPoint();
		
		//kill us both
		BlockSlime->MakeAttachedBlocksFall();
		BlockSlime->Destroy();
		
		MakeAttachedBlocksFall();
		Destroy();
	}
}

AStackemsGameMode* ABlockBase::GetStackemsGameMode() const
{
	return StackemsGameMode;
}

bool ABlockBase::GetIsFalling() const
{
	return bIsFalling;
}

EBlockColour ABlockBase::GetBlockColour() const
{
	return BlockColour;
}

void ABlockBase::StopFalling()
{
	bIsFalling = false;
}

void ABlockBase::UnattachAndStartFalling()
{
	AttachToActor(nullptr, FAttachmentTransformRules::KeepWorldTransform);
	
	bIsFalling = true;
}

void ABlockBase::MakeAttachedBlocksFall()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (auto AttachedActor : AttachedActors)
	{
		if (!AttachedActor) continue;
		
		ABlockBase* BlockBase = Cast<ABlockBase>(AttachedActor);
		if (!BlockBase) continue;
		
		BlockBase->UnattachAndStartFalling();
	}
}

void ABlockBase::SetFallSpeed(float InSpeed)
{
	FallSpeed = InSpeed;
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

