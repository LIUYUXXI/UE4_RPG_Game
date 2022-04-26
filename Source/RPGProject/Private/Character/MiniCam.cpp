// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MiniCam.h"
// GetCaptureComponent2D����ʵ����"Components/SceneCaptureComponent2D.h"�������"Engine/SceneCapture2D.h"������ĵ�д�Ĳ��԰�
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RBaseCharacter.h"

AMiniCam::AMiniCam() {
	// ����������������������
	PrimaryActorTick.bCanEverTick = true;
	GetCaptureComponent2D()->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
}


void AMiniCam::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AMiniCamBeginPlay"));
	// ��ȡpawn
	Character = Cast<ARBaseCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)) ;
	SetActorLocation(FVector(Character->GetActorLocation().X, Character->GetActorLocation().Y, Character->GetActorLocation().Z + 1200.0f));
}


void AMiniCam::OutsideTick() {
	//FVector TargetLocation = FVector(Character->GetActorLocation().X, Character->GetActorLocation().Y, GetActorLocation().Z);
	FVector TargetLocation = Character->GetActorLocation() + FVector(0, 0, 1200);
	UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f"),TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
	SetActorLocation(TargetLocation);
}

void AMiniCam::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UE_LOG(LogTemp, Warning, TEXT("AMiniCamTick"));
	OutsideTick();
}
