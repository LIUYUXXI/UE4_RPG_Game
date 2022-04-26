// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/RBaseCharacter.h"
#include "BaseSkill.generated.h"
// ����������
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

	

	bool bOnCoolDown;//�Ƿ�������ȴ��
	bool bCurrentCasted;//�����ͷ������ͷ�
	class USkillHotKey* Hotkey;//��ü��ܰ󶨵Ŀ�ݼ�

	class ARBaseCharacter* PlayerReference;//˭ӵ���˸ü���

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE FSkillStage GetCurrentStage() { return SkillInfo.Stages[CurrentStageIndex]; }
	FORCEINLINE void SetHotKey(class USkillHotKey* HotKey) {this->Hotkey = HotKey;}
	FORCEINLINE FSkillInfo GetFSkillInfo() { return SkillInfo; }
	void OnTryCastSkill();
};
