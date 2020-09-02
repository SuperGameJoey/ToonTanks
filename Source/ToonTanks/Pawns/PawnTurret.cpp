// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition()
{
    // If Player == null || is Dead, THEN Bail!
    if (PlayerPawn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("PawnTurrent's PlayerPawn is null"));
        return;
    }

    // If Player IS in range, THEN Fire
    if(ReturnDistanceToPlayer() < FireRange)
    {
        UE_LOG(LogTemp, Warning, TEXT("Turrent Fire!"));
    }
}

float APawnTurret::ReturnDistanceToPlayer()
{
    // If Player == null || is Dead, THEN Bail!
    if (PlayerPawn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("PawnTurrent's PlayerPawn is null"));
        return 0.0f;
    }
   
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}