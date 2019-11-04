// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Sword.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(36.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName("PC");

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f,800.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraBoom->TargetArmLength = 400.0f; 	
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<UAnimSequence>AnimAsset(TEXT("/Game/CloseCombat/Character/UE4Mannequin/Animations/Swordsman/Avoid/A_SW_Avoid_Forward"));
	if (AnimAsset.Succeeded()) {
    	DodgeAnim = AnimAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence>AnimAsset1(TEXT("/Game/CloseCombat/Character/UE4Mannequin/Animations/Swordsman/Attack/A_SW_Attack_01"));
	if (AnimAsset1.Succeeded()) {
    	Attack1Anim = AnimAsset1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence>AnimAsset2(TEXT("/Game/CloseCombat/Character/UE4Mannequin/Animations/Swordsman/Attack/A_SW_Attack_02"));
	if (AnimAsset2.Succeeded()) {
    	Attack2Anim = AnimAsset2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence>AnimAsset3(TEXT("/Game/CloseCombat/Character/UE4Mannequin/Animations/Swordsman/Attack/A_SW_Attack_04"));
	if (AnimAsset3.Succeeded()) {
    	Attack3Anim = AnimAsset3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence>AnimAsset4(TEXT("/Game/CloseCombat/Character/UE4Mannequin/Animations/Swordsman/Avoid/A_SW_Avoid_Backward"));
	if (AnimAsset4.Succeeded()) {
    	BackStepAnim = AnimAsset4.Object;
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	FName fnWeaponSocket = TEXT("Socket_Weapon");
 	UClass* m_cUClassWeapon = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/BluePrint/BP_Sword.BP_Sword_C"));
	if(m_cUClassWeapon!=nullptr)
	{
 	ASword* m_cWeapon = GetWorld()->SpawnActor<ASword>(m_cUClassWeapon);
 	m_cWeapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,fnWeaponSocket);
	}
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle,this,&APlayerCharacter::GetScore,10.f,true);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&APlayerCharacter::MoveForward);

	PlayerInputComponent->BindAxis("MoveRight",this,&APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Attack1",IE_Pressed,this,&APlayerCharacter::Attack1);

	PlayerInputComponent->BindAction("Attack2",IE_Pressed,this,&APlayerCharacter::Attack2);

	PlayerInputComponent->BindAction("Attack3",IE_Pressed,this,&APlayerCharacter::Attack3);

	PlayerInputComponent->BindAction("Dodge",IE_Pressed,this,&APlayerCharacter::Dodge);

	PlayerInputComponent->BindAction("BackStep",IE_Pressed,this,&APlayerCharacter::BackStep);
}

void APlayerCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction,Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction,Value);
}

void APlayerCharacter::Attack1()
{
	if(AttackAnimPlay==false&&DodgeAnimPlay==false&&BackAnimPlay==false)
	{
		AttackAnimPlay = true;
		GetMesh()->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(Attack1Anim,TEXT("Attack"),0.1f,0.2f,1.7f,1,-1.7f);
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		FTimerHandle handle;
    	GetWorldTimerManager().SetTimer(handle,this,&APlayerCharacter::ResetParm,0.8f,false);
	}
}

void APlayerCharacter::Attack2()
{
	if(AttackAnimPlay==false&&DodgeAnimPlay==false&&BackAnimPlay==false)
	{
		AttackAnimPlay = true;
		GetMesh()->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(Attack2Anim,TEXT("Attack"),0.1f,0.2f,1.7f,1,-1.4f);
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		FTimerHandle handle;
    	GetWorldTimerManager().SetTimer(handle,this,&APlayerCharacter::ResetParm,0.8f,false);
	}
}

void APlayerCharacter::Attack3()
{
	if(AttackAnimPlay==false&&DodgeAnimPlay==false&&BackAnimPlay==false)
	{
		AttackAnimPlay = true;
		GetMesh()->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(Attack3Anim,TEXT("Attack"),0.1f,0.2f,1.7f,1,-1.3);
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		FTimerHandle handle;
    	GetWorldTimerManager().SetTimer(handle,this,&APlayerCharacter::ResetParm,0.8f,false);
	}
}

void APlayerCharacter::BackStep()
{
	if(AttackAnimPlay==false&&DodgeAnimPlay==false&&BackAnimPlay==false)
	{
	BackAnimPlay = true;
	GetMesh()->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(BackStepAnim,TEXT("Back"),0.1f,0.2f,1.f,1,-0.2f);
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle,this,&APlayerCharacter::ResetParm,0.8f,false);
	}
}


void APlayerCharacter::Dodge()
{
	if(AttackAnimPlay==false&&DodgeAnimPlay==false&&BackAnimPlay==false)
	{
	DodgeAnimPlay = true;
	GetMesh()->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(DodgeAnim,TEXT("Dodge"),0.1f,0.2f,1.f,1,-0.2f);
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle,this,&APlayerCharacter::ResetParm,0.8f,false);
	}
}

void APlayerCharacter::ResetParm()
{
	AttackAnimPlay = false;
	DodgeAnimPlay = false;
	BackAnimPlay = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f,800.0f,0.0f);
}

void APlayerCharacter::GetScore()
{
	this->Score += 20;
}