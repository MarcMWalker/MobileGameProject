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
	DeltaTime = 1 / 30.0;
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChange = 1.60f;
	const float SmoothBlendTime = 0.40f;
	TimeToNextCameraChange -= DeltaTime;

	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChange;

		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this,0);
	
		if(OurPlayerController){

			if (OurPlayerController->IsInputKeyDown(EKeys::A) && CameraTwo && (OurPlayerController->GetViewTarget() == CameraOne)) {
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::D) && CameraOne && (OurPlayerController->GetViewTarget() == CameraOne)) {
				OurPlayerController->SetViewTargetWithBlend(CameraFour, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::D) && CameraTwo && (OurPlayerController->GetViewTarget() == CameraTwo)) {
				OurPlayerController->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::A) && CameraThree && (OurPlayerController->GetViewTarget() == CameraTwo)) {
				OurPlayerController->SetViewTargetWithBlend(CameraThree, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::D) && CameraThree && (OurPlayerController->GetViewTarget() == CameraThree)) {
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::W) && CameraThree && (OurPlayerController->GetViewTarget() == CameraThree)) {
				OurPlayerController->SetViewTargetWithBlend(CameraFive, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::S) && CameraFive && (OurPlayerController->GetViewTarget() == CameraFive)) {
				OurPlayerController->SetViewTargetWithBlend(CameraThree, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::D) && CameraFour && (OurPlayerController->GetViewTarget() == CameraFour)) {
				OurPlayerController->SetViewTargetWithBlend(CameraThree, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::A) && CameraFour && (OurPlayerController->GetViewTarget() == CameraThree)) {
				OurPlayerController->SetViewTargetWithBlend(CameraFour, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::W) && CameraFour && (OurPlayerController->GetViewTarget() == CameraFour)) {
				OurPlayerController->SetViewTargetWithBlend(CameraSix, SmoothBlendTime);
			}

			else if (OurPlayerController->IsInputKeyDown(EKeys::S) && CameraSix && (OurPlayerController->GetViewTarget() == CameraSix)) {
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

