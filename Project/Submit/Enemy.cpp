// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Bullet.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
    FTimerManager& timerManager = GetWorld()->GetTimerManager();
	FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle,this,&AEnemy::Fire,/*3.f*/FMath::FRandRange(1,3),false);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::Fire()
{
    if (ProjectileClass)
    {
        FVector CameraLocation;
        FRotator CameraRotation;
        GetActorEyesViewPoint(CameraLocation, CameraRotation);

        FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
        FRotator MuzzleRotation = CameraRotation;
        MuzzleRotation.Pitch += FMath::FRandRange(0,30);
        MuzzleRotation.Yaw += FMath::FRandRange(-60,60);
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;
            ABullet* Projectile = World->SpawnActor<ABullet>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (ProjectileClass)
            {
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);
            }
        }
    }
    FTimerManager& timerManager = GetWorld()->GetTimerManager();
	FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle,this,&AEnemy::Fire,FMath::FRandRange(0.5,1.5),false);
}
