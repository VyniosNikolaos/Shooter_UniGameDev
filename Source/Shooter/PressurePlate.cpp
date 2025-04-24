#include "PressurePlate.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "PushedActor.h"
#include "Camera/CameraActor.h"
#include "ShooterPlayerController.h"
#include "BurningFireEmitter.h"

// Constructor
APressurePlate::APressurePlate()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize CollisionBox
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	// Set Collision Properties
	CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 20.0f));
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
}

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
}

// Overlap Event
void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
									bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	// Check if overlapping actor is player or PushedActor
	AShooterCharacter* PlayerCharacter = Cast<AShooterCharacter>(OtherActor);
	APushedActor* PushedActor = Cast<APushedActor>(OtherActor);
	
	if (PlayerCharacter || OtherActor->ActorHasTag("PushedActor") || PushedActor)
	{
		// Play clicking sound
		if (TriggeredSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, TriggeredSound, GetActorLocation());
		}
		bIsTriggered = true;
	}

	if (OtherActor->ActorHasTag("PushedActor") || PushedActor)
	{

		// Switch the camera if FireEmitterCamera is set
		if (FireEmitterCamera)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
			{
				// Switch to FireEmitterCamera
				PlayerController->SetViewTargetWithBlend(FireEmitterCamera, 2.0f, EViewTargetBlendFunction::VTBlend_Cubic);

				// Freeze the player (disable input)
				//AShooterCharacter* PlayerShooterCharacter = Cast<AShooterCharacter>(PlayerController->GetPawn());
				if (PlayerCharacter)
				{
					PlayerCharacter->DisableInput(PlayerController);
				}

				// Delay the fire emitter spawn
				FTimerHandle SpawnFireEmitterHandle;
				GetWorldTimerManager().SetTimer(SpawnFireEmitterHandle, FTimerDelegate::CreateLambda([this]()
				{
					if (BurningFireEmitterClass)
					{
						FVector SpawnLocation = GetActorLocation() + FireEmitterSpawnOffset;
						FRotator SpawnRotation = FRotator::ZeroRotator;

						// Spawn the emitter
						ABurningFireEmitter* SpawnedEmitter = GetWorld()->SpawnActor<ABurningFireEmitter>(
							BurningFireEmitterClass, SpawnLocation, SpawnRotation);
					}
				}), 3.0f, false); // Delay of 3 seconds (1 second after camera blend completes)

				// Delay to switch back to the player camera
				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this, PlayerController]()
				{SwitchBackToPlayerCamera(PlayerController); }), 5.0f, false); // 2 seconds
			}
		}
	}
}

void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APressurePlate::SwitchAwayFromPlayerCamera(APlayerController* PlayerController)
{
}

void APressurePlate::SwitchBackToPlayerCamera(APlayerController* PlayerController)
{
	if (PlayerController)
	{
		// Switch back to the player camera
		PlayerController->SetViewTargetWithBlend(PlayerController->GetPawn(), 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);

		// Re-enable input
		AShooterCharacter* PlayerCharacter = Cast<AShooterCharacter>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			PlayerCharacter->EnableInput(PlayerController);
		}
	}
}