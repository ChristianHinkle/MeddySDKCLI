// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <iostream>
#include <string_view>

int main(int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "usage: meddy [--help]" << '\n';
        std::cout.flush();
        return 0;
    }

    if (argc == 2)
    {
        const std::string_view arg = argv[1];

        if (arg == "--help")
        {
            std::cout << "There is nothing so far." << '\n';
            std::cout.flush();
            return 0;
        }

        std::cout << "meddy: '" << arg << "' is not a meddy command. See 'meddy --help'." << '\n';
        std::cout.flush();
        return 0;
    }

    std::cout << "meddy: What is even that?" << '\n';
    std::cout.flush();
    return 0;
}
