// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget/SkillHotKey.h"
#include "MainUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class RPGPROJECT_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

	class UTextBlock* LevelText;
	class UProgressBar* HPProgressBar;
	class UProgressBar* MPProgressBar;
	//class UHotkeyRow;

	UPROPERTY(Meta = (BindWidget))
	class UVerticalBox* HotKeyRowContainer;

	TArray<FKey> Keys;

	TArray<USkillHotKey*> AllHotKeySlots;

	virtual bool Initialize() override;
	// debug
	TArray<class UHotKeyRow*> HotkeyRows;

public:
	void SetLevelText(FText Text);

	void SetHPProgressBar(float Percent);

	void SetMPProgressBar(float Percent);

	void GenerateHotKeys(TArray<FKey> KeysToGenerate,int KeysPerRow);

};
