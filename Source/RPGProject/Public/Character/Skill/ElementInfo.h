// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Color.h"
// 下面这个自动引用的头文件要注释掉
//#include "UObject/NoExportTypes.h"
//#include "Character/Skill/BaseElement.h"
#include "ElementInfo.generated.h"



class ABaseElement;

USTRUCT()
struct FElementInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere,Category=ElementData)
		FText Name;
	UPROPERTY(EditAnywhere, Category = ElementData)
	class UTexture2D* Icon;// 元素图标
	UPROPERTY(EditAnywhere, Category = ElementData)
	FLinearColor Color;//元素的颜色
	UPROPERTY(EditAnywhere, Category = ElementData)
	TArray<TSubclassOf<ABaseElement>> Resistances; //增强效果的元素
	UPROPERTY(EditAnywhere, Category = ElementData)
	TArray<TSubclassOf<ABaseElement>> Weakness; //增强效果的元素
};
