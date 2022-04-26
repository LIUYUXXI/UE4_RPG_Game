// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Color.h"
// ��������Զ����õ�ͷ�ļ�Ҫע�͵�
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
	class UTexture2D* Icon;// Ԫ��ͼ��
	UPROPERTY(EditAnywhere, Category = ElementData)
	FLinearColor Color;//Ԫ�ص���ɫ
	UPROPERTY(EditAnywhere, Category = ElementData)
	TArray<TSubclassOf<ABaseElement>> Resistances; //��ǿЧ����Ԫ��
	UPROPERTY(EditAnywhere, Category = ElementData)
	TArray<TSubclassOf<ABaseElement>> Weakness; //��ǿЧ����Ԫ��
};
