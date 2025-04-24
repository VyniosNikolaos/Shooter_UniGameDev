#include "FogManager.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ExponentialHeightFogComponent.h"

// Sets default values
AFogManager::AFogManager()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	MinHeight = -1000.0f;
	MaxHeight = 1500.0f;
	MinFogDensity = 0.01f;
	MaxFogDensity = 0.5f;
}

// Called when the game starts or when spawned
void AFogManager::BeginPlay()
{
	Super::BeginPlay();

	// Find the player character
	PlayerCharacter = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Log a warning if FogActor is not set
	if (!FogActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("FogActor is not set in FogManager. Please assign it in the editor."));
	}
}

// Called every frame
void AFogManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ensure FogActor and PlayerCharacter are valid
	if (FogActor && PlayerCharacter)
	{
		// Get the player's height (Z-axis location)
		float PlayerHeight = PlayerCharacter->GetActorLocation().Z;

		// Adjust height normalization to include MinHeight
		float NormalizedHeight = FMath::Clamp((PlayerHeight - MinHeight) / (MaxHeight - MinHeight), 0.0f, 1.0f);

		// Calculate fog density
		float FogDensity = FMath::Lerp(MinFogDensity, MaxFogDensity, NormalizedHeight);

		// Update fog density dynamically
		UExponentialHeightFogComponent* FogComponent = FogActor->FindComponentByClass<UExponentialHeightFogComponent>();
		if (FogComponent)
		{
			FogComponent->SetFogDensity(FogDensity);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FogComponent not found on the FogActor!"));
		}
	}
}

