
#include "efx/CaveSound.h"
void CaveSound::SoundInitialize()
{

	ALFWInit();
	ALFWprintf("OpenAL Now Available\n");

	if (!ALFWInitOpenAL())
	{
		ALFWprintf("Failed to initialize OpenAL\n");
		ALFWShutdown();
	}
	
	alGenBuffers(128, caveBuffer);
	if (alGetError() != NO_ERROR)
		exit(1);

	alGenSources(128, caveSource);
	if (alGetError() != NO_ERROR)
	{
		ALFWprintf("Failed to generate a source\n");
		alDeleteBuffers(1, caveBuffer);
		ALFWShutdownOpenAL();
		ALFWShutdown();
		exit(1);
	}
	
	if (alGetError() != AL_NO_ERROR)
	{
		ALFWprintf("Failed to set the source attributes.\n");
		alDeleteBuffers(1, caveBuffer);
		alDeleteSources(1, caveSource);
		ALFWShutdownOpenAL();
		ALFWShutdown();
		exit(1);
	}
}

void CaveSound::SoundExtension()
{
	

	/*pDevice = alcOpenDevice(NULL); // 디폴트 OpenAL device를 오픈한다.
	if (!pDevice) return;
	// Effect Extension 기능이 지원되는 장치인지 확인한다.
	if (alcIsExtensionPresent(pDevice, "ALC_EXT_EFX") == AL_FALSE) return;
	printf("EFX Extension found!\n");
	// Context 생성. 생성하면서 source 당 최대 4개의 Auxiliary Send를 허용하겠다고 설정함.
	attribs[0] = ALC_MAX_AUXILIARY_SENDS;
	attribs[1] = 1;
	pContext = alcCreateContext(pDevice, attribs);
	if (!pContext) return;
	alcMakeContextCurrent(pContext); // 생성한 context를 활성화
// 각 Source 당 실제 사용 가능한 Aux. Send 개수를 얻는다.
	alcGetIntegerv(pDevice, ALC_MAX_AUXILIARY_SENDS, 1, &iSends);
	printf("Device supports %d Aux Sends per Source\n", iSends);*/
	// Effect Extension 함수 포인터를 얻는다.
	// 중요!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
	
	// 필요한 모든 Effect Extension 함수들의 포인터를 얻는다.
	// 얻은 function pointer들이 유효한지 검사한다.
	if (!(alGenEffects && alDeleteEffects && alIsEffect)) std::cout << "fuck its not working!";
	// EFX 초기화가 완료되어 이제부터 EFX 프로그래밍이 가능해졌음!!!!
}

void CaveSound::AddSound(const ALchar* wavFile)
{

	// 구조체에서 웨이브이름이랑 몇번째에 저장했는지
	// 
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(wavFile), caveBuffer[0]))
	{
		ALFWprintf("Failed to load or attach %s\n", ALFWaddMediaPath(wavFile));
		alDeleteBuffers(1, caveBuffer);
		ALFWShutdownOpenAL(); ALFWShutdown();
		exit(1);
	}
}


void CaveSound::SoundToSource(const ALchar* wavFile)
{
	alSourcei(caveSource[0], AL_BUFFER, caveBuffer[0]);
}

void CaveSound::SetLoop(bool b)
{
	if (b == true)
		alSourcei(caveSource[0], AL_LOOPING, AL_TRUE);
	else if(b == false)
		alSourcei(caveSource[0], AL_LOOPING, AL_FALSE);
}

void CaveSound::SetMaxDistance(ALfloat maxDis)
{
	alSourcef(caveSource[0], AL_MAX_DISTANCE, maxDis);
}

void CaveSound::SetRefDistance(ALfloat refDis)
{
	alSourcef(caveSource[0], AL_REFERENCE_DISTANCE, refDis);
}


void CaveSound::SetListenerPos()
{
	//게임에서 리스너(플레이어 캐릭터)의 값을 가져옴
	
	//리스너에 값 적용
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

void CaveSound::SoundPlay()
{
	alSourcePlay(caveSource[0]);
	
}

void CaveSound::SetVolume(ALfloat *gain)
{
	alSourcefv(caveSource[0], AL_GAIN, gain);
}

void CaveSound::SetPitch(ALfloat *pitch)
{
	alSourcefv(caveSource[0], AL_PITCH, pitch);
}

void CaveSound::SetSourcePos()
{
	alSourcefv(caveSource[0], AL_POSITION, SourcePos);
}

void CaveSound::SetRolloff(ALfloat rolloff)
{
	alSourcef(caveSource[0], AL_ROLLOFF_FACTOR, rolloff);
}



