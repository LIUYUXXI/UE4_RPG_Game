// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/MainUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "UserWidget/HotKeyRow.h"
#include "Components/VerticalBox.h"

bool UMainUserWidget::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	LevelText =Cast<UTextBlock>(GetWidgetFromName("TEXT_Level"));
	HPProgressBar =Cast<UProgressBar>(GetWidgetFromName("ProgressBar_HP"));
	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName("ProgressBar_MP"));
	return true;
}

void UMainUserWidget::SetLevelText(FText Text)
{
	LevelText->SetText(Text);
}

void UMainUserWidget::SetHPProgressBar(float Percent)
{
	HPProgressBar->SetPercent(Percent);
}

void UMainUserWidget::SetMPProgressBar(float Percent)
{
	MPProgressBar->SetPercent(Percent);
}

void UMainUserWidget::GenerateHotKeys(TArray<FKey> KeysToGenerate, int KeysPerRow)
{	
	TArray<FKey> LocalKeys = KeysToGenerate;
	TArray<FKey> LocalModifyKeys = KeysToGenerate;
	if (KeysToGenerate.Num() % KeysPerRow != 0) {
		UE_LOG(LogTemp, Warning, TEXT("The keys num is invalid!"));
		return;
	}
	if (LocalKeys.Num() == KeysPerRow) {
		UHotKeyRow* HotKeyRow = CreateWidget<UHotKeyRow>(GetWorld(), LoadClass<UHotKeyRow>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/WBP_HotKeyRow.WBP_HotKeyRow_C'")));
		HotKeyRow->SetHotKeys(LocalKeys);
		//HotKeyRowContainer->AddChildToVerticalBox(HotKeyRow);
		AllHotKeySlots.Append(HotKeyRow->GenerateHotKeys());
		//debug
		HotkeyRows.Add(HotKeyRow);
		for (int i = HotkeyRows.Num() - 1; i >= 0; i--) {
			HotKeyRowContainer->AddChildToVerticalBox(HotkeyRows[i]);
		}
	}
	else {
		LocalModifyKeys.SetNum(KeysPerRow);
		UHotKeyRow* HotKeyRow = CreateWidget<UHotKeyRow>(GetWorld(), LoadClass<UHotKeyRow>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/WBP_HotKeyRow.WBP_HotKeyRow_C'")));
		HotKeyRow->SetHotKeys(LocalModifyKeys);
		//HotKeyRowContainer->AddChildToVerticalBox(HotKeyRow);
		AllHotKeySlots.Append(HotKeyRow->GenerateHotKeys());
		//debug
		HotkeyRows.Add(HotKeyRow);
		for (auto key : LocalModifyKeys) {
			if (LocalKeys.Contains(key)) {
				LocalKeys.Remove(key);
			}
		}
		GenerateHotKeys(LocalKeys, KeysPerRow);
	}
	
}
