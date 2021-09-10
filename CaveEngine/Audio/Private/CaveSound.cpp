
#include "efx/CaveSound.h"

namespace cave
{
	ALint Sound::wavCount = 0;

	void Sound::Initialize()
	{

		ALFWInit();

		if (!ALFWInitOpenAL())
		{
			ALFWprintf("Failed to initialize OpenAL\n");
			ALFWShutdown();
		}

		alGenBuffers(128, Buffer);
		if (alGetError() != NO_ERROR)
			exit(1);

		alGenSources(128, Source);
		if (alGetError() != NO_ERROR)
		{
			ALFWprintf("Failed to generate a source\n");
			alDeleteBuffers(1, Buffer);
			ALFWShutdownOpenAL();
			ALFWShutdown();
			exit(1);
		}

		if (alGetError() != AL_NO_ERROR)
		{
			ALFWprintf("Failed to set the source attributes.\n");
			alDeleteBuffers(1, Buffer);
			alDeleteSources(1, Source);
			ALFWShutdownOpenAL();
			ALFWShutdown();
			exit(1);
		}

	}

	void Sound::Extension()
	{

		// Update 
		alGenAuxiliaryEffectSlots = (LPALGENEFFECTS)alGetProcAddress("alGenAuxiliaryEffectSlots");
		alGenEffects = (LPALGENEFFECTS)alGetProcAddress("alGenEffects");
		alDeleteEffects = (LPALDELETEEFFECTS)alGetProcAddress("alDeleteEffects");
		alIsEffect = (LPALISEFFECT)alGetProcAddress("alIsEffect");
		alEffecti = (LPALEFFECTI)alGetProcAddress("alEffecti");
		alEffectf = (LPALEFFECTF)alGetProcAddress("alEffectf");
		alGenFilters = (LPALGENFILTERS)alGetProcAddress("alGenFilters");
		alIsFilter = (LPALISFILTER)alGetProcAddress("alIsFilter");
		alFilteri = (LPALFILTERI)alGetProcAddress("alFilteri");
		alFilterf = (LPALFILTERF)alGetProcAddress("alFilterf");
		alAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI)alGetProcAddress("alAuxiliaryEffectSloti");
		if (!(alGenEffects && alDeleteEffects && alIsEffect))
		{
			std::cout << "Something wrong while Initialize EFX";
		}


		alGetError();
		//alGenEffects(1, &Effect);
		//alGenAuxiliaryEffectSlots(1, &EffectSlot);
		//alGenFilters(1, &Filter);
	}

	void Sound::Add(const ALchar* wavFile)
	{
		if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(wavFile), Buffer[wavCount]))
		{
			ALFWprintf("Failed to load or attach %s\n", ALFWaddMediaPath(wavFile));
			alDeleteBuffers(1, Buffer);
			ALFWShutdownOpenAL(); ALFWShutdown();
			exit(1);
		}

		alSourcei(Source[wavCount], AL_BUFFER, Buffer[wavCount]);

		wavMap.insert(std::unordered_map<const ALchar*, ALint>::value_type(wavFile, wavCount));
		wavCount++;
	}

	void Sound::SetLoop(const ALchar* wavFile, bool b)
	{
		if (b == true)
			alSourcei(Source[wavMap[wavFile]], AL_LOOPING, AL_TRUE);
		else if (b == false)
			alSourcei(Source[wavMap[wavFile]], AL_LOOPING, AL_FALSE);
	}

	void Sound::SetMaxDistance(const ALchar* wavFile, ALfloat maxDis)
	{
		alSourcef(Source[wavMap[wavFile]], AL_MAX_DISTANCE, maxDis);
	}

	void Sound::SetRefDistance(const ALchar* wavFile, ALfloat refDis)
	{
		alSourcef(Source[wavMap[wavFile]], AL_REFERENCE_DISTANCE, refDis);
	}


	void Sound::SetListenerPos()
	{
		alListenerfv(AL_POSITION, ListenerPos);
		alListenerfv(AL_VELOCITY, ListenerVel);
		alListenerfv(AL_ORIENTATION, ListenerOri);
	}

	void Sound::Play(const ALchar* wavFile)
	{

		alSourcePlay(Source[wavMap[wavFile]]);

	}

	void Sound::SetVolume(const ALchar* wavFile, ALfloat* gain)
	{
		alSourcefv(Source[wavMap[wavFile]], AL_GAIN, gain);
	}

	void Sound::SetPitch(const ALchar* wavFile, ALfloat* pitch)
	{
		alSourcefv(Source[wavMap[wavFile]], AL_PITCH, pitch);
	}

	void Sound::SetSourcePos(const ALchar* wavFile)
	{
		alSourcefv(Source[wavMap[wavFile]], AL_POSITION, SourcePos);
	}

	void Sound::SetRolloff(const ALchar* wavFile, ALfloat rolloff)
	{
		alSourcef(Source[wavMap[wavFile]], AL_ROLLOFF_FACTOR, rolloff);
	}

	void Sound::SetEffect(const ALchar* wavFile, const ALchar* effect)
	{
		alGetError();

		if (effect == "0")
		{
			alSource3i(Source[wavMap[wavFile]], AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, NULL);
			if (alGetError() != AL_NO_ERROR)
				printf("Failed to disable Source Send 0\n");
		}

		else
		{
			if (effect == "reverb")
			{
				if (alIsEffect(Effect)) {
					alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
					if (alGetError() != AL_NO_ERROR)
						printf("Reverb Effect not supported\n");
					else
						alEffectf(Effect, AL_REVERB_DECAY_TIME, 5.0f);
				}
			}

			alAuxiliaryEffectSloti(EffectSlot, AL_EFFECTSLOT_EFFECT, Effect);
			if (alGetError() != AL_NO_ERROR)
				printf("Failed to load effect into effect slot\n");

			alSource3i(Source[wavMap[wavFile]], AL_AUXILIARY_SEND_FILTER, EffectSlot, 0, NULL);
			if (alGetError() != AL_NO_ERROR)
				printf("Failed to configure Source Send 0\n");
		}
	}

	void Sound::SetFilter(const ALchar* wavFile, const ALchar* filter)
	{
		if (filter == "low_pass");
		{
			if (alIsFilter(Filter))
			{
				alFilteri(Filter, AL_FILTER_TYPE, AL_FILTER_LOWPASS);

				if (alGetError() != AL_NO_ERROR)
					printf("Low Pass Filter not supported\n");

				else
				{
					alFilterf(Filter, AL_LOWPASS_GAIN, 0.5f);
					alFilterf(Filter, AL_LOWPASS_GAINHF, 0.5f);
				}
			}
		}
		alSource3i(Source[wavMap[wavFile]], AL_AUXILIARY_SEND_FILTER, EffectSlot, 0, Filter);
		if (alGetError() != AL_NO_ERROR)
			printf("Failed to configure Source Send 1\n");
	}
}



