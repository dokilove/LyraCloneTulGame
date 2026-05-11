// Fill out your copyright notice in the Description page of Project Settings.


#include "TulActivatableWidget.h"

UTulActivatableWidget::UTulActivatableWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

TOptional<FUIInputConfig> UTulActivatableWidget::GetDesiredInputConfig() const
{
	// 앞서 정의 했던 WidgetInpuyMode에 따라, InputConfig을 설정해준다
	// - ECommonInputMode에 따라 Input의 흐름을 Game/Menu 혹은 둘다로 정하는 것이 가능하다
	// - 예로 들어, 우리가 Menu로 들어갔을 경우, 더이상 Game에 Input을 보내고 싶지 않을 경우 매우 용의하다.
	// - 상상해봐라, Menu모드인데 Space를 누르거나 MouseClick으로 총알이 나간다면.. .우리가 의도한 상황이 아닐 것이다
	switch (InputConfig)
	{
	case ETulWidgetInputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
	case ETulWidgetInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
	case ETulWidgetInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, GameMouseCaptureMode);
	case ETulWidgetInputMode::Default:
	default:
		return TOptional<FUIInputConfig>();
	}
}
