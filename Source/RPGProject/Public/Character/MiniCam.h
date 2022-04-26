// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "MiniCam.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API AMiniCam : public ASceneCapture2D
{
	GENERATED_BODY()

		AMiniCam();

	virtual void BeginPlay() override;
	class ARBaseCharacter* Character;

public:
	// Called every frame

	
	void OutsideTick();

	void Tick(float DeltaSeconds) override;
};
