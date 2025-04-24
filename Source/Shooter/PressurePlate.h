// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

// Forward Declarations
class UBoxComponent;
class USoundBase;
class ACameraActor;
class ABurningFireEmitter;

UCLASS()
class SHOOTER_API APressurePlate : public AActor
{
	GENERATED_BODY()

public:
	APressurePlate();

protected:
	virtual void BeginPlay() override;

	//  Called when overlapping 
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	/* //  Called when End Overlapping
	UFUNCTION()
	void OnBoxOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex); */

	//void PlayPressureTriggerSound();
	//void PlayPressureReleaseSound();

	bool bIsTriggered;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	//static mesh for the plate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plate Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PlateMesh;

	//collision box to detect pressure
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Plate Properties", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;

	// Sound played when plate is triggered
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plate Properties", meta = (AllowPrivateAccess = "true"))
	USoundBase* TriggeredSound;

	// Camera to switch to when activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plate Properties", meta = (AllowPrivateAccess = "true"))
	ACameraActor* FireEmitterCamera;

	// BurningFireEmitter class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plate Properties", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABurningFireEmitter> BurningFireEmitterClass;

	// Location where the BurningFireEmitter will spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plate Properties", meta = (AllowPrivateAccess = "true"))
	FVector FireEmitterSpawnOffset;

	void SwitchAwayFromPlayerCamera(APlayerController* PlayerController);
	
	// Switch back to player camera
	void SwitchBackToPlayerCamera(APlayerController* PlayerController);
};


