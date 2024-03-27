// Copyright (c) 2023-2024 Christian Hinkle, Brian Hinkle.

#include "MeddySDKCLI.h"

#include <iostream>
#include "MeddySDK_Meddyproject.h"

int main(int argc, char** argv)
{
    std::cout << "Hello CMake." << std::endl;

    MeddySDK::Meddyproject::MyBoostFilesystemExperiment();

    return 0;
}
