// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/HotKeyRow.h"
#include "UserWidget/SkillHotKey.h"
#include "Components/HorizontalBox.h"

TArray<USkillHotKey*> UHotKeyRow::GenerateHotKeys()
{
	for (auto key : HotKeys) {
		// 生成widget的目标类必须是蓝图类，之前引用的是C++类，所以会找不到正确的类，导致SkillHotKey的指针为空。
		//USkillHotKey* SkillHotKey =  CreateWidget<USkillHotKey>(GetWorld(), LoadClass<USkillHotKey>(GetWorld(), TEXT("Class'/Script/RPGProject.SkillHotKey_C'")));
		USkillHotKey* SkillHotKey =  CreateWidget<USkillHotKey>(GetWorld(), LoadClass<USkillHotKey>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/WBP_SkillHotKey.WBP_SkillHotKey_C'")));
		SkillHotKey->SetKey(key);
		SlotWidgets.Add(SkillHotKey);
		RowBox->AddChildToHorizontalBox(SkillHotKey);
	}
	return SlotWidgets;
} 
