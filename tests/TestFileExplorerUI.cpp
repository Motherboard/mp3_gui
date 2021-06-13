//
// Created by master on 6/29/19.
//

#include "FileExplorerUI.hpp"
#include "AbstractScreen.hpp"
#include "catch.hpp"
#include "hippomocks.h"
#include <array>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "FSMocks.hpp"
#include "TestScreen.hpp"

using namespace std;
using namespace Catch::Matchers;


TEST_CASE("Test navigation") {
    map<string, vector<string>> fs = {
            {"/.db", {"Hello.mp3", "World.mp3", "InnerDir/"}},
            {"/InnerDir/.db", {"This.mp3", "is.mp3", "inside.mp3", "the.mp3", "inner.mp3", "dir.mp3"}}
            };
    FSMocks mocks(fs);
    TestScreen screen;
    FileExplorerUI ui(screen);
    ui.draw_whole_screen();
    REQUIRE_THAT(screen.lines[0], Equals("*Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("*World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("*InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("*InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("*World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("*InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("*InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("*World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("*World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("*InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_right_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*This.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("is.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("the.mp3"));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("This.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("*is.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("the.mp3"));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("This.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("is.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("*inside.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("the.mp3"));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("This.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("is.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("*the.mp3"));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("is.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("the.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("*inner.mp3"));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("the.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("inner.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("*dir.mp3"));
    ui.on_down_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("the.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("inner.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("*dir.mp3"));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("the.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("*inner.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("dir.mp3"));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("*the.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("inner.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("dir.mp3"));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*inside.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("the.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("inner.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("dir.mp3"));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*is.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("the.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("inner.mp3"));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*This.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("is.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("the.mp3"));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*This.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("is.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("inside.mp3"));
    REQUIRE_THAT(screen.lines[3], Equals("the.mp3"));
    ui.on_left_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*InnerDir/"));
    REQUIRE_THAT(screen.lines[1], Equals(""));
    REQUIRE_THAT(screen.lines[2], Equals(""));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*World.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("InnerDir/"));
    REQUIRE_THAT(screen.lines[2], Equals(""));
    REQUIRE_THAT(screen.lines[3], Equals(""));
    ui.on_up_pressed();
    REQUIRE_THAT(screen.lines[0], Equals("*Hello.mp3"));
    REQUIRE_THAT(screen.lines[1], Equals("World.mp3"));
    REQUIRE_THAT(screen.lines[2], Equals("InnerDir/"));
    REQUIRE_THAT(screen.lines[3], Equals(""));

}