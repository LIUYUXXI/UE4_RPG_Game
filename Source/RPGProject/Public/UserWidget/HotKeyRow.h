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
	class UHorizontalBox* RowBox;// �����Ͻ�ÿ����ݼ���Ž�userwidget�ĵط�

	TArray<FKey> HotKeys;  // �ⲿ���ݹ����ģ���һ������Ҫ�İ���
	TArray<USkillHotKey*> SlotWidgets; // �߼��ϴ��ÿ����ݼ�ָ��ĵط�
public:
	FORCEINLINE void SetHotKeys(TArray<FKey> Keys) { this->HotKeys = Keys; }
	TArray<USkillHotKey*> GenerateHotKeys();
};
