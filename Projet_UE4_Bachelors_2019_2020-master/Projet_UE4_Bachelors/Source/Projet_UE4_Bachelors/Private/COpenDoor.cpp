// Fill out your copyright notice in the Description page of Project Settings.


#include "COpenDoor.h"
#include "Kismet/GameplayStatics.h"




ACOpenDoor::ACOpenDoor() {
	TriggerBox = NULL;
	MassToOpen = 110.0f;
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	LockSound = NULL;
	Fermeture = false;
}

void ACOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnActorBeginOverlap.AddDynamic(this, &ACOpenDoor::TriggerChange);
	TriggerBox->OnActorEndOverlap.AddDynamic(this, &ACOpenDoor::TriggerChange);
	// ...

	RotateValue = 1.0f;

	if (CurveDoor) {
		FOnTimelineFloat TimelineCallback;

		TimelineCallback.BindUFunction(this, FName("ControleDoor"));
		
		MyTimeline = NewObject<UTimelineComponent>(this, FName("DoorAnimation"));
		MyTimeline->AddInterpFloat(CurveDoor, TimelineCallback);
		MyTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
		MyTimeline->RegisterComponent();

	}

}


void ACOpenDoor::ControleDoor() {
	TimelineValue = MyTimeline->GetPlaybackPosition();
	CurveFloatValue = RotateValue * CurveDoor->GetFloatValue(TimelineValue);

	FQuat NewRotation = FQuat(FRotator(0.0f, CurveFloatValue, 0.0f));

	Door->SetRelativeRotation(NewRotation);
	if (TimelineValue >= 0.01f && TimelineValue <= 0.5f && Fermeture == true) {
		Fermeture = false;
		UE_LOG(LogTemp, Warning, TEXT("LE SON"));
		UGameplayStatics::PlaySoundAtLocation(this, LockSound, this->GetTransform().GetLocation());
	}
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
	return mass;
}

void ACOpenDoor::TriggerChange(AActor* current, AActor* other)
{
	if (MassToOpen <= SetPoidsTotal()) {
		Fermeture = false;
		MyTimeline->Play();
	}
	else {
		Fermeture = true;
		MyTimeline->Reverse();
	}
}

