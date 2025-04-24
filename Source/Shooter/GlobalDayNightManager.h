#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlobalDayNightManager.generated.h"

class ADirectionalLight;
class UAudioComponent;
class USoundBase;


UCLASS()
class SHOOTER_API AGlobalDayNightManager : public AActor
{
    GENERATED_BODY()

public:
    AGlobalDayNightManager();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Called by other managers to fade out or in the day–night track
    UFUNCTION(BlueprintCallable, Category="DayNight")
    void FadeOutDayNight(float FadeTime, float FadeVolumeEnd);

    UFUNCTION(BlueprintCallable, Category="DayNight")
    void FadeInDayNight(float FadeTime, float FadeVolume);

    void UpdateDayNightAudio();

    bool bIsOutside;



private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky", meta = (AllowPrivateAccess = "true"))
    AActor* SunSkySphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky", meta = (AllowPrivateAccess = "true"))
    ADirectionalLight* SunLightSource;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky", meta = (AllowPrivateAccess = "true"))
    float SunTurnRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
    USoundBase* DaySound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
    USoundBase* NightSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
    UAudioComponent* DayNightAudio;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky", meta = (AllowPrivateAccess = "true"))
    float NightThresholdPitch;


    
};
