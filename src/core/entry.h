#pragma once

#include "engine/astrum_engine.h"

#define A_ENTRY(x)                          \
int main()                                  \
{                                           \
    AstrumEngine<x> app;                    \
    try                                     \
    {                                       \
        app.run();                          \
    }                                       \
    catch (const std::exception& exception) \
    {                                       \
        A_LOG_OUT(exception.what());        \
                                            \
        return EXIT_FAILURE;                \
    }                                       \
                                            \
    return EXIT_SUCCESS;                    \
}