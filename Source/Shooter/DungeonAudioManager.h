// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonAudioManager.generated.h"

class UBoxComponent;
class UAudioComponent;
class USoundBase;
class AGlobalDayNightManager; 
class AShooterCharacter;

UCLASS()
class SHOOTER_API ADungeonAudioManager : public AActor
{
	GENERATED_BODY()
    
public:
	ADungeonAudioManager();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDungeonBeginOverlap(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult & SweepResult);

	UFUNCTION()
	void OnDungeonEndOverlap(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* DungeonTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* DungeonAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundBase* DungeonSound;

	// Reference to the global day-night manager (assigned in Editor or via code)
	UPROPERTY(EditAnywhere, Category="References")
	AGlobalDayNightManager* GlobalManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	float FadeTime;
};
