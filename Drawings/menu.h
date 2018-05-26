//
//  menu.hpp
//  macOS base
//

#pragma once

#include "main.h"

class cMenu
{
public:
    
    void renderCheckbox(int x, int y, const char* str, bool* var);
    void renderSlider(int x, int y, int w, const char* szString, int& value, int max, int min);
    void renderSlider(int x, int y, int w, const char* szString, float& value, int max, int min);
    void renderCombo(int x, int y, int w, int h, const char* szString, vector<string> szValue, int& currValue, bool* bOpend);
    void renderButton(int x, int y, const char* szString, bool* var);
    void drawcolorpicker(int x, int y, const char *szString, Color &col);
    void playerbutton(int x, int y, int w, int h, int index, int& playercount, const char* szString);
    
    void renderMenu();
    void renderConfigs(int x, int y);
    void renderAim(int x, int y);
    void renderPlayer(int x, int y);
    void renderVis(int x, int y);
    void renderMisc(int x, int y);
    void renderColors(int x, int y);
    
    
};

void setupConfig();

extern cMenu* menu;
