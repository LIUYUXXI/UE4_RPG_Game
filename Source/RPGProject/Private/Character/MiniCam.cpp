// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MiniCam.h"
// GetCaptureComponent2D函数实际在"Components/SceneCaptureComponent2D.h"里，而不是"Engine/SceneCapture2D.h"里，官网文档写的不对啊
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RBaseCharacter.h"

AMiniCam::AMiniCam() {
	// 下面这句必须声明！！！！
	PrimaryActorTick.bCanEverTick = true;
	GetCaptureComponent2D()->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
}


void AMiniCam::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AMiniCamBeginPlay"));
	// 获取pawn
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
