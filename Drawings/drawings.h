#pragma once

extern HFONT framefont, espfont, mFont, osFont, sFont, tFont, cFont, titleFont, subtitleFont, heading, o4Font_20, o4Font_11, o4Font_03;; // if you want to add more

typedef int ViVec_t;

class ViVecMouse {
public:
    
    ViVec_t x, y;
    ViVecMouse(void);
    ViVecMouse(ViVec_t X, ViVec_t Y);
    
};

class cDrawings {
public:
    
    wstring wstringtostring(string str);
    wstring StringToWstring(string str);
    HFONT createfont(HFONT font, const char* szFont, int tall, int flags);
    
    void drawbox(int x, int y, int w, int h, Color color);
    void drawboxoutline(int x, int y, int w, int h, Color color);
    void fillrgba(int x, int y, int w, int h, Color color);
    void drawline(int x, int y, int xx, int yy, Color color);
    void drawstring(int x, int y, Color color, HFONT font, const char* szString, bool bCenter = false);
    void drawgradient(int x, int y, int w, int h, Color col1, Color col2);
    void GradientH(int x, int y, int width, int height, Color color1, Color color2);
    void BorderBox(int x, int y, int w, int h, int thickness, Color color);
    void RectOutlined(int x, int y, int w, int h, int thickness, Color color, Color outlined);
    
    void textbox(int x, int y, int w, const char* szString, string szValue[100], int inputIndex, int index, bool* var);
    void handleinput(int eventcode, string arr[100]);
    
    bool inArea(int x, int y, int w, int h);
    Vector2D GetTextSize(const char* text, HFONT font);
    
    int CalcPos(int x);
    bool MoveMenu(int & x, int & y, int w, int h, int index);
    
    ViVecMouse GetMouse();
    void drawmouse();
    
    void drawCrosshair(int x, int y, Color col);
    
    /* Creds to reactiioN @ uc */
    size_t m_nCurrentPos[100];
    string m_szCurrentString[100];
    string m_szChangedValue[100];
    
    bool IsKeyPressed(int eventCode, ButtonCode_t keyCode) {
        return (eventCode == keyCode) ? true : false;
    }
    
};

void setupConfig();

extern cDrawings* draw;
