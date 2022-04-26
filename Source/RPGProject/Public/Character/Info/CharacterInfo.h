// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "CharacterInfo.generated.h"

USTRUCT()
struct FCharacterInfo: public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "CharanterInfo")
	FString CharacterName;
	UPROPERTY(EditAnywhere, Category = "CharanterInfo")
	float StartHp;
	UPROPERTY(EditAnywhere, Category = "CharanterInfo")
	float StartMp;
};
/**
 * 
 */
//UCLASS()
//class RPGPROJECT_API UCharacterInfo : public UObject
//{
//	GENERATED_BODY()
//	
//};
