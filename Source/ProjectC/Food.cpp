// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/AssetData.h"
// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	if (IsGeneratingBlueprint == true)
	{
		GetActortFromFolder("/Game/Blueprints/FoodTypes", FoodLoadedArray);
			for (int i = 0; i <= CountOfGeneratingFood; i++)
			{
				GenerateFood(GetRandomFoodType());
				UE_LOG(LogTemp, Error, TEXT("Begin Play loop is working"));
			}
	}
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			switch (id)
			{
				case 1:
					Snake->AddSnakeElement(1);
				
					Snake->Hunger(HungerTime);
					this->GenerateFood(this);
					break;
				case 2:
					Snake->AddSnakeElement(2);
					Snake->Hunger(HungerTime);
					this->GenerateFood(this);
					break;
				case 3:
					Snake->RemoveSnakeElement(1);
					Snake->Hunger(HungerTime);
					this->GenerateFood(this);
					break;
				case 4:
					Snake->RemoveSnakeElement(2);
					Snake->Hunger(HungerTime);
					this->GenerateFood(this);
					break;
				case 5:
					Snake->SetActorTickInterval(Snake->MovementSpeed * 0.7);
					
					Snake->Hunger(HungerTime);
					this->GenerateFood(this);
					
			}
			;
		}
	}
}




void AFood::GenerateFood(AFood* WhichFoodType)
{
	int iterator = 0;

	bool flag = false;
	FVector NewCoords;

	const float radius = 32.0f;
	ETraceTypeQuery sphereTraceQuery = ETraceTypeQuery::TraceTypeQuery1;
	const TArray<AActor*> ActorsToIgnore;
	const float drawTime = 5.0f;
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	
	
	while (iterator < 150 && !flag)
	{
		NewCoords = FVector(FMath::RandRange(-1000, 1000), FMath::RandRange(-1000, 1000), 20);
		TArray<FHitResult> HitResults;

		UKismetSystemLibrary::SphereTraceMulti(World, NewCoords, NewCoords, radius, sphereTraceQuery, false,
			ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResults, true,
			FLinearColor::Green, FLinearColor::Red, drawTime);

		if (HitResults.Num() == 0)
		{
			if (this->id == 0)
			{
				UClass* FoodClass = WhichFoodType->GetClass();
				AFood* SpawningFood = World->SpawnActor<AFood>(FoodClass,NewCoords,{0,0,0},SpawnParams);
				UE_LOG(LogTemp, Error, TEXT("Spawned"));
			}
			else
			{
				this->SetActorLocation(NewCoords);
				UE_LOG(LogTemp, Error, TEXT("Location Changer"));

			}
			flag = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Hit resutl ponos"));
		}
		iterator++;

	}
}

AFood* AFood::GetRandomFoodType()
{
	AFood* GeneratingFood = FoodLoadedArray[FMath::RandRange(0, FoodLoadedArray.Num() - 1)];
	UE_LOG(LogTemp, Warning, TEXT("Name of Food: %s"), *GeneratingFood->GetName());
	return GeneratingFood;
}


void AFood::GetActortFromFolder(const FString& WhichFolder, TArray<AFood*>& OutClasses)
{

	// Получаем доступ к AssetRegistryModule
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	// Получаем доступ к IAssetRegistry классу для выполнения запросов к ассетам
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	// Создаем фильтр для ассетов в указанной папке

	FARFilter AssetFilter;
	FName FolderPathName = FName(*WhichFolder);
	AssetFilter.PackagePaths.Add(FolderPathName);
	AssetFilter.bRecursivePaths = true;
	AssetFilter.bRecursiveClasses = true;

	// Запрашиваем ассеты с помощью фильтра
	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssets(AssetFilter, AssetDataList);




	// Iterate over the assets and load the classes
	for (const FAssetData& AssetData : AssetDataList)
	{
		if (UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.GetAsset()))
		{
			if (Blueprint->GeneratedClass)
			{
				AFood* DefaultObject = Cast<AFood>(Blueprint->GeneratedClass->GetDefaultObject());
				if (DefaultObject)
				{
					OutClasses.Add(DefaultObject);
					

					// Вывод длины OutClasses после добавления элемента
				

				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("DefaultObject cast failed for Blueprint: %s"), *Blueprint->GetName());
				}
			}

		}
		
	}
}