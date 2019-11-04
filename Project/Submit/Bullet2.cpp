
// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet2.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"

ABullet2::ABullet2()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Bullet"));
	CollisionComponent -> InitSphereRadius(40.0f);
	

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent -> SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent -> InitialSpeed = 500.0f;
	ProjectileMovementComponent -> MaxSpeed = 500.0f;
	ProjectileMovementComponent -> bRotationFollowsVelocity = true;
	ProjectileMovementComponent -> bShouldBounce = true;
	ProjectileMovementComponent -> ProjectileGravityScale = 0;

	InitialLifeSpan = 10.0f;
}

void ABullet2::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerCharacter* Target = Cast<APlayerCharacter>(GetWorld() -> GetFirstPlayerController()->GetPawn());
}

void ABullet2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet2::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}
