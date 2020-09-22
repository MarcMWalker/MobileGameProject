// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerInput.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	start = true;
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChange = 0.45f;
	const float SmoothBlendTime = 0.40f;
	TimeToNextCameraChange -= DeltaTime*4;

	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChange;

		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this,0);
	
		if(OurPlayerController){

			if (OurPlayerController->IsInputKeyDown(EKeys::A) && CameraTwo && (OurPlayerController->GetViewTarget() == CameraOne)) {
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::A) && CameraThree && (OurPlayerController->GetViewTarget() == CameraTwo)) {
				OurPlayerController->SetViewTargetWithBlend(CameraThree, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::A) && CameraFour && (OurPlayerController->GetViewTarget() == CameraThree)) {
				OurPlayerController->SetViewTargetWithBlend(CameraFour, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::A) && CameraOne &&(OurPlayerController->GetViewTarget() == CameraFour)) {
				OurPlayerController->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);
			}

			else if (start == true && CameraOne) {
				OurPlayerController->SetViewTarget(CameraOne);
			}
			start = false;
		}
	}
}

