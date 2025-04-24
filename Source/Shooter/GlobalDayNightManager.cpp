#include "GlobalDayNightManager.h"

#include "DungeonAudioManager.h"
#include "Components/AudioComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/World.h"
#include "Sound/SoundBase.h"
#include "Misc/OutputDeviceNull.h"

AGlobalDayNightManager::AGlobalDayNightManager():
    SunTurnRate(1.0f),
    NightThresholdPitch(0.f),
    bIsOutside(true)
{
    PrimaryActorTick.bCanEverTick = true;

    
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    DayNightAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("DayNightAudio"));
    DayNightAudio->SetupAttachment(RootComponent);
    DayNightAudio->bAutoActivate = false;
}

void AGlobalDayNightManager::BeginPlay()
{
    Super::BeginPlay();

    // Play day sound at the start by default
    if (DaySound)
    {
        DayNightAudio->SetSound(DaySound);
        DayNightAudio->Play();
    }
    
}

void AGlobalDayNightManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (SunLightSource)
    {
        // Rotate sun
        SunLightSource->AddActorLocalRotation(FRotator( DeltaTime * SunTurnRate,0 ,0 ));
    }
    if (SunSkySphere)
    {
        FOutputDeviceNull OutputDevice;
        SunSkySphere->CallFunctionByNameWithArguments(
        TEXT("UpdateSunDirection"), OutputDevice, nullptr, true);
    }    

    // Update day vs. night
    UpdateDayNightAudio();
    
}

void AGlobalDayNightManager::UpdateDayNightAudio()
{
    // If no SunLightSource, or no sounds, just return
    if (!SunLightSource || !DaySound || !NightSound || !bIsOutside) return;
    
    float Pitch = SunLightSource->GetActorRotation().Pitch;

    // If pitch < NightThresholdPitch => "Daytime" (arbitrary logic)
    bool bIsDay = (Pitch < NightThresholdPitch);

    // If currently playing a different sound, switch
    USoundBase* CurrentSound = DayNightAudio->Sound;
    if (bIsDay && CurrentSound != DaySound)
    {
        DayNightAudio->SetSound(DaySound);
        DayNightAudio->Play();
    }
    else if (!bIsDay && CurrentSound != NightSound)
    {
        DayNightAudio->SetSound(NightSound);
        DayNightAudio->Play();
    }
}

void AGlobalDayNightManager::FadeOutDayNight(float FadeTime, float FadeVolumeEnd)
{
    if (DayNightAudio && DayNightAudio->IsPlaying())
    {
        DayNightAudio->FadeOut(FadeTime, 0.f);
    }
}

void AGlobalDayNightManager::FadeInDayNight(float FadeTime, float FadeVolume)
{
    if (DayNightAudio && !DayNightAudio->IsPlaying())
    {
        DayNightAudio->FadeIn(FadeTime, 1.f);
    }
}
