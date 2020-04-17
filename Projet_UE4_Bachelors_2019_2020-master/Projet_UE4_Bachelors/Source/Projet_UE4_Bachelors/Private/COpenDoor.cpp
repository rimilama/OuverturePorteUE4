// Fill out your copyright notice in the Description page of Project Settings.


#include "COpenDoor.h"




ACOpenDoor::ACOpenDoor() {
	TriggerBox = NULL;
	MassToOpen = 110.0f;
}

void ACOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnActorBeginOverlap.AddDynamic(this, &ACOpenDoor::TriggerChange);
	TriggerBox->OnActorEndOverlap.AddDynamic(this, &ACOpenDoor::TriggerChange);
	// ...

}

float ACOpenDoor::SetPoidsTotal()
{
	float mass = 0.0f;
	TArray<AActor*> TabObjet;
	TArray<UMeshComponent*> TabMesh;
	TriggerBox->GetOverlappingActors(TabObjet);
	for (int i = 0; i < TabObjet.Num(); i++) {
		TabObjet[i]->GetComponents<UMeshComponent>(TabMesh);
		for (UMeshComponent* Mesh : TabMesh) {
			mass += Mesh->GetMass();
		}
	}
	//UE_Log();
	return mass;
}

void ACOpenDoor::TriggerChange(AActor* current, AActor* other)
{
	if (MassToOpen >= SetPoidsTotal()) {
		//Play
	}
	else {
		//Reverse
	}
}

