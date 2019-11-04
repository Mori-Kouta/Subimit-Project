// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"


ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Bullet"));
	CollisionComponent -> InitSphereRadius(40.0f);
	

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent -> SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent -> InitialSpeed = 45.0f;
	ProjectileMovementComponent -> MaxSpeed = 450.0f;
	ProjectileMovementComponent -> bRotationFollowsVelocity = true;
	ProjectileMovementComponent -> bShouldBounce = true;
	ProjectileMovementComponent -> ProjectileGravityScale = 0;

	InitialLifeSpan = 15.0f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerCharacter* Target = Cast<APlayerCharacter>(GetWorld() -> GetFirstPlayerController()->GetPawn());
	ProjectileMovementComponent -> HomingTargetComponent = Target -> GetRootComponent();
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle,this,&ABullet::Homing,FMath::FRandRange(3,5),false);
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void ABullet::Homing()
{
	ProjectileMovementComponent -> bIsHomingProjectile = true;
	ProjectileMovementComponent -> HomingAccelerationMagnitude = 400.0f;
}