// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterExtinguisher.generated.h"

// Forward Declarations
class UBoxComponent;

UCLASS()
class SHOOTER_API AWaterExtinguisher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterExtinguisher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Handle overlap event
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Collision sphere
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Extinguisher", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;

};
