// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonAudioManager.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "GlobalDayNightManager.h"

ADungeonAudioManager::ADungeonAudioManager():
    FadeTime(1.0f)

{
    PrimaryActorTick.bCanEverTick = true;

    DungeonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DungeonTrigger"));
    SetRootComponent(DungeonTrigger);
    DungeonTrigger->SetBoxExtent(FVector(200.f)); // Example size

    DungeonAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("DungeonAudio"));
    DungeonAudio->SetupAttachment(RootComponent);
    DungeonAudio->bAutoActivate = false;
}

void ADungeonAudioManager::BeginPlay()
{
    Super::BeginPlay();

    // If assigned in Editor, or search for it:
     //GlobalManager = Cast<AGlobalDayNightManager>(
     //    UGameplayStatics::GetActorOfClass(GetWorld(), AGlobalDayNightManager::StaticClass()));
    
    DungeonTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADungeonAudioManager::OnDungeonBeginOverlap);
    DungeonTrigger->OnComponentEndOverlap.AddDynamic(this, &ADungeonAudioManager::OnDungeonEndOverlap);

    if (DungeonSound)
    {
        DungeonAudio->SetSound(DungeonSound);
    }
}

void ADungeonAudioManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

void ADungeonAudioManager::OnDungeonBeginOverlap(
    UPrimitiveComponent* OverlappedComp, 
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex, 
    bool bFromSweep, 
    const FHitResult & SweepResult)
{
    AShooterCharacter* PlayerChar = Cast<AShooterCharacter>(OtherActor);
    if (!PlayerChar) return;

    // Fade out day-night audio if we want
    if (GlobalManager)
    {
        GlobalManager->FadeOutDayNight(FadeTime, 0.0f);
        GlobalManager->bIsOutside = false;
    }

    // Fade in dungeon music
    if (!DungeonAudio->IsPlaying())
    {
        DungeonAudio->FadeIn(FadeTime, 1.0f);
    }
}

void ADungeonAudioManager::OnDungeonEndOverlap(
    UPrimitiveComponent* OverlappedComp, 
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex)
{
    AShooterCharacter* PlayerChar = Cast<AShooterCharacter>(OtherActor);
    if (!PlayerChar) return;

    // Fade out dungeon music
    if (DungeonAudio->IsPlaying())
    {
        DungeonAudio->FadeOut(FadeTime, 0.0f);
    }

    // Fade in day-night audio again
    if (GlobalManager)
    {
        GlobalManager->bIsOutside = true;
        GlobalManager->FadeInDayNight(FadeTime, 1.0f);
    }
}
