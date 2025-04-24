// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterExtinguisher.h"
#include "Components/BoxComponent.h"
#include "ShooterCharacter.h"

// Sets default values
AWaterExtinguisher::AWaterExtinguisher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize CollisionBox
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));	
    CollisionBox->SetupAttachment(GetRootComponent());	
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void AWaterExtinguisher::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap event
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWaterExtinguisher::OnOverlapBegin);
}

// Overlap event
void AWaterExtinguisher::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
										UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
										bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is the player
	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OtherActor);
	if (ShooterCharacter)
	{
		// Call ExtinguishFire method
		ShooterCharacter->ExtinguishFire();
	}
}

// Called every frame
void AWaterExtinguisher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

