// Fill out your copyright notice in the Description page of Project Settings.


#include "PushedActor.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APushedActor::APushedActor()

{
	PrimaryActorTick.bCanEverTick = true;

	// Create and set the static mesh component
	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RockMesh"));
	RockMesh->SetupAttachment(RootComponent);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RockMesh);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APushedActor::OnOverlapBegin);
	
	// Enable physics for the rock
	RockMesh->SetSimulatePhysics(true);
	
}

// Called when the game starts or when spawned
void APushedActor::BeginPlay()
{
	Super::BeginPlay();
}


void APushedActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterCharacter* PlayerCharacter = Cast<AShooterCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PushSound, GetActorLocation());
	}
}

// Called every frame
void APushedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}