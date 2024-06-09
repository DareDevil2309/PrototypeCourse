// Fill out your copyright notice in the Description page of Project Settings.


#include "HighlighterComponent.h"


// Sets default values for this component's properties
UHighlighterComponent::UHighlighterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	zOffset = -70;

	ownerRef = Cast<ACombatant>(this->GetOwner());

	highlighterMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Highlighter Mesh"));
	highlighterMesh->Mobility = EComponentMobility::Movable;
	highlighterMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_torus(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (StaticMeshOb_torus.Object)
		highlighterMesh->SetStaticMesh(StaticMeshOb_torus.Object);

	highlighterMesh->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	
}


// Called when the game starts
void UHighlighterComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UHighlighterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ownerRef->Target)
	{
		this->SetWorldLocation(ownerRef->Target->GetActorLocation()+FVector(0,0, zOffset));
	}
	else 
	{
		this->SetWorldLocation(FVector(0, 0, -10000));
	}
}
