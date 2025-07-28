// Fill out your copyright notice in the Description page of Project Settings.


#include "TulExperienceManagerComponent.h"

void UTulExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(FOnTulExperienceLoaded::FDelegate&& Delegate)
{
	// IsExperienceLoaded() ����
	if (IsExperienceLoaded())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		/**
		* �����, �����е��� Delegate ��ü�� �ڼ��� ���캸��, ���������� �ʿ��� �������� �޸� �Ҵ��س��´�
		* TArray<int> a = {1, 2, 3, 4};
		* delegate_type delegate = [a](){
		* return a.Num();
		* }
		* a�� delegate_type ���ο� new�� �Ҵ�Ǿ� �ִ�. ���� ����� ���߱� ���� Move�� ���� �ϴ� ���� ���� ����!
		*/
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}
