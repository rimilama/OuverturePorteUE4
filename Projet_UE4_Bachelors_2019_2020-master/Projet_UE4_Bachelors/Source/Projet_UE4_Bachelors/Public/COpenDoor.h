// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/MeshComponent.h"
#include "Engine/TriggerVolume.h"
#include "COpenDoor.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_UE4_BACHELORS_API ACOpenDoor : public AStaticMeshActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	ACOpenDoor();

	UPROPERTY(EditAnywhere)
	ATriggerVolume* TriggerBox;
	
	float MassToOpen;
	
	void TriggerChange(AActor*, AActor*);

	
private:
	float SetPoidsTotal();

	
};
