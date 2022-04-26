// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HotKeyRow.generated.h"
class USkillHotKey;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API UHotKeyRow : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(Meta = (BindWidget))
	class UHorizontalBox* RowBox;// 物理上将每个快捷键存放进userwidget的地方

	TArray<FKey> HotKeys;  // 外部传递过来的，这一排所需要的按键
	TArray<USkillHotKey*> SlotWidgets; // 逻辑上存放每个快捷键指针的地方
public:
	FORCEINLINE void SetHotKeys(TArray<FKey> Keys) { this->HotKeys = Keys; }
	TArray<USkillHotKey*> GenerateHotKeys();
};
