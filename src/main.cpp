#include "core/engine/astrum_engine.h"

int main()
{
    try
    {
        AstrumEngine().run();
    }
    catch (std::exception& exception)
    {
        A_LOG_OUT(exception.what());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}