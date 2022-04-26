// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RGideon.h"
#include "Animation/AnimInstance.h"
#include "Engine/SkeletalMesh.h"

ARGideon::ARGideon() {
	// 用mesh命名会有问题
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Skeleton(TEXT("SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon'"));
	GetMesh()->SetSkeletalMesh(Skeleton.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));
	static ConstructorHelpers::FClassFinder<UAnimInstance> Anim(TEXT("AnimBlueprint'/Game/Blueprints/Character/Animations/ABP_Gideon.ABP_Gideon_C'"));
	GetMesh()->SetAnimInstanceClass(Anim.Class);
}
