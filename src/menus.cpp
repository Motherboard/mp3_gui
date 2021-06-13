#include <utility>

#include <utility>

#include <array>
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <stack>
#include <experimental/filesystem>
#include <cstdio>



// For TTGO 16M bytes (128M Bit) Pro ESP32 OLED V2.0
// USE SCREEN with U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 16, /* clock=*/ 15, /* data=*/ 4);

// Can also be used with https://github.com/ThingPulse/esp8266-oled-ssd1306
// SDA = pin 4, SCL = pin 15, RESET = pin 16
//initialize device:

//SSD1306 display(0x3c, 4, 15);

//pulse RESET signal, or keep it high during startup:

//pinMode(16, OUTPUT);
//digitalWrite(16, 1);


using namespace std;

struct MenuItem
{
    MenuItem(string in_title, function<void()> in_function);
    string title;
    function<void()> menu_function;
};

MenuItem::MenuItem(string in_title, function<void()> in_function) : title(std::move(in_title)), menu_function(std::move(in_function)) {}


class Menu {
    int current_page = 0;
    int current_item_in_page = 0;

    vector<vector<MenuItem>> menu_items;

};



int main() {
    cout << "hello world" << endl;
}