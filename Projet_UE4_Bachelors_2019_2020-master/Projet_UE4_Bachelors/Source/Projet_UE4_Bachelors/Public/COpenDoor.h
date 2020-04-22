// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/MeshComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/TimelineComponent.h"
#include "COpenDoor.generated.h"


class UTimelineComponent;
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
	
	UFUNCTION()
	void TriggerChange(AActor* current, AActor* other);

	UTimelineComponent* MyTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveDoor;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere)
	USoundBase* LockSound;
	
	float RotateValue;
	float TimelineValue;
	float CurveFloatValue;
	bool Fermeture;

	UFUNCTION()
	void ControleDoor();

private:
	float SetPoidsTotal();

	
};
