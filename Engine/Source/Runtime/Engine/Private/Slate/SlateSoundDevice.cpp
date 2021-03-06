// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "EnginePrivate.h"
#include "ActiveSound.h"
#include "AudioDevice.h"
#include "Slate/SlateSoundDevice.h"
#include "Sound/SoundBase.h"
#include "Sound/SlateSound.h"

DEFINE_LOG_CATEGORY_STATIC(LogSlateSoundDevice, Log, All);

void FSlateSoundDevice::PlaySound(const FSlateSound& Sound, int32 UserIndex) const
{
	if( GEngine && Sound.GetResourceObject() != nullptr )
	{
		FAudioDevice* const AudioDevice = GEngine->GetActiveAudioDevice();
		if(AudioDevice)
		{
			UObject* const Object = Sound.GetResourceObject();
			USoundBase* const SoundResource = Cast<USoundBase>(Object);
			if(SoundResource)
			{
				FActiveSound NewActiveSound;
				NewActiveSound.Sound = SoundResource;
				NewActiveSound.bIsUISound = true;
				NewActiveSound.UserIndex = UserIndex;

				AudioDevice->AddNewActiveSound(NewActiveSound);
			}
			else if(Object)
			{
				// An Object but no SoundResource means that the FSlateSound is holding an invalid object; report that as an error
				UE_LOG(LogSlateSoundDevice, Error, TEXT("A sound contains a non-sound resource '%s'"), *Object->GetName());
			}
		}
	}
}

float FSlateSoundDevice::GetSoundDuration(const FSlateSound& Sound) const
{
	USoundBase* const SoundResource = Cast<USoundBase>(Sound.GetResourceObject());
	return (SoundResource) ? SoundResource->Duration : 0.0f;
}
