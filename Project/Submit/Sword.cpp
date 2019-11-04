// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Bullet.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

ASword::ASword()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("/Game/CloseCombat/Weapon/Swords/SwordOfDarkness/Meshes/SM_SwordOfDarkness"));
	if(StaticMeshAsset.Succeeded())
	{
		SwordAsset = StaticMeshAsset.Object;
		mStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
		if(mStaticMeshComponent)
		{
			RootComponent = mStaticMeshComponent;
			mStaticMeshComponent -> SetStaticMesh(SwordAsset);
		}
	}
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SwordBox"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Sword"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	CollisionComponent->InitCapsuleSize(10.f, 80.0f);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASword::OnCompHit);
}

void ASword::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASword::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld() -> GetFirstPlayerController()->GetPawn());
	OtherActor->Destroy();
	if((OtherActor != this) && (OtherActor != NULL) && (OtherComp != NULL) && (Player->AttackAnimPlay == true))
	{
		Player->Score += 100;
	}
}