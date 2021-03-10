#include "Module/CaveEngine.h"

namespace caveengine
{
    CaveEngine::~CaveEngine()
    {
        // Clear Memory
        // Shutdown Engine
        delete mInstance;
    }

    CaveEngine& CaveEngine::GetInstance()
    {
        if (mInstance == nullptr)
        {
            mInstance = new CaveEngine();
        }

        return *mInstance;
    }

    void CaveEngine::Initialize()
    {
        // initialise Log Manager

        // initialise Memory Manager

        // initialise Resource Group Manager
        // initialise Resource Background Queue

        // initialise Timer

#if PROFILING
        // initialise Profiler
#endif

        // initialise File System

        // initialise Graphics Manager

        // initialise Input Manager
        // intialise Page Memory Manager

        // initialise Audio Manager
        // initialise Cache Manager
        // initialise User Control Manager

        // initialise Resource Manager   
    }

    void CaveEngine::RunDemo()
    {
        static uint8_t lastDemo = 0;

        // start intro song

        while (true)
        {
            // Fade Out
            
            // Run Game Loop
            mInstance->RunGame();
            // Fade Out
            // Start intro song
        }

    }

    void CaveEngine::RunGame()
    {
        // restartgame:
        // Clear memory
        // draw play screen
        // died = false

        // restart:
        do
        {
            // if game is not loaded
            // then get previous data (like score)
            // Draw Score

            // if game is not loaded
            // then set up game level

            // Start Music
            // Check page main memory
            // if not dead
            // then preload graphics

            // Draw level

            // startplayloop:
            PlayLoop();
            // Stop Music
            // if startgame or loadedgame
            // then goto restartgame
            // switch (playstate)
            // if completed
            // then draw keys
            // then fade out
            // then clear memory
            // then level complete
            // if died
            // then Died()
            // then clear memory
            return;
            // else if victorious
            // then fade out
            // then clear memory
            // then Victory()
            // then clear memory
            return;
            // else
            // then clear memory
        } while (true);
        
    }

    void CaveEngine::PlayLoop()
    {
        bool bIsGameStarted = false;
        do
        {
            // Poll Controls
            // Actor Thinks
            // Poll Sounds
            // Update Sound Location
            // if faded
            // then fade in
            // Check Keys
        } while (bIsGameStarted);
        
    }
} // namespace caveengine
