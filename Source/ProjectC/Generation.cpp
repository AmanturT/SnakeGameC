// Fill out your copyright notice in the Description page of Project Settings.


#include "Generation.h"
#include "Obtacle.h"
#include "Food.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/AssetData.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
AGeneration::AGeneration()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeneration::BeginPlay()
{
	Super::BeginPlay();
    GetActortFromFolder("/Game/Blueprints/Obtacles/SingleObtacles", SingleObtacles);
    GenerateObtacles(SingleObtacles, 4);
}

// Called every frame
void AGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeneration::GetActortFromFolder(const FString& WhichFolder, TArray<AObtacle*>& OutClasses)
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
    UE_LOG(LogTemp, Warning, TEXT("Number of assets found: %d"), AssetDataList.Num());
   


    // Iterate over the assets and load the classes
    for (const FAssetData& AssetData : AssetDataList)
    {
        if (UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.GetAsset()))
        {
            if (Blueprint->GeneratedClass)
            {
                AObtacle* DefaultObject = Cast<AObtacle>(Blueprint->GeneratedClass->GetDefaultObject());
                if (DefaultObject)
                {
                    OutClasses.Add(DefaultObject);
                    UE_LOG(LogTemp, Error, TEXT("Found Blueprint Class: %s"), *DefaultObject->GetName());

                    // Вывод длины OutClasses после добавления элемента
                    UE_LOG(LogTemp, Warning, TEXT("OutClasses length: %d"), SingleObtacles.Num());
                    
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("DefaultObject cast failed for Blueprint: %s"), *Blueprint->GetName());
                }
            }
            
        }
        UE_LOG(LogTemp, Error, TEXT("Loop working!!!"));
    }
}

void AGeneration::GenerateObtacles(TArray<AObtacle*> ArrayOfObtacles, int count)
{
    int iterator = 0;
    bool flag = false;
    FVector NewCoords;
    const float radius = 32.0f;
    ETraceTypeQuery sphereTraceQuery = ETraceTypeQuery::TraceTypeQuery1;
    const TArray<AActor*> ActorsToIgnore;
    const float drawTime = 5.0f;
    FActorSpawnParameters SpawnParams;
    AObtacle* GeneratingObtacle = nullptr;
    UWorld* World = GetWorld();
    FRotator NewRotation;
    // Логирование длины ArrayOfObtacles до начала генерации
    UE_LOG(LogTemp, Warning, TEXT("Initial length of ArrayOfObtacles: %d"), ArrayOfObtacles.Num());

    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("World is null"));
        return;
    }

    for (int i = 0; i < count; i++)
    {
        iterator = 0;
        flag = false;

        while (iterator < 150 && !flag)
        {
            NewCoords = FVector(FMath::RandRange(-1000, 1000), FMath::RandRange(-1000, 1000), 20);
            NewRotation = FRotator(0, FMath::RandRange(0, 360), 0);
            TArray<FHitResult> HitResults;

            UKismetSystemLibrary::SphereTraceMulti(World, NewCoords, NewCoords, radius, sphereTraceQuery, false,
                ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResults, true,
                FLinearColor::Green, FLinearColor::Red, drawTime);

            if (HitResults.Num() == 0)
            {
                if (ArrayOfObtacles.Num() != 0)
                {
                    GeneratingObtacle = ArrayOfObtacles[FMath::RandRange(0, ArrayOfObtacles.Num() - 1)];

                    // Проверка на случай, если GeneratingObtacle равен nullptr
                    if (!GeneratingObtacle)
                    {
                        UE_LOG(LogTemp, Error, TEXT("GeneratingObtacle is null before spawning"));
                        continue;
                    }

                    // Попытка создать новый объект
                    AObtacle* SpawnedObtacle = GetWorld()->SpawnActor<AObtacle>(GeneratingObtacle->GetClass(), NewCoords,NewRotation, SpawnParams);

                    // Проверка на случай, если SpawnedObtacle равен nullptr
                    if (!SpawnedObtacle)
                    {
                        UE_LOG(LogTemp, Error, TEXT("Failed to spawn AObtacle"));
                        continue;
                    }

                    // Логирование имени GeneratingObtacle
                    UE_LOG(LogTemp, Warning, TEXT("Spawned Obtacle: %s"), *SpawnedObtacle->GetName());

                    flag = true;

                    // Логирование длины ArrayOfObtacles после добавления нового препятствия
                    UE_LOG(LogTemp, Warning, TEXT("Length of ArrayOfObtacles after spawning: %d"), ArrayOfObtacles.Num());
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("ArrayOfObtacles is empty"));
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Hit results detected in trace"));
            }
            iterator++;
        }
    }

    // Логирование длины ArrayOfObtacles после завершения генерации
    UE_LOG(LogTemp, Warning, TEXT("Final length of ArrayOfObtacles: %d"), ArrayOfObtacles.Num());
}


