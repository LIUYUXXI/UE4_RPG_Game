// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CursorDecal.h"
#include "Components/DecalComponent.h"
#include "Components/SceneComponent.h"
//#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"

// Sets default values
ACursorDecal::ACursorDecal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
	
	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRootComponent");
	RootComponent = DefaultRootComponent;
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	// CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	Boxcomponent = CreateDefaultSubobject<UBoxComponent>("Boxcomponent");
	Boxcomponent->SetupAttachment(RootComponent);
	Boxcomponent->SetBoxExtent(FVector(32.0f,34.0f,20.0f));

	//Boxcomponent->OnComponentBeginOverlap.AddDynamic(this, &ACursorDecal::OnOverlap);
	
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));\
	// 因为是在构造函数中的静态加载，所以用的是FObjectFinder，如果是动态加载，就是用LoadObject吗？
	static ConstructorHelpers::FObjectFinder<UMaterial>  DecalMaterial(TEXT("Material'/Game/Textures/CursorDecal_Material.CursorDecal_Material'"));
	if (DecalMaterial.Succeeded()) {
		CursorToWorld->SetDecalMaterial(DecalMaterial.Object);
	}
}

// Called when the game starts or when spawned
void ACursorDecal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACursorDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACursorDecal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	// Follow the Outer chain to get the AActor that 'Owns' this component
	if (OtherActor == GetOwner()) {
		Destroy();
	}
}

//void ACursorDecal::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor == GetOwner()) {
//		Destroy();
//	}
//}

