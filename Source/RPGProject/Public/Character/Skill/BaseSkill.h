// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/RBaseCharacter.h"
#include "BaseSkill.generated.h"
// 基本技能类
UCLASS()
class RPGPROJECT_API ABaseSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSkill();

protected:
	UPROPERTY(EditAnywhere, Category = SkillInfo)
	FSkillInfo SkillInfo;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int CurrentStageIndex;

	

	bool bOnCoolDown;//是否正在冷却中
	bool bCurrentCasted;//技能释放正在释放
	class USkillHotKey* Hotkey;//与该技能绑定的快捷键

	class ARBaseCharacter* PlayerReference;//谁拥有了该技能

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE FSkillStage GetCurrentStage() { return SkillInfo.Stages[CurrentStageIndex]; }
	FORCEINLINE void SetHotKey(class USkillHotKey* HotKey) {this->Hotkey = HotKey;}
	FORCEINLINE FSkillInfo GetFSkillInfo() { return SkillInfo; }
	void OnTryCastSkill();
};
