// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

#define OUT

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::PullTrigger()
{
	// Play MuzzleFlash
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	// Play SFX
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	
	// If something gets hit...
	if(GunTrace(Hit, ShotDirection))
	{
		// Spawn Hit FX pointing back to the line trace start
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.Location, ShotDirection.Rotation());

		// Play SFX at location
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Hit.Location, ShotDirection.Rotation());

		AActor* ActorHit = Hit.GetActor();
		if(ActorHit != nullptr)
		{
			AController* OwnerController = GetOwnerController();
			if(!OwnerController) return;
			
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			ActorHit->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}


	
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if(!OwnerController) return false;

	// Get Player Viewpoint (start of line trace)
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(OUT Location, OUT Rotation);

	// Calculate end of line trace
	const FVector End = Location + Rotation.Vector() * MaxRange;

	// Setup stuff to ignore
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	ShotDirection = -Rotation.Vector();
	
	// Line Trace
	return GetWorld()->LineTraceSingleByChannel(OUT Hit, Location, End, ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	// Setup For line trace
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(!OwnerPawn) return nullptr;
	
	return OwnerPawn->GetController();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

