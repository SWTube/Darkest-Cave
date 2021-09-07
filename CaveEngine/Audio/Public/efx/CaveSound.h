#pragma once
#include <iostream>
#include <efx/Framework.h>
#include <AL\al.h>
#include <efx/al.h>
#include <math.h>
#include <efx/EFX-Util.h>
#include <cstring>
#include <unordered_map>

#define TEST_WAVE_FILE "Footsteps.wav"
#define VEHICLE_WAVE_FILE "Vehicle.wav"

namespace cave
{
	class Sound
	{
	public:

		//Initialize and generate buffer and source
		void Initialize();

		// Sound Extension for Reverb,Filter etc..
		void Extension();

		//Add sound to buffer
		void Add(const ALchar* wavFile);


		//Play Sound(Source)
		void Play(const ALchar* wavFile);

		// Set Volume
		void SetVolume(const ALchar* wavFile, ALfloat* gain);

		// Set Pitch
		void SetPitch(const ALchar* wavFile, ALfloat* pitch);

		// Set Source Position
		void SetSourcePos(const ALchar* wavFile);

		// Set Rolloff
		void SetRolloff(const ALchar* wavFile, ALfloat rolloff);

		// Set Loop
		void SetLoop(const ALchar* wavFile, bool b);

		// Set Max Distance
		void SetMaxDistance(const ALchar* wavFile, ALfloat maxDis);

		// Set Reference Distance
		void SetRefDistance(const ALchar* wavFile, ALfloat refDis);

		// Set Linstener Position
		void SetListenerPos();

		// Set Audio Effect
		void SetEffect(const ALchar* wavFile, const ALchar* effect);

		// Set Audio Filter
		void SetFilter(const ALchar* wavFile, const ALchar* filter);

		ALuint Source[128]; // Source ID
		ALuint Buffer[128]; // Buffer ID

		ALCdevice* pDevice = NULL;
		ALCcontext* pContext = NULL;
		ALint attribs[4] = { 0 };
		ALCint iSends = 0;

		ALuint EffectSlot = 0;
		ALuint Effect = 0;
		ALuint Filter = 0;

	private:
		std::unordered_map<const ALchar*, ALint> wavMap;
		static ALint wavCount;
		ALfloat ListenerPos[3] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerVel[3] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerOri[6] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };
		ALfloat SourcePos[3] = { 0.0, 0.0, 0.0 };
		ALfloat SourceVel[3] = { 0.0, 0.0, 0.0 };

		ALubyte ch = ' ';
		ALfloat default_max_distance = (ALfloat)3.40282e+38;
		ALfloat default_ref_distance = (ALfloat)1;
		ALfloat default_doppler_factor = 1;
		ALfloat default_sound_speed = (ALfloat)343.3;
		ALfloat rolloff;
		ALfloat maxDistance;
		ALfloat refDistance;
		ALfloat dopplerFactor;
		ALfloat soundSpeed;
	};
}

