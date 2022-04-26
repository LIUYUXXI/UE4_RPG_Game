// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillEnum.generated.h"


UENUM()
enum class ETargetTypes:uint8 
{
	Self,
	SelectedEnemy,
	SelectedArea, // AOE
	AreaAroundSelf,
	Missle
};

UENUM()
enum class EDamageTypes :uint8
{
	Magic,
	Physical
};

UENUM()
enum class EEffectiveness :uint8
{
	Effective,
	SuperEffective,
	NotEffctive
};

UCLASS()
class RPGPROJECT_API USkillEnum : public UObject
{
	GENERATED_BODY()
	
};
