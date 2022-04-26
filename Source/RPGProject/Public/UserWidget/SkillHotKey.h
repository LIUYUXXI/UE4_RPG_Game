// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputCoreTypes.h"
#include "SkillHotKey.generated.h"


class UTextBlock;
class UImage;
class ABaseSkill;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API USkillHotKey : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* HotKeyName;
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* CoolDownText;
	UPROPERTY(Meta = (BindWidget))
	UImage* SkillIcon;
	UPROPERTY(Meta = (BindWidget))
	UImage* CoolDownImage;
	UPROPERTY(Meta = (BindWidget))
	class UButton* SkillButton;

	
	bool bHasSetKeyName = false;
	virtual bool Initialize() override;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	FKey HotKey;
	ABaseSkill* AssignedSkill; // 这个快捷键被分配了什么技能

	UFUNCTION()
	void OnSkillButtonClicked();

public:
	FORCEINLINE void SetKey(FKey Key) { 
		////if (Key != NULL) {
		//UE_LOG(LogTemp, Error, TEXT("First: "));
		//	UE_LOG(LogTemp, Error, TEXT("%s"), *(Key.GetDisplayName().ToString()));
		////}
		//	if (this != nullptr) {
		//		UE_LOG(LogTemp, Error, TEXT("This is not nullptr"));
		//}
		this->HotKey = Key;
	}
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void AssignSkill(ABaseSkill* NewAssighSkill);// 为该快捷键分配技能
	void ClearAssignedSkill();// 为该快捷键clear技能

};
