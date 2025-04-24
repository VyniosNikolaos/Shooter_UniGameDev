// Fill out your copyright notice in the Description page of Project Settings.

#include "BurningFireEmitter.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "ShooterCharacter.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Constructor
ABurningFireEmitter::ABurningFireEmitter()
{
	PrimaryActorTick.bCanEverTick = true;

	FireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fire Mesh"));
	SetRootComponent(FireMesh);
	
	// Initialize CollisionSphere
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(FireMesh);
	// Bind overlap event
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABurningFireEmitter::OnOverlapBegin);

	// FireEffect
	FireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(RootComponent);

	// FireAudioComponent
	FireAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FireAudioComponent"));
	FireAudioComponent->SetupAttachment(RootComponent);
	FireAudioComponent->bAutoActivate = false; // Activate manually
}

void ABurningFireEmitter::BeginPlay()
{
	Super::BeginPlay();

	if (FireEffect)
	{
		FireEffect->ActivateSystem();
	}

	if (FireSound && FireAudioComponent)
	{
		FireAudioComponent->SetSound(FireSound);

		// Enable attenuation for proximity-based volume adjustment
		FireAudioComponent->SetVolumeMultiplier(1.0f);
		FireAudioComponent->Play();
	}
}void ABurningFireEmitter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
										 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
										 bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OtherActor);
	if (ShooterCharacter)
	{
		// Start burning the player
		ShooterCharacter->StartBurning();
	}
}
