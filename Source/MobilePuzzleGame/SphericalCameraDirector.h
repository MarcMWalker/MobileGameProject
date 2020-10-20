// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SphericalCameraDirector.generated.h"

UCLASS()
class MOBILEPUZZLEGAME_API ASphericalCameraDirector : public APawn
{
	GENERATED_BODY()

	AActor* CameraActors[4];

	UPROPERTY (EditAnywhere, Category = Camera)
	float Azimuth = 0.0f;

	UPROPERTY (EditAnywhere, Category = Camera)
	float Radius = 1.0f;

	UPROPERTY (EditAnywhere, Category = Camera)
	float BlendTime = 0.5f;

	unsigned char CameraIndex = 0;

	class APlayerController* Controller = NULL;

public:
	// Sets default values for this pawn's properties
	ASphericalCameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RightCamera ();
	void LeftCamera ();
	
};
