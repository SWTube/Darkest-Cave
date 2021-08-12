#pragma once
#include <iostream>
#include <efx/Framework.h>
#include <AL\al.h>
#include <efx/al.h>
#include <math.h>
#include <efx/EFX-Util.h>

#define TEST_WAVE_FILE "Footsteps.wav"
#define VEHICLE_WAVE_FILE "Vehicle.wav"

class CaveSound 
{
public:
	//사운드에 default 값을 줌
	void SoundInitialize();
	void SoundExtension();

	//사운드(wav파일)를 끌어와 추가할 때
	void AddSound(const ALchar* wavFile);
	//사운드버퍼를 소스에 넣을 때
	void SoundToSource(const ALchar* wavFile);
	
	//특정 조건(위치,공격,피격,이동)을 만족하면 사운드 재생
	void SoundPlay();//loop? 



	void SetVolume(ALfloat *gain);
	void SetPitch(ALfloat *pitch);
	void SetSourcePos();
	void SetRolloff(ALfloat rolloff);
	void SetLoop(bool b);
	void SetMaxDistance(ALfloat maxDis);
	void SetRefDistance(ALfloat refDis);
	void SetListenerPos();

	ALuint caveSource[128]; // Source ID
	ALuint caveBuffer[128]; // Buffer ID

	ALCdevice* pDevice = NULL;
	ALCcontext* pContext = NULL;
	ALint attribs[4] = { 0 };
	ALCint iSends = 0;
private:
	ALfloat ListenerPos[3] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerVel[3] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerOri[6] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };
	ALfloat SourcePos[3] = { 0.0, 0.0, 0.0 };
	ALfloat SourceVel[3] = { 0.0, 0.0, 0.0 };

	
	ALubyte ch = ' ';
	ALfloat default_max_distance = (ALfloat)3.40282e+38;
	ALfloat default_ref_distance = (ALfloat)1;
	ALfloat default_doppler_factor = 1;
	ALfloat default_sound_speed = 343.3;
	ALfloat rolloff, maxDistance; // rollof 조절과 최대거리 조절
	ALfloat refDistance; // 참조거리
	ALfloat dopplerFactor; //도플러
	ALfloat soundSpeed; //소리의 속도 조절을 위해
};

