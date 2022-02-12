// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = GetOwner()->GetActorRotation();
	FinalRotation = InitialRotation;
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT(" The OpenDoor Component attached to %s has no PressurePlate set!"), *GetOwner()->GetName());
	}
	
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
		
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
	}else
	{ 
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime){
	FinalRotation.Yaw = FMath::FInterpTo(FinalRotation.Yaw,InitialRotation.Yaw + 90.f,DeltaTime, 2);
	GetOwner()->SetActorRotation(FinalRotation);
}
void UOpenDoor::CloseDoor(float DeltaTime){
	FinalRotation.Yaw = FMath::FInterpTo(FinalRotation.Yaw,InitialRotation.Yaw,DeltaTime, 3);
	GetOwner()->SetActorRotation(FinalRotation);
}


