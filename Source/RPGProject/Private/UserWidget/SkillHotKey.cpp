// Fill out your copyright notice in the Description page of Project Settings.
#include "UserWidget/SkillHotKey.h"
#include "Components/TextBlock.h"
#include "Character/Skill/BaseSkill.h"
#include "Components/Button.h"
#include "Components/Image.h"

bool USkillHotKey::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	SkillButton->OnClicked.AddDynamic(this, &USkillHotKey::OnSkillButtonClicked);
	return true;
}

void USkillHotKey::OnSkillButtonClicked()
{
	AssignedSkill->OnTryCastSkill();
}

void USkillHotKey::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (!bHasSetKeyName) {
		HotKeyName->SetText(HotKey.GetDisplayName());
		bHasSetKeyName = true;
	}
	
}

void USkillHotKey::AssignSkill(ABaseSkill* NewAssighSkill)
{
	this->AssignedSkill = NewAssighSkill;
	AssignedSkill->SetHotKey(this);
	SkillButton->SetIsEnabled(true);
	if (AssignedSkill->GetCurrentStage().OverideIcon) {
		SkillIcon->SetBrushFromTexture(AssignedSkill->GetCurrentStage().OverideIcon);
	}
	else {
		SkillIcon->SetBrushFromTexture(AssignedSkill->GetFSkillInfo().Icon);
	}
	SkillIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void USkillHotKey::ClearAssignedSkill()
{
	if (AssignedSkill) {
		AssignedSkill->SetHotKey(nullptr);
		AssignedSkill = nullptr;

		SkillButton->SetIsEnabled(false);
		SkillIcon->SetBrushFromTexture(nullptr);
		SkillIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}
