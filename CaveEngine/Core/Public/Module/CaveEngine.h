#pragma once

#include "DataTypes.h"

namespace caveengine
{
    class CaveEngine
    {
    public:
        CaveEngine(const CaveEngine& other) = delete;
        CaveEngine(const CaveEngine&& other) = delete;
        CaveEngine& operator=(const CaveEngine& other) = delete;
        ~CaveEngine();

        static CaveEngine& GetInstance();
        static void Initialize();
        static void RunDemo();
        virtual void RunGame();
        virtual void PlayLoop();
    private:
        CaveEngine();
        static CaveEngine* mInstance;
    };
} // namespace caveengine
