/*
 Main entry point for the Dynamik Studio.

 Author:    Dhirak Wishal
 Date:      19/05/2020
*/
#include "studioafx.h"
#include "Dynamik.h"
using namespace Dynamik;

I32 main(I32 argc, CPTR* argv)
{
    Dynamik::DMKEngine::createInstance();
    Dynamik::DMKEngine::execute();

    return 0;
}