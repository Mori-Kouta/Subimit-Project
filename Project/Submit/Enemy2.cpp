// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy2.h"
#include "Bullet2.h"

// Sets default values
AEnemy2::AEnemy2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemy2::BeginPlay()
{
	Super::BeginPlay();
    FTimerManager& timerManager = GetWorld()->GetTimerManager();
	FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle,this,&AEnemy2::Fire,/*3.f*/FMath::FRandRange(1,3),false);
}

// Called every frame
void AEnemy2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy2::Fire()
{
    if (ProjectileClass)
    {
        FVector CameraLocation;
        FRotator CameraRotation;
        GetActorEyesViewPoint(CameraLocation, CameraRotation);

        FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
        FRotator MuzzleRotation = CameraRotation;
        MuzzleRotation.Yaw += FMath::FRandRange(-20,20);
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;
            ABullet2* Projectile = World->SpawnActor<ABullet2>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (ProjectileClass)
            {
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);
            }
        }
    }
    FTimerManager& timerManager = GetWorld()->GetTimerManager();
	FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle,this,&AEnemy2::Fire,FMath::FRandRange(1.0,2.0),false);
}
