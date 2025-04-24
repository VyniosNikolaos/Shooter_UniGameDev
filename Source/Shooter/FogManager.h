// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/ExponentialHeightFog.h"
#include "GameFramework/Actor.h"
#include "FogManager.generated.h"

//Forward Declarations
class AShooterCharacter;

UCLASS()
class SHOOTER_API AFogManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFogManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Reference to the fog actor in the scene
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	AExponentialHeightFog* FogActor;

	// Reference to the ShooterCharacter
	UPROPERTY(BlueprintReadOnly, Category = "Fog")
	AShooterCharacter* PlayerCharacter;

	// Maximum height for fog density adjustment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float MinHeight;
	
	// Maximum height for fog density adjustment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float MaxHeight;

	// Minimum fog density
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float MinFogDensity;

	// Maximum fog density
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float MaxFogDensity;
};
