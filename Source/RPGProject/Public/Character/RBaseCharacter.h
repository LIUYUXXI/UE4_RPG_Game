// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/SkillEnum.h"
#include "GameFramework/Character.h"
#include "RBaseCharacter.generated.h"

class ABaseSkill;
//class UTexture2D;
class ABaseElement;
USTRUCT() 
struct FSkillStage
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = SkillData)
		int RequiredLevel;// ��Ҫ��ǰ�õȼ�
	UPROPERTY(EditAnywhere, Category = SkillData)
	TArray<ABaseSkill*> RequiredSkills;// ��Ҫ��ǰ�ü���
	UPROPERTY(EditAnywhere, Category = SkillData)
	UTexture2D* OverideIcon;// ���ǵ�ͼ�꣬���Ϊ�գ������ó�ʼ���ܵ�ͼ��
	UPROPERTY(EditAnywhere, Category = SkillData)
	float Range;// �˺���Χ
	UPROPERTY(EditAnywhere, Category = SkillData)
	float Damage;// �˺�ֵ
	UPROPERTY(EditAnywhere, Category = SkillData)
	EDamageTypes DamageType; // �˺�����
	UPROPERTY(EditAnywhere, Category = SkillData)
	int CriticalChance; // ������
	UPROPERTY(EditAnywhere, Category = SkillData)
	float CoolDownTime;// ������ȴʱ��
	UPROPERTY(EditAnywhere, Category = SkillData)
	float CastingTime;// �����ͷ�ʱ��
	UPROPERTY(EditAnywhere, Category = SkillData)
	float ManaCost; // ħ������ֵ
	UPROPERTY(EditAnywhere, Category = SkillData)
	float MissileSpeed;// Ͷ���༼�ܵ��ٶ�
};

USTRUCT()
struct FSkillInfo 
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = SkillData)
		FText Name;
	UPROPERTY(EditAnywhere, Category = SkillData)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, Category = SkillData)
	FText Description;
	UPROPERTY(EditAnywhere, Category = SkillData)
	TSubclassOf<ABaseElement> Element;
	UPROPERTY(EditAnywhere, Category = SkillData)
	ETargetTypes Target;
	UPROPERTY(EditAnywhere, Category = SkillData)
	TArray<FSkillStage> Stages;
};

UCLASS()
class RPGPROJECT_API ARBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARBaseCharacter();

protected:

	class UMainUserWidget* MainUserWidget;
	// ������������ᵼ�³������
	// class APlayerController PC;
	class APlayerController* PC;
	UPROPERTY(VisibleAnywhere, Category="Camera")
	class UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USceneCaptureComponent2D* Portrait;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float MinCameraZoom_V = 25.0f;
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxCameraZoom_V = 1000.0f;
	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraZoomAlpha = 25.0f;

	UPROPERTY(EditAnywhere, Category = "Mouse")
	TSubclassOf<class ACursorDecal> CursorDecal;

	bool bHasMouseMoveCommand = false;

	class ACursorDecal* CurrentDecal;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveForward(float value);
	void MoveRight(float value);
	void OnSetDestinationPressed();
	void SetNewMoveDestination(const FVector DesLocation);
	void CancelMoveToCursor();
	void MoveToCursor();
	void CameraZoomIn();
	void CameraZoomOut();

protected:
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	float CurrentHp;
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	float CurrentMp;
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	float CurrentExp;
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	float TotalHp;
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	float TotalMp;
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	int CurrentLevel;
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	FString CharacterName;

	void ReadData();

protected:
	UPROPERTY(EditAnywhere, Category = UI)
	TArray<FKey> Keys;
	UPROPERTY(EditAnywhere, Category = UI)
	int KeysPerRow = 9;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ChangeCurrentHp(float DeltaHp);
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	void ChangeCurrentMp(float DeltaMp);
	FORCEINLINE float GetCurrentMp() { return CurrentMp; }
	FORCEINLINE void ChangeCurrentExp(float DeltaExp) { CurrentExp += DeltaExp; }
	FORCEINLINE float GetCurrentExp() { return CurrentExp; }
	FORCEINLINE FString GetCharacterName() { return CharacterName; }
	void SetLevel(int Level);

};
