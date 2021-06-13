#include "../src/FileExplorer.hpp"
#include "catch.hpp"
#include "hippomocks.h"
#include <string>
#include <iostream>
#include <cstdio>
#include "reverse.hpp"
#include "FSMocks.hpp"

using namespace Catch::Matchers;


TEST_CASE("Single entry") {
    std::string SINGLE_MP3 = "Hello.mp3";
    int entry_idx = 0;
    MockRepository mocks;
    mocks.OnCallFunc(fopen).Return(reinterpret_cast<FILE *>(1));
    mocks.OnCallFunc(fgets).Do(
        [&](char * buf, int n, FILE * f)->char *{ 
            if (entry_idx++ == 0)
            {
                strcpy(buf, SINGLE_MP3.c_str());
                return buf;
            }
            else
                return nullptr;
            }
        );
    mocks.OnCallFunc(fclose).Return(0);
    FileExplorer file_explorer;
    REQUIRE_THAT(file_explorer.next_file_name(), Equals(SINGLE_MP3));
    REQUIRE_THAT(file_explorer.next_file_name(), Equals(""));
}



TEST_CASE("Double entry relative")
{
    std::map<std::string, std::vector<std::string>> fs{{"/.db", {"Hello.mp3", "World.mp3"}}};
    FSMocks fsMocks(fs);
    auto files = fs["/.db"];
    FileExplorer file_explorer;
    for (const auto &entry: files)
        REQUIRE_THAT(file_explorer.next_file_name(), Equals(entry));
    REQUIRE_THAT(file_explorer.next_file_name(), Equals(""));
    for (int i = files.size() - 2; i > -1; --i)
        REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals(files[i]));
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals(""));
}

TEST_CASE("Triple entry relative")
{
    std::map<std::string, std::vector<std::string>> fs{{"/.db", {"Hello.mp3", "World.mp3", "Its me.mp3"}}};
    FSMocks fsMocks(fs);
    auto files = fs["/.db"];
    FileExplorer file_explorer;
    for (const auto &entry: files)
        REQUIRE_THAT(file_explorer.next_file_name(), Equals(entry));
    REQUIRE_THAT(file_explorer.next_file_name(), Equals(""));
    for (int i = files.size() - 2; i > -1; --i)
        REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals(files[i]));
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals(""));
    for (int i = 1; i < files.size(); ++i)
        REQUIRE_THAT(file_explorer.next_file_name(), Equals(files[i]));
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals(files[files.size() - 2]));
    REQUIRE_THAT(file_explorer.next_file_name(), Equals(files[files.size() - 1]));
}

TEST_CASE("Triple entry absolute")
{
    std::map<std::string, std::vector<std::string>> fs{{"/.db", {"Hello.mp3", "World.mp3", "Its me.mp3"}}};
    FSMocks fsMocks(fs);
    auto files = fs["/.db"];
    FileExplorer file_explorer;
    for (const auto &entry: files)
        REQUIRE_THAT(file_explorer.next_file_name(), Equals(entry));
    int indices[3] = {0, 2, 1};
    for (int idx: indices)
        REQUIRE_THAT(file_explorer.seek_file_name(idx, SeekMode::Absolute), Equals(files[idx]));
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Absolute), Equals(""));
    REQUIRE_THAT(file_explorer.seek_file_name(3, SeekMode::Absolute), Equals(""));
    REQUIRE_THAT(file_explorer.seek_file_name(40, SeekMode::Absolute), Equals(""));
    REQUIRE_THAT(file_explorer.seek_file_name(0, SeekMode::Absolute), Equals(files[0]));
    REQUIRE_THAT(file_explorer.next_file_name(), Equals(files[1]));
    while (!file_explorer.next_file_name().empty())
        continue;
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals(files[files.size() - 2]));
}

TEST_CASE("Multiple dirs")
{
    std::map<std::string, std::vector<std::string>> fs{
        {"/.db", {"Hello.mp3", "World.mp3", "Its me.mp3"}},
        {"/inner/.db", {"1.mp3", "2.mp3", "3.mp3", "4.mp3"}}
    };
    FSMocks fsMocks(fs);
    auto files = fs["/.db"];
    FileExplorer file_explorer;
    for (const auto &entry: files)
        REQUIRE_THAT(file_explorer.next_file_name(), Equals(entry));
    int indices[3] = {0, 2, 1};
    for (int idx: indices)
        REQUIRE_THAT(file_explorer.seek_file_name(idx, SeekMode::Absolute), Equals(files[idx]));
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Absolute), Equals(""));
    REQUIRE_THAT(file_explorer.seek_file_name(3, SeekMode::Absolute), Equals(""));
    REQUIRE_THAT(file_explorer.seek_file_name(40, SeekMode::Absolute), Equals(""));
    file_explorer.set_dir("/inner/", SeekMode::Absolute);
    files = fs["/inner/.db"];
    for (const auto &entry: files)
        REQUIRE_THAT(file_explorer.next_file_name(), Equals(entry));
    REQUIRE_THAT(file_explorer.next_file_name(), Equals(""));
    for (int i = files.size() - 2; i > -1; --i)
        REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals(files[i]));
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals(""));
    for (int i = 1; i < files.size(); ++i)
        REQUIRE_THAT(file_explorer.next_file_name(), Equals(files[i]));
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals(files[files.size() - 2]));
    REQUIRE_THAT(file_explorer.next_file_name(), Equals(files[files.size() - 1]));

}


TEST_CASE("Test absolute seek") {
    std::map<std::string, std::vector<std::string>> fs = {
            {"/.db", {"Hello.mp3", "World.mp3", "InnerDir/"}},
            {"/InnerDir/.db", {"This.mp3", "is.mp3", "inside.mp3", "the.mp3", "inner.mp3", "dir.mp3"}}
    };
    FSMocks mocks(fs);
    FileExplorer file_explorer;
    file_explorer.next_file_name();
    REQUIRE_THAT(file_explorer.seek_file_name(0, SeekMode::Absolute), Equals("Hello.mp3"));
    REQUIRE_THAT(file_explorer.next_file_name(), Equals("World.mp3"));
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals("Hello.mp3"));

    while (not file_explorer.next_file_name().empty())
        continue;
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals("World.mp3"));
    file_explorer.set_dir("/InnerDir/", SeekMode::Absolute);
    while (not file_explorer.next_file_name().empty())
        continue;
    file_explorer.seek_file_name(0, SeekMode::Absolute);
    while (not file_explorer.next_file_name().empty())
        continue;
    REQUIRE_THAT(file_explorer.seek_file_name(-1, SeekMode::Relative), Equals("inner.mp3"));

}


TEST_CASE("Test set previous dir") {
    std::map<std::string, std::vector<std::string>> fs = {
            {"/.db", {"Hello.mp3", "World.mp3", "InnerDir/"}},
            {"/InnerDir/.db", {"This.mp3", "is.mp3", "inside.mp3", "the.mp3", "inner.mp3", "dir.mp3"}}
    };
    FSMocks mocks(fs);
    FileExplorer file_explorer;
    file_explorer.set_dir("InnerDir", SeekMode::Relative);
    file_explorer.next_file_name();
    file_explorer.next_file_name();
    file_explorer.set_dir("..", SeekMode::Relative);
    REQUIRE_THAT(file_explorer.next_file_name(), Equals("Hello.mp3"));
}