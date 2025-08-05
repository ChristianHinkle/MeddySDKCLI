// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include "Main.h"

#include "Path.h"
#include <iostream>

int main(int argc, char** argv)
{
    std::filesystem::path videosPath =
        std::filesystem::weakly_canonical("c:/Users/Meddy Man/Videos");

    std::cout << videosPath << std::endl;

    std::filesystem::path videosMeddyprojectPath =
        MeddySDK::Meddyproject::Path::MakeProjectPath(std::filesystem::path(videosPath));

    std::cout << std::endl;
    std::cout << videosMeddyprojectPath << std::endl;

    return 0;
}
