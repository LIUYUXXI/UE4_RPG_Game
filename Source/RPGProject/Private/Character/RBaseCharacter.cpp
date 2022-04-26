// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RBaseCharacter.h"
#include "Engine/Engine.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Character/CursorDecal.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "UserWidget/MainUserWidget.h"
#include "Engine/DataTable.h"
#include "Character/Info/CharacterInfo.h"
#include "Components/SceneCaptureComponent2D.h"
//#include "RPGProject.h"
#define CursorTraceChannel ECC_GameTraceChannel1

// Sets default values
ARBaseCharacter::ARBaseCharacter()
{
	// UE_LOG(LogTemp, Warning, TEXT("construct"));
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	CameraBoom->TargetArmLength = 600.0f;
	// bUsePawnControlRotation设置为true后,下面这句语句就无效了
	// CameraBoom->SetRelativeRotation(FRotator(-30.0f, 0, 0)); 

	bUseControllerRotationYaw = false;
	CameraBoom->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 不能在构造函数里使用ReadData，因为此时widget还没有生成，readdata里就尝试修改widget里的控件，指针为空，肯定会有异常
	// ReadData();

	Portrait = CreateDefaultSubobject<USceneCaptureComponent2D>("Portrait");
	Portrait->SetupAttachment(GetMesh(),"head");
	Portrait->SetRelativeLocation(FVector(0.0f,80.0f,0.0f));
	Portrait->SetRelativeRotation(FRotator(0.0f,-90.0f,90.0f));
	Portrait->FOVAngle = 30.0f;
	
	Keys.Add(EKeys::One);
	Keys.Add(EKeys::Two);
	Keys.Add(EKeys::Three);
	Keys.Add(EKeys::Four);
	Keys.Add(EKeys::Five);
	Keys.Add(EKeys::Six);
	Keys.Add(EKeys::Seven);
	Keys.Add(EKeys::Eight);
	Keys.Add(EKeys::Nine);
	Keys.Add(EKeys::F6);
	Keys.Add(EKeys::F7);
	Keys.Add(EKeys::F8);
	Keys.Add(EKeys::F9);
	Keys.Add(EKeys::F10);
	Keys.Add(EKeys::F11);
	Keys.Add(EKeys::F12);
	Keys.Add(EKeys::B);
	Keys.Add(EKeys::I);
	KeysPerRow = 9;
}

void ARBaseCharacter::ReadData()
{
	UDataTable* CharacterInfo =  Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/Blueprints/Character/Info/CharacterInfo.CharacterInfo'"))); 
	if (CharacterInfo == NULL) {
		UE_LOG(LogTemp, Error, TEXT("CharacterInfo is not found!"));
	}
	FCharacterInfo* Row = CharacterInfo->FindRow<FCharacterInfo>(TEXT("S1"), TEXT("Error"));

	if (Row) {
		TotalHp = Row->StartHp;
		CurrentHp = Row->StartHp;
		TotalMp = Row->StartMp;
		CurrentMp = Row->StartMp;
		CharacterName = Row->CharacterName;
		CurrentLevel = 1;
		SetLevel(CurrentLevel);
		ChangeCurrentHp(0);
		ChangeCurrentMp(0);
		
	}

}

// Called when the game starts or when spawned
void ARBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<APlayerController>(Controller);
	// PC = Cast<APlayerController>(GetController());
	PC->bShowMouseCursor = true;
	
	// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "BeginPlay");
	// UE_LOG(LogTemp, Warning, TEXT("%s"), * GetName()); 
	
	MainUserWidget = CreateWidget<UMainUserWidget>(
		GetWorld(), LoadClass<UMainUserWidget>(this,TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/WBP_Main.WBP_Main_C'")));
	MainUserWidget->GenerateHotKeys(Keys, KeysPerRow);
	MainUserWidget->AddToViewport();
	// ReadData can't used in 构造函数。
	ReadData();
}
     
void ARBaseCharacter::MoveForward(float value)
{
	
	if (value != 0 && Controller) {
		if (bHasMouseMoveCommand == true) {
			CancelMoveToCursor();
		}
		FRotator rotation = Controller->GetControlRotation();
		// UE_LOG(LogTemp, Warning, TEXT("%d"),rotation.Yaw);
		FRotator YawRotation = FRotator(0, rotation.Yaw, 0);
		// 如果不改变controller的方向，Direction2和Direction的效果是等效的，我就说了，controller Rotation不是（0，0，0）吗……,因为旋转镜头时改变了controller的方向，同时也改变了摄像机的方向
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector Direction2 = FVector(1, 0, 0);
		// UE_LOG(LogTemp, Warning, TEXT("%d,%d,%d"), Direction.X, Direction.Y, Direction.Z);
		AddMovementInput(Direction, value);
		// UE_LOG(LogTemp, Warning, TEXT("MoveForward")); 
	}
      
}

void ARBaseCharacter::MoveRight(float value)
{

	if (value != 0 && Controller) {
		if (bHasMouseMoveCommand == true) {
			CancelMoveToCursor();
		}
		FRotator rotation = Controller->GetControlRotation();
		//UE_LOG(LogTemp, Warning, TEXT("%d"), rotation.Yaw);
		FRotator YawRotation = FRotator(0, rotation.Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		FVector Direction2 = FVector(0, 1, 0);
		//UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f"), Direction.X, Direction.Y, Direction.Z);
		AddMovementInput(Direction, value);
	}
	
}

void ARBaseCharacter::OnSetDestinationPressed()
{
	CancelMoveToCursor();
	bHasMouseMoveCommand = true;
	MoveToCursor();
}

void ARBaseCharacter::SetNewMoveDestination(const FVector DesLocation)
{
	const float distance = FVector::Dist(DesLocation, GetActorLocation());
	if (distance > 100.0f) {
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(PC, DesLocation);
	}
}

void ARBaseCharacter::CancelMoveToCursor()
{
	bHasMouseMoveCommand = false;
	if (CurrentDecal) {
		GetCharacterMovement()->StopMovementImmediately();
		CurrentDecal->Destroy();
		CurrentDecal = nullptr;
	}
}

void ARBaseCharacter::MoveToCursor()
{
	FHitResult Hit;
	// Performs a collision query under the mouse cursor, looking for object types
	PC->GetHitResultUnderCursor(CursorTraceChannel, false, Hit);
	// Struct of optional parameters passed to SpawnActor function(s).
	FActorSpawnParameters params;
	params.Owner = this;
	// Indicates if this hit was a result of blocking collision.
	if (Hit.bBlockingHit) {
		CurrentDecal = GetWorld()->SpawnActor<ACursorDecal>(CursorDecal, Hit.Location, FRotator::ZeroRotator, params);
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ARBaseCharacter::CameraZoomIn()
{
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength - CameraZoomAlpha, MinCameraZoom_V, MaxCameraZoom_V);
}

void ARBaseCharacter::CameraZoomOut()
{
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength + CameraZoomAlpha, MinCameraZoom_V, MaxCameraZoom_V);
}


// Called every frame
void ARBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this, &ARBaseCharacter::MoveForward);// this是指明作用对象
	PlayerInputComponent->BindAxis("MoveRight", this, &ARBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ARBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ARBaseCharacter::Jump);// 这里是不是stopjumping才对
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &ARBaseCharacter::OnSetDestinationPressed);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARBaseCharacter::CameraZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARBaseCharacter::CameraZoomOut);
}

void ARBaseCharacter::ChangeCurrentHp(float DeltaHp)
{
	CurrentHp += DeltaHp; 
	MainUserWidget->SetHPProgressBar(CurrentHp / TotalHp);
}
void ARBaseCharacter::ChangeCurrentMp(float DeltaMp)
{
	CurrentMp += DeltaMp;
	MainUserWidget->SetMPProgressBar(CurrentMp / TotalMp);
}

void ARBaseCharacter::SetLevel(int Level)
{
	//Generate an FText that represents the passed number in the current culture
	CurrentLevel = Level;
	MainUserWidget->SetLevelText(FText::AsNumber(Level));
}

