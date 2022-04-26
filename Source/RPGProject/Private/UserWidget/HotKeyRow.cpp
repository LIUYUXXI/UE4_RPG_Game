// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/HotKeyRow.h"
#include "UserWidget/SkillHotKey.h"
#include "Components/HorizontalBox.h"

TArray<USkillHotKey*> UHotKeyRow::GenerateHotKeys()
{
	for (auto key : HotKeys) {
		// ����widget��Ŀ�����������ͼ�֮࣬ǰ���õ���C++�࣬���Ի��Ҳ�����ȷ���࣬����SkillHotKey��ָ��Ϊ�ա�
		//USkillHotKey* SkillHotKey =  CreateWidget<USkillHotKey>(GetWorld(), LoadClass<USkillHotKey>(GetWorld(), TEXT("Class'/Script/RPGProject.SkillHotKey_C'")));
		USkillHotKey* SkillHotKey =  CreateWidget<USkillHotKey>(GetWorld(), LoadClass<USkillHotKey>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/WBP_SkillHotKey.WBP_SkillHotKey_C'")));
		SkillHotKey->SetKey(key);
		SlotWidgets.Add(SkillHotKey);
		RowBox->AddChildToHorizontalBox(SkillHotKey);
	}
	return SlotWidgets;
} 
