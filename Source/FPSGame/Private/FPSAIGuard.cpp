// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::onNoiseHeard);
}

//seen in line of sight
void AFPSAIGuard::OnPawnSeen(APawn * SeenPawn)
{
	if (!SeenPawn)
	{
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Seen Player"));
	//DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
}

void AFPSAIGuard::onNoiseHeard(APawn * Instigator, const FVector & Location, float Volume)
{
	if (!Instigator)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

