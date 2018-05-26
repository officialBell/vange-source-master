#include "clantag.h"


void gamesense()
{
    if(!vars.misc.gamesense)
        return;
    
    static int Tick = 0;
    Tick++;
    
    if (Tick > 0 && Tick < 15)
    {
        SetClanTag("          gam", "gamesense");
    }
    else if (Tick > 30 && Tick < 45)
    {
        SetClanTag("         game", "gamesense");
    }
    else if (Tick > 60 && Tick < 75)
    {
        SetClanTag("        games", "gamesense");
    }
    else if (Tick > 90 && Tick < 105)
    {
        SetClanTag("       gamese", "gamesense");
    }
    else if (Tick > 120 && Tick < 135)
    {
        SetClanTag("      gamesen", "gamesense");
    }
    else if (Tick > 150 && Tick < 165)
    {
        SetClanTag("     gamesens", "gamesense");
    }
    else if (Tick > 180 && Tick < 195)
    {
        SetClanTag("    gamesense", "gamesense");
    }
    else if  (Tick > 210 && Tick < 225)
    {
        SetClanTag("   gamesense ", "gamesense");
    }
    else if (Tick > 240 && Tick < 255)
    {
        SetClanTag("  gamesense  ", "gamesense");
    }
    else if (Tick > 270 && Tick < 285)
    {
        SetClanTag(" gamesense   ", "gamesense");
    }
    else if (Tick > 300 && Tick < 315)
    {
        SetClanTag("gamesense    ", "gamesense");
    }
    else if (Tick > 330 && Tick < 345)
    {
        SetClanTag("amesense     ", "gamesense");
    }
    else if (Tick > 360 && Tick < 375)
    {
        SetClanTag("mesense      ", "gamesense");
    }
    else if (Tick > 390 && Tick < 405)
    {
        SetClanTag("esense       ", "gamesense");
    }
    else if (Tick > 420 && Tick < 435)
    {
        SetClanTag("sense        ", "gamesense");
    }
    else if (Tick > 450 && Tick < 465)
    {
        SetClanTag("esnse        ", "gamesense");
    }
    else if (Tick > 480 && Tick < 495)
    {
        SetClanTag("snse         ", "gamesense");
    }
    else if (Tick > 510 && Tick < 525)
    {
        SetClanTag("nse          ", "gamesense");
    }
    else if (Tick > 540 && Tick < 555)
    {
        SetClanTag("se           ", "gamesense");
    }
    else if (Tick > 570 && Tick < 585)
    {
        SetClanTag("e            ", "gamesense");
    }
    else if (Tick > 600 && Tick < 615)
    {
        SetClanTag("             ", "gamesense");
    }
    
    
    // Reset
    if(Tick > 615)
    {
        Tick = 0;
    }
}

void vangeme()
{
    
    if(!vars.misc.vangeme)
        return;
    
    static int Tick = 0;
    Tick++;
    
    if (Tick > 0 && Tick < 15) {
        SetClanTag("            v", "vange.me");
    }
    else if (Tick > 30 && Tick < 45) {
        SetClanTag("           va", "vange.me");
    }
    else if (Tick > 60 && Tick < 75) {
        SetClanTag("          van", "vange.me");
    }
    else if (Tick > 90 && Tick < 105) {
        SetClanTag("         vang", "vange.me");
    }
    else if (Tick > 120 && Tick < 135) {
        SetClanTag("        vange", "vange.me");
    }
    else if (Tick > 150 && Tick < 165) {
        SetClanTag("       vange.", "vange.me");
    }
    else if  (Tick > 180 && Tick < 195) {
        SetClanTag("      vange.m", "vange.me");
    }
    else if  (Tick > 210 && Tick < 225) {
        SetClanTag("     vange.me", "vange.me");
    }
    else if (Tick > 240 && Tick < 255) {
        SetClanTag("    vange.me", "vange.me");
    }
    else if (Tick > 270 && Tick < 285) {
        SetClanTag("   vange.me ", "vange.me");
    }
    else if (Tick > 300 && Tick < 315) {
        SetClanTag(" vange.me   ", "vange.me");
    }
    else if (Tick > 330 && Tick < 345) {
        SetClanTag("vange.me    ", "vange.me");
    }
    else if (Tick > 360 && Tick < 375) {
        SetClanTag("ange.me     ", "vange.me");
    }
    else if (Tick > 390 && Tick < 405) {
        SetClanTag("nge.me      ", "vange.me");
    }
    else if (Tick > 420 && Tick < 435) {
        SetClanTag("ge.me       ", "vange.me");
    }
    else if (Tick > 450 && Tick < 465) {
        SetClanTag("e.me        ", "vange.me");
    }
    else if (Tick > 480 && Tick < 495) {
        SetClanTag(".me         ", "vange.me");
    }
    else if (Tick > 510 && Tick < 525) {
        SetClanTag("me          ", "vange.me");
    }
    else if (Tick > 540 && Tick < 555) {
        SetClanTag("e           ", "vange.me");
    }
    if (Tick > 555) {
        Tick = 0;
    }
}

void aimware() {
    
    if(!vars.misc.aimware)
        return;
    
    static int Tick = 0;
    Tick++;
    if (Tick > 0 && Tick < 15) {
        SetClanTag("               A", "aimware");
    }
    else if (Tick > 30 && Tick < 45) {
        SetClanTag("              AI", "aimware");
    }
    else if (Tick > 60 && Tick < 75) {
        SetClanTag("             AIM", "aimware");
    }
    else if (Tick > 90 && Tick < 105) {
        SetClanTag("             AIMW", "aimware");
    }
    else if (Tick > 120 && Tick < 135) {
        SetClanTag("            AIMWA", "aimware");
    }
    else if (Tick > 150 && Tick < 165) {
        SetClanTag("          AIMWAR", "aimware");
    }
    else if  (Tick > 180 && Tick < 195) {
        SetClanTag("         AIMWARE", "aimware");
    }
    else if  (Tick > 210 && Tick < 225) {
        SetClanTag("        AIMWARE.", "aimware");
    }
    else if (Tick > 240 && Tick < 255) {
        SetClanTag("       AIMWARE.n", "aimware");
    }
    else if (Tick > 270 && Tick < 285) {
        SetClanTag("      AIMWARE.ne", "aimware");
    }
    else if (Tick > 300 && Tick < 315) {
        SetClanTag("     AIMWARE.net", "aimware");
    }
    else if (Tick > 330 && Tick < 345) {
        SetClanTag("   AIMWARE.net  ", "aimware");
    }
    else if (Tick > 360 && Tick < 375) {
        SetClanTag("  AIMWARE.net   ", "aimware");
    }
    else if (Tick > 390 && Tick < 405) {
        SetClanTag(" AIMWARE.net    ", "aimware");
    }
    else if (Tick > 420 && Tick < 435) {
        SetClanTag("AIMWARE.net     ", "aimware");
    }
    else if (Tick > 450 && Tick < 465) {
        SetClanTag("IMWARE.net     A", "aimware");
    }
    else if (Tick > 480 && Tick < 495) {
        SetClanTag("MWARE.net     AI", "aimware");
    }
    else if (Tick > 510 && Tick < 525) {
        SetClanTag("WARE.net     AIM", "aimware");
    }
    else if (Tick > 540 && Tick < 555) {
        SetClanTag("ARE.net     AIMW", "aimware");
    }
    else if (Tick > 570 && Tick < 585) {
        SetClanTag("RE.net     AIMWA", "aimware");
    }
    else if (Tick > 600 && Tick < 615) {
        SetClanTag("E.net     AIMWAR", "aimware");
    }
    else if (Tick > 630 && Tick < 645) {
        SetClanTag(".net     AIMWARE", "aimware");
    }
    else if (Tick > 660 && Tick < 675) {
        SetClanTag("net     AIMWARE.", "aimware");
    }
    else if (Tick > 675 && Tick < 690) {
        SetClanTag("et     AIMWARE.n", "aimware");
    }
    else if (Tick > 690 && Tick < 705) {
        SetClanTag("t     AIMWARE.ne", "aimware");
    }
    else if (Tick > 705 && Tick < 720) {
        SetClanTag("     AIMWARE.net", "aimware");
    }
    else if (Tick > 720 && Tick < 735) {
        SetClanTag("    AIMWARE.net ", "aimware");
    }
    else if (Tick > 735 && Tick < 750) {
        SetClanTag("  AIMWARE.net   ", "aimware");
    }
    else if (Tick > 750 && Tick < 765) {
        SetClanTag(" AIMWARE.net    ", "aimware");
    }
    else if (Tick > 765 && Tick < 780) {
        SetClanTag("AIMWARE.net     ", "aimware");
    }
    else if (Tick > 780 && Tick < 795) {
        SetClanTag("IMWARE.net      ", "aimware");
    }
    else if (Tick > 795 && Tick < 810) {
        SetClanTag("MWARE.net       ", "aimware");
    }
    else if (Tick > 810 && Tick < 825) {
        SetClanTag("WRE.net         ", "aimware");
    }
    else if (Tick > 825 && Tick < 840) {
        SetClanTag("RE.net          ", "aimware");
    }
    else if (Tick > 840 && Tick < 855) {
        SetClanTag("E.net           ", "aimware");
    }
    else if (Tick > 855 && Tick < 870) {
        SetClanTag(".net           ", "aimware");
    }
    else if (Tick > 870 && Tick < 885) {
        SetClanTag("                ", "aimware");
    }
    
    if (Tick > 885) {
        Tick = 0;
    }
}



auto start = chrono::high_resolution_clock::now();
float TickCounter = 0;
void SetScrollClanTag(string Tag)
{
    
    if(!vars.misc.clantag)
        return;
    
    int TagLength = (int)Tag.length();
    string Space;
    
    for (int i = 0; i < TagLength; i++)
    {
        Space += " ";
    }
    
    string SpaceTag = Space + Tag + Space;
    
    if (TickCounter / 1000.0f > TagLength * 2)
    {
        start = chrono::high_resolution_clock::now();
    }
    
    string CurrentSubStr = SpaceTag.substr((int)(TickCounter / 1000.0f), TagLength);
    SetClanTag(CurrentSubStr.c_str(), CurrentSubStr.c_str());
    TickCounter = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count();
}














