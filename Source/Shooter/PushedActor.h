// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushedActor.generated.h"

//Forward Declarations
class USoundBase;
class USphereComponent;

UCLASS()
class SHOOTER_API APushedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APushedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Flag to determine if the rock is being pushed
	//bool bIsBeingPushed;

	//  Called when overlapping 
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;


private:
	// The static mesh of the rock
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RockMesh;

	// the collision box for the character to collide with to push the rock
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionSphere;

	// Sound to play while the rock is moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	USoundBase* PushSound;

	
};
