// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHairWidget.h"
#include "Components/Image.h"
#include <Kismet/GameplayStatics.h>
#include <Components/CanvasPanel.h>
#include "Engine/LocalPlayer.h"
#include <MiniCyphers/MiniCyphersPlayerController.h>
#include "../Character/MiniCyphersCharacter.h"

void UCrossHairWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCrossHairWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    FVector2D AimScreenPosition = GetAimScreenPosition(AimPoint);
    FVector2D NewScreenPosition = GetScreenMousePosition();

    FVector2D NewPosition = FVector2D(AimScreenPosition.X, NewScreenPosition.Y);
    FWidgetTransform ImageTransform;
    ImageTransform.Translation = NewPosition;

    AimPoint->SetRenderTransform(ImageTransform);
}

FVector2D UCrossHairWidget::GetScreenMousePosition()
{
    FVector2D WorldMousePosition;

    APlayerController* PlayerController = GetOwningPlayer();
    if (PlayerController == nullptr)
        return FVector2D::ZeroVector;

    AMiniCyphersPlayerController* Controller = Cast<AMiniCyphersPlayerController>(PlayerController);
    if (Controller == nullptr)
        return FVector2D::ZeroVector;

    AMiniCyphersCharacter* Character = Controller->GetCharacter();
    if (Character)
        return FVector2D::ZeroVector;
    
    FVector TargetLocation = Character->GetTargetPosition(ECollisionChannel::ECC_EngineTraceChannel1, 3500.0f);

    FVector2D ScreenPosition;
    if (PlayerController->ProjectWorldLocationToScreen(TargetLocation, ScreenPosition))
    {
        WorldMousePosition.X = ScreenPosition.X;
        WorldMousePosition.Y = ScreenPosition.Y;
    }
    return WorldMousePosition;
}

FVector2D UCrossHairWidget::GetAimScreenPosition(UImage* AimImage)
{
    if (!AimImage) return FVector2D::ZeroVector;

    // �θ� ������ Canvas Panel�� ã���ϴ�.
    UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(AimImage->GetParent());
    if (!CanvasPanel) return FVector2D::ZeroVector;

    // MyImage�� ���� ���� ��ġ�� �����ɴϴ�.
    FVector2D LocalPosition = AimImage->GetCachedGeometry().LocalToAbsolute(FVector2D::ZeroVector);

    // Canvas Panel�� ���� ���� ��ġ�� �����ɴϴ�.
    FVector2D CanvasPosition = CanvasPanel->GetCachedGeometry().LocalToAbsolute(FVector2D::ZeroVector);

    // MyImage�� ȭ�� ���� ��ġ�� ����մϴ�.
    FVector2D ScreenPosition = LocalPosition + CanvasPosition;

    return ScreenPosition;
}
