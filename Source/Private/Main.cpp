// Copyright (c) 2023-2024 Christian Hinkle, Brian Hinkle.

#include "Main.h"

#include "ProjectPath.h"
#include <iostream>

int main(int argc, char** argv)
{
    std::filesystem::path videosPath =
        std::filesystem::weakly_canonical("c:/Users/Meddy Man/Videos");

    std::cout << videosPath << std::endl;

    std::filesystem::path videosMeddyprojectPath =
        MeddySDK::Meddyproject::ProjectPath::MakeProjectPath(videosPath);

    std::cout << std::endl;
    std::cout << videosMeddyprojectPath << std::endl;

    return 0;
}
