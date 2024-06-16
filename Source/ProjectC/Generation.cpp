// Fill out your copyright notice in the Description page of Project Settings.


#include "Generation.h"
#include "Obtacle.h"
#include "Food.h"

#include "SnakeBase.h"
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
    GetActortFromFolder("/Game/Blueprints/Obtacles/Structures", Structures);
    GetActortFromFolder("/Game/Blueprints/GameFields", Fields);
    
    


    SpawnNewMapSegment(FVector(0,0,0));
}

// Called every frame
void AGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (Snake && CurrentMapSegment)
    {
        CheckSnakePosition();
    }
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
                    

                    
                   
                    
                }
               
            }
            
        }
       
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

                  

                    // Попытка создать новый объект
                    AObtacle* SpawnedObtacle = GetWorld()->SpawnActor<AObtacle>(GeneratingObtacle->GetClass(), NewCoords,NewRotation, SpawnParams);

                    // Проверка на случай, если SpawnedObtacle равен nullptr
                    
                    // Логирование имени GeneratingObtacle
                  

                    flag = true;

                    // Логирование длины ArrayOfObtacles после добавления нового препятствия
                    
                }
                
            }
          
            iterator++;
        }
    }

}

void AGeneration::SpawnNewMapSegment(FVector SpawnLocation)
{
    
   

    // Вычисляем случайное число от 0 до 99
    int32 RandomNumber = FMath::RandRange(0, 99);
    FActorSpawnParameters SpawnParams;
    // Выбираем элемент массива Fields в зависимости от случайного числа
    AObtacle* SpawnedObstacle = nullptr;
    if (Fields.Num() != 0)
    {
        SpawnedObstacle = Fields[0];

    

       
        AObtacle* SpawnedObject = GetWorld()->SpawnActor<AObtacle>(SpawnedObstacle->GetClass(), SpawnLocation, FRotator::ZeroRotator, SpawnParams);

        if(SpawnedObject)
        {
            UE_LOG(LogTemp,Error,TEXT("sdawerqwtfgrmigsrmnvg9[gbyjmnuwbh"))
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("SpawnNewMapSegment: Failed to spawn obstacle"));
        }

    }
   

  
 
}

void AGeneration::CheckSnakePosition()
{
    FVector SnakeLocation = Snake->GetActorLocation();
    FVector SegmentLocation = CurrentMapSegment->GetActorLocation();

    float DistanceToLeft = FVector::Dist(SnakeLocation, SegmentLocation - FVector(MapSegmentLength / 2, 0, 0));
    float DistanceToRight = FVector::Dist(SnakeLocation, SegmentLocation + FVector(MapSegmentLength / 2, 0, 0));
    float DistanceToTop = FVector::Dist(SnakeLocation, SegmentLocation + FVector(0, MapSegmentLength / 2, 0));
    float DistanceToBottom = FVector::Dist(SnakeLocation, SegmentLocation - FVector(0, MapSegmentLength / 2, 0));

    if (DistanceToLeft <= 5000.0f)
    {
        FVector NewSegmentLocation = SegmentLocation - FVector(MapSegmentLength, 0, 0);
        SpawnNewMapSegment(NewSegmentLocation);
    }
    else if (DistanceToRight <= 5000.0f)
    {
        FVector NewSegmentLocation = SegmentLocation + FVector(MapSegmentLength, 0, 0);
        SpawnNewMapSegment(NewSegmentLocation);
    }
    else if (DistanceToTop <= 5000.0f)
    {
        FVector NewSegmentLocation = SegmentLocation + FVector(0, MapSegmentLength, 0);
        SpawnNewMapSegment(NewSegmentLocation);
    }
    else if (DistanceToBottom <= 5000.0f)
    {
        FVector NewSegmentLocation = SegmentLocation - FVector(0, MapSegmentLength, 0);
        SpawnNewMapSegment(NewSegmentLocation);
    }
}


