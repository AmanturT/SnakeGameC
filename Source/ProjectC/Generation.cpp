// Fill out your copyright notice in the Description page of Project Settings.


#include "Generation.h"
#include "Obtacle.h"
#include "Food.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/AssetData.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SnakeElementBase.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeBase.h"
#include "Food.h"
// Sets default values
AGeneration::AGeneration()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //  LastSpawnedSegmentEnd = SpawnLocation;  // Update the position of the last segment's end
   
  
}

// Called when the game starts or when spawned
void AGeneration::BeginPlay()
{
	Super::BeginPlay();
    GetActortFromFolder("/Game/Blueprints/Obtacles/SingleObtacles", SingleObtacles);
   
    GetActortFromFolder("/Game/Blueprints/Segments", GameFieldSegments);
    SpawnNewSegment(FVector(0,0,-75));
    FoodClass = Cast<AFood>(UGameplayStatics::GetActorOfClass(GetWorld(), AFood::StaticClass()));
   
}

// Called every frame
void AGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
    if (!SnakeBaseClass)
    {
        FindSnake();

        return;
    }
    


   
        
 }
   
void AGeneration::GetActortFromFolder(const FString& WhichFolder, TArray<AObtacle*>& OutClasses)
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

    FARFilter AssetFilter;
    FName FolderPathName = FName(*WhichFolder);
    AssetFilter.PackagePaths.Add(FolderPathName);
    AssetFilter.bRecursivePaths = true;
    AssetFilter.bRecursiveClasses = true;

    TArray<FAssetData> AssetDataList;
    AssetRegistry.GetAssets(AssetFilter, AssetDataList);

    FString AssetCountMessage = FString::Printf(TEXT("Number of assets found: %d"), AssetDataList.Num());
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, AssetCountMessage);
    }

    for (const FAssetData& AssetData : AssetDataList)
    {
        UObject* Asset = AssetData.GetAsset();
        if (Asset && Asset->IsA<UBlueprint>())
        {
            UBlueprint* BlueprintFromFolder = Cast<UBlueprint>(Asset);
            if (BlueprintFromFolder)
            {
                if (BlueprintFromFolder->GeneratedClass)
                {
                    AObtacle* DefaultObject = Cast<AObtacle>(BlueprintFromFolder->GeneratedClass->GetDefaultObject());
                    if (DefaultObject)
                    {
                        OutClasses.Add(DefaultObject);
                        FString FoundClassMessage = FString::Printf(TEXT("Found Blueprint Class: %s"), *DefaultObject->GetName());
                        if (GEngine)
                        {
                            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FoundClassMessage);
                        }

                        FString OutClassesLengthMessage = FString::Printf(TEXT("OutClasses length: %d"), OutClasses.Num());
                        if (GEngine)
                        {
                            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, OutClassesLengthMessage);
                        }
                    }
                    else
                    {
                        FString DefaultObjectCastFailedMessage = FString::Printf(TEXT("DefaultObject cast failed for Blueprint: %s"), *BlueprintFromFolder->GetName());
                        if (GEngine)
                        {
                            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DefaultObjectCastFailedMessage);
                        }
                    }
                }
                else
                {
                    if (GEngine)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("GeneratedClass is null"));
                    }
                }
            }
            else
            {
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("BlueprintFromFolder is null"));
                }
            }
        }
        else
        {
            FString AssetTypeMessage = FString::Printf(TEXT("Asset is not a UBlueprint: %s"), *Asset->GetClass()->GetName());
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, AssetTypeMessage);
            }
        }

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Loop working!!!"));
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
            NewCoords = FVector(FMath::RandRange(-2000 + LastSpawnedSegmentEnd.X, 2000 + LastSpawnedSegmentEnd.X), FMath::RandRange(-2000 +LastSpawnedSegmentEnd.Y, 2000 + LastSpawnedSegmentEnd.Y), 20);
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

                 
                    if (!GeneratingObtacle)
                    {
                        UE_LOG(LogTemp, Error, TEXT("GeneratingObtacle is null before spawning"));
                        continue;
                    }

                    
                    AObtacle* SpawnedObtacle = GetWorld()->SpawnActor<AObtacle>(GeneratingObtacle->GetClass(), NewCoords,NewRotation, SpawnParams);

                    if (!SpawnedObtacle)
                    {
                        UE_LOG(LogTemp, Error, TEXT("Failed to spawn AObtacle"));
                        continue;
                    }

                   
                    UE_LOG(LogTemp, Warning, TEXT("Spawned Obtacle: %s"), *SpawnedObtacle->GetName());

                    flag = true;

                    
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

  
    UE_LOG(LogTemp, Warning, TEXT("Final length of ArrayOfObtacles: %d"), ArrayOfObtacles.Num());
}

void AGeneration::SpawnNewSegment(FVector SpawnLocation)
{
    if (GameFieldSegments.Num() != 0)
    {
       
        AObtacle* SegmentToSpawn;
        SegmentToSpawn = GameFieldSegments[0];
        if (!SegmentToSpawn)
        {
            UE_LOG(LogTemp, Error, TEXT("GeneratingObtacle is null before spawning"));
            
        }
        FActorSpawnParameters SpawnParams;
        AObtacle* SpawnedSegment = GetWorld()->SpawnActor<AObtacle>(SegmentToSpawn->GetClass(), SpawnLocation, FRotator::ZeroRotator, SpawnParams);

        if (SpawnedSegment)
        {
            LastSpawnedSegmentEnd = SpawnLocation;  
            UE_LOG(LogTemp, Error, TEXT("Spawned %d"), GameFieldSegments.Num());
            GenerateObtacles(SingleObtacles, countOfSingleObtacles);
          
            if (FoodClass)
            {
                for (int i = 0; i <= CountOfGeneratingFood; i++)
                     {
                        FoodClass->GenerateFood(FoodClass->GetRandomFoodType());
                        UE_LOG(LogTemp, Error, TEXT("Begin Play loop is working"));
                     }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("FoodClass is null"));
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Segments !> 1 %d"), GameFieldSegments.Num());
    }
}

void AGeneration::CheckSnakeLocation()
{
    if (!SnakeBaseClass || SnakeBaseClass->SnakeElements.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("SnakeBaseClass is nullptr or SnakeElements is empty in CheckSnakeLocation"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("SnakeBaseClass is valid in CheckSnakeLocation"));

    FVector SnakeLocation = SnakeBaseClass->SnakeElements[0]->GetActorLocation();
    FVector PossibleNewLocations[4] = {
        LastSpawnedSegmentEnd + FVector(SegmentSize.X / 2, 0, 0),  // Right
        LastSpawnedSegmentEnd - FVector(SegmentSize.X / 2, 0, 0),  // Left
        LastSpawnedSegmentEnd + FVector(0, SegmentSize.Y / 2, 0),  // Top
        LastSpawnedSegmentEnd - FVector(0, SegmentSize.Y / 2, 0)   // Bottom
    };

    float Distances[4] = {
        FVector::Dist(SnakeLocation, PossibleNewLocations[0]),
        FVector::Dist(SnakeLocation, PossibleNewLocations[1]),
        FVector::Dist(SnakeLocation, PossibleNewLocations[2]),
        FVector::Dist(SnakeLocation, PossibleNewLocations[3])
    };

    float MinDistance = FLT_MAX;
    int MinIndex = -1;

    // Ќаходим минимальное значение и его индекс
    for (int i = 0; i < 4; i++)
    {
        if (Distances[i] < MinDistance)
        {
            MinDistance = Distances[i];
            MinIndex = i;
        }

        
        UE_LOG(LogTemp, Warning, TEXT("Distances[%d] = %f"), i, Distances[i]);
    }

   
    if (MinIndex != -1)
    {
        FVector NewSpawnLocation = LastSpawnedSegmentEnd;

        switch (MinIndex)
        {
        case 0: // Right
            NewSpawnLocation.X += 1000;
            break;
        case 1: // Left
            NewSpawnLocation.X -= 1000;
            break;
        case 2: // Top
            NewSpawnLocation.Y += 1000;
            break;
        case 3: // Bottom
            NewSpawnLocation.Y -= 1000;
            break;
        }

        SpawnNewSegment(NewSpawnLocation);
    }
  
}

void AGeneration::FindSnake()
{
    SnakeBaseClass = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeBase::StaticClass()));
    if (SnakeBaseClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Snake found!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Snake not found."));
    }
}


