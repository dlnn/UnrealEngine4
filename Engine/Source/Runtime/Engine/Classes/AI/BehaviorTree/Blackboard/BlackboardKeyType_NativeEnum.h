// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BlackboardKeyType_NativeEnum.generated.h"

UCLASS(EditInlineNew, MinimalAPI)
class UBlackboardKeyType_NativeEnum : public UBlackboardKeyType
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category=Blackboard, EditDefaultsOnly)
	FString EnumName;

	UPROPERTY(Category=Blackboard, VisibleDefaultsOnly)
	bool bIsEnumNameValid;

	UPROPERTY()
	UEnum* EnumType;

	static uint8 GetValue(const uint8* RawData);
	static bool SetValue(uint8* RawData, uint8 Value);

	virtual FString DescribeValue(const uint8* RawData) const OVERRIDE;
	virtual FString DescribeSelf() const OVERRIDE;
	virtual bool IsAllowedByFilter(UBlackboardKeyType* FilterOb) const OVERRIDE;
	virtual EBlackboardCompare::Type Compare(const uint8* MemoryBlockA, const uint8* MemoryBlockB) const OVERRIDE;
	virtual bool TestArithmeticOperation(const uint8* MemoryBlock, EArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const OVERRIDE;
	virtual FString DescribeArithmeticParam(int32 IntValue, float FloatValue) const OVERRIDE;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) OVERRIDE;
#endif
};
