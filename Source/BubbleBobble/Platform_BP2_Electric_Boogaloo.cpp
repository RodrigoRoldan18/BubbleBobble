// Fill out your copyright notice in the Description page of Project Settings.

#include "Platform_BP2_Electric_Boogaloo.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlatform_BP2_Electric_Boogaloo::APlatform_BP2_Electric_Boogaloo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PlatformBase"));
	}	

	sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	sprite->SetupAttachment(RootComponent);

	colBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	colBox->SetRelativeLocation(FVector(0, 0, 280));
	colBox->SetRelativeScale3D(FVector(4.25, 1.0, 0.5));
	colBox->OnComponentBeginOverlap.AddDynamic(this, &APlatform_BP2_Electric_Boogaloo::OnOverlapBegin);
	colBox->OnComponentEndOverlap.AddDynamic(this, &APlatform_BP2_Electric_Boogaloo::OnOverlapEnd);
	colBox->SetupAttachment(sprite);

}

// Called when the game starts or when spawned
void APlatform_BP2_Electric_Boogaloo::BeginPlay()
{
	Super::BeginPlay();

	switch (isprite)
	{
	case 0:
		sprite->SetSprite(sprite1);
		break;
	case 1:
		sprite->SetSprite(sprite2);
		break;
	case 2:
		sprite->SetSprite(sprite3);
		break;
	case 3:
		sprite->SetSprite(sprite4);
		break;
	case 4:
		sprite->SetSprite(sprite5);
		break;
	case 5:
		sprite->SetSprite(sprite6);
		break;
	case 6:
		sprite->SetSprite(sprite7);
		break;
	case 7:
		sprite->SetSprite(sprite8);
		break;
	case 8:
		sprite->SetSprite(sprite9);
		break;
	case 9:
		sprite->SetSprite(sprite10);
		break;
	}

	sprite->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	sprite->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	sprite->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Block);
}

void APlatform_BP2_Electric_Boogaloo::Activate_Floor_Player()
{
	sprite->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

void APlatform_BP2_Electric_Boogaloo::Activate_Floor_Enemy()
{
	sprite->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}

void APlatform_BP2_Electric_Boogaloo::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		if (colBox->GetComponentLocation().Z < OtherActor->GetRootComponent()->GetComponentLocation().Z) // Coming from above
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Player has collided with the platform FROM ABOVE");
			sprite->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Player has collided with the platform FROM BELLOW");
			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				World->GetTimerManager().SetTimer(loopTimeHandle, this, &APlatform_BP2_Electric_Boogaloo::Activate_Floor_Player, 0.3f, false);
			}			
		}
	}
	else
	{
		if (OtherActor->ActorHasTag("Enemy"))
		{
			if (colBox->GetComponentLocation().Z < OtherActor->GetRootComponent()->GetComponentLocation().Z)
			{
				sprite->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
			}
			else
			{
				UWorld* const World = GetWorld();
				if (World != NULL)
				{
					World->GetTimerManager().SetTimer(loopTimeHandle, this, &APlatform_BP2_Electric_Boogaloo::Activate_Floor_Enemy, 0.3f, false);
				}				
			}
		}
	}
}

void APlatform_BP2_Electric_Boogaloo::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		sprite->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
	else if (OtherActor->ActorHasTag("Enemy"))
	{
		sprite->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	}
}

// Called every frame
void APlatform_BP2_Electric_Boogaloo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UWorld* const World = GetWorld();
	//if (World != NULL)
	//{
	//	//if platform is higher than the player then the platform will ignore so that the player can go through
	//	if (colBox->GetComponentLocation().Z > UGameplayStatics::GetPlayerCharacter(World, 0)->GetCapsuleComponent()->GetComponentLocation().Z)
	//	{
	//		if (sprite->GetCollisionResponseToChannel(ECC_Pawn) != ECR_Ignore)
	//		{
	//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Platform higher than the player");
	//			sprite->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	//		}
	//		//THE PROBLEM IS HERE!!
	//	}
	//}	
}

