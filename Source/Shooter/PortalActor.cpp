// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

// Sets default values
APortalActor::APortalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the trigger box and set its collision profile
	PortalTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalTriggerBox"));
	RootComponent = PortalTriggerBox;
	PortalTriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PortalTriggerBox->SetCollisionObjectType(ECC_WorldDynamic);
	PortalTriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	PortalTriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Bind overlap event
	PortalTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::OnOverlapBegin);

	// Set a default level name (you can modify this in the Editor)
	DestinationLevelName = "DungeonLevel"; 
}


// Called when the game starts or when spawned
void APortalActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	// Check if the overlapping actor is a player character
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		// Open the destination level
		UGameplayStatics::OpenLevel(this, DestinationLevelName);
	}
}