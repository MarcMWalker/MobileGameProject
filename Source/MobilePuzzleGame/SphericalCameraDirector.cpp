// Fill out your copyright notice in the Description page of Project Settings.

#include "SphericalCameraDirector.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"


// Sets default values
ASphericalCameraDirector::ASphericalCameraDirector ()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASphericalCameraDirector::BeginPlay ()
{
	Super::BeginPlay ();

	//	This is the angular distance between cameras in Radians
	float Polar = (2.0f * PI) / 4.0f;

	//	Position and rotate cameras
	for (int i = 0; i < 4; ++i)
	{
		//	Use Spherical Coordinates to position camera
		FVector Position = FVector (
			Radius * sin (Azimuth) * sin (i * Polar), 
			Radius * sin (Azimuth) * cos (i * Polar), 
			cos (Azimuth) * Radius);

		//	TODO : Add Custom World Target
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation (Position, FVector (0.0f, 0.0f, 0.0f));

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.Instigator = Instigator;

		CameraActors[i] = (AActor*) GetWorld ()->SpawnActor <ACameraActor> (Position, Rotation, SpawnInfo);
	}

	Controller = UGameplayStatics::GetPlayerController (this, 0);
	Controller->SetViewTarget (CameraActors[CameraIndex]);
}

// Called every frame
void ASphericalCameraDirector::Tick (float DeltaTime)
{
	Super::Tick (DeltaTime);

}

// Called to bind functionality to input
void ASphericalCameraDirector::SetupPlayerInputComponent (UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent (PlayerInputComponent);

	//	Setup Input Bindings
	// TODO : Setup Touch Controls
	PlayerInputComponent->BindAction ("GoRight", IE_Pressed, this, &ASphericalCameraDirector::RightCamera);
	PlayerInputComponent->BindAction ("GoLeft", IE_Pressed, this, &ASphericalCameraDirector::LeftCamera);
}

void ASphericalCameraDirector::RightCamera ()
{
	//	Blend to camera to the right
	CameraIndex = (CameraIndex + 1) & 3;
	Controller->SetViewTargetWithBlend (CameraActors[CameraIndex], BlendTime);

	UE_LOG (LogTemp, Warning, TEXT ("Right Index : %d"), CameraIndex);
}

void ASphericalCameraDirector::LeftCamera ()
{
	//	Blend to camera to the left
	CameraIndex = (CameraIndex - 1) & 3;
	Controller->SetViewTargetWithBlend (CameraActors[CameraIndex], BlendTime);

	UE_LOG (LogTemp, Warning, TEXT ("Left Index : %d"), CameraIndex);
}