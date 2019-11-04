// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class SUBMIT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Attack1();

	UFUNCTION()
	void Attack2();

	UFUNCTION()
	void Attack3();

	UFUNCTION()
	void Dodge();

	UFUNCTION()
	void BackStep();

	UFUNCTION()
	void ResetParm();

	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(VisibleDefaultsOnly, Category = Sword)
    UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Attack)
	bool AttackAnimPlay;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Anim)
	bool DodgeAnimPlay = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Anim)
	bool BackAnimPlay = false;

	UPROPERTY()
	FName fnWeaponSocket;

	UPROPERTY()
	UClass* m_cUClassWeapon;


	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsGameOver = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int Score = 0;

	UFUNCTION()
	void GetScore();

private:
	UPROPERTY()
	UAnimSequence* DodgeAnim;

	UPROPERTY()
	UAnimSequence* Attack1Anim;

	UPROPERTY()
	UAnimSequence* Attack2Anim;

	UPROPERTY()
	UAnimSequence* Attack3Anim;

	UPROPERTY()
	UAnimSequence* BackStepAnim;
};
