#pragma once

class ccombobox // this class only handles all the open checks for the combo boxes, nothing more
{
public:
    
    // Anti aim
    bool aaY_opend;
    bool aaX_opend;
    bool FaaY_opend;
    bool MaaY_opend;
    bool AaaY_opend;
    // Chams
    bool hands_opend;
    bool weapons_opend;
    bool players_opend;
    // Menu
    bool colors_opend;
    // Misc
    bool fakelag_opend;
    bool clantag_opend;
    bool resolver_opend;
    bool hitscan_opend;
    bool fakewalk_opend;
    bool indicatorAA_opend;
    // For aa corrections
    bool playerlist_opend_x[64];
    bool playerlist_opend_y[64];
    
    // Config
    bool mCol_opend;
    bool cfg_opend;
    
    // For text input
    bool misc_clantag, misc_name, misc_changename;

};

class cVariables : public ccombobox
{
public:
    
    bool menu               = false;
    int  buttonPadding      = 24;
    int  playerTab          = 0;
    int  inputIndex         = 0;
    bool cfgInit = false;
    
    class cAimbot
    {
    public:
        
        bool enabled     = true;         // Enable
        bool silent      = true;         // Silent Aim ob
        int  FovToPlayer = 180;          // Aimbot Fov
        int  hitbox      = 0;            // Hitbox
        int  pointscale  = 80;           // Pointscale
        bool trigger     = false;        // Will shoot when an enemy is in your crosshair
        bool prediction  = true;         // Player prediction
        bool autowall    = true;         // Shoots through walls if calulated damage is higher than set amount
        int  mindmg      = 5;            // Autowall min damage
        bool hitchance  = true;         // Hitchance
        int accuracyhithcance = 40;     // Hitchance Accuacry
        bool hitscan    = true;         // Hitscan
        int hitscantype = 0;            // HItscan Types
        bool autoshoot  = false;        // Shoots for you
        bool autoscope  = true;         // Autoscope
        bool autostop   = false;        // auto stop
        bool autopistol = true;         // Pistol is like AK
        bool autocock   = true;         // Auto Revovler
        bool autozeus   = true;         // Zeus when something is close enough
        bool rcs        = false;        // Recoil control system
        int rcsf        = 0;            // Recoil control
        bool Yawresolver= false;        // Resolver
        int yresolve    = 0;            // different resolver
        bool backtrack = false;
        

    }aimbot;
    
    class cVisuals
    {
    public:
        
        bool enabled    = true;        // Enable
        bool enemyonly  = true;        // Enemy only
        bool visonly    = false;       // Visual only
        bool box        = false;       // Box ESP
        bool name       = true;        // Name ESP
        bool health     = true;        // Health Bar
        bool healthtext = true;        // Health Text
        bool armour     = false;       // Armour Bar
        bool skeleton   = true;        // Skeleton ESP
        bool snapline   = false;       // Snaplines obv
        bool rcrosshair = true;       // Recoil Crosshair (Shows but doesn't move)
        bool scrosshair = false;       // Sniper Crosshair
        bool defusing   = true;        // Defusing ESP
        bool rescuing   = false;       // Hostage rescue and carrying esp
        bool scoped     = true;        // Scoped ESP
        bool weapons    = false;       // Dropped Weapons
        bool bombtimer  = true;        // Bomb Timer
        bool skinc      = true;        // SkinChanger
        bool nosmoke    = true;        // No Smoke
        bool antiaim_indicator= true;  // Manual AA idicator
        int indicatorAA_types = 2;     // antiaim idicator
        bool antiaiminfos= true;       // AntiAim Lines
        bool direction = true;         // Enemy Direction
        bool hitmarker  = true;        // Aimware Hitmarkers
    

        // Chams
        bool chams      = true;         // Player Chams
        bool handchams  = false;        // Handchams obv
        bool weaponchams= false;        // Weapon chams obv
        int weaponType  = 1;            // Weapon Type 0 - Lit 1 - Texture 2 - Wireframe
        int handsType   = 1;            // Hand   Type 0 - Lit 1 - Texture 2 - Wireframe
        int playersType = 1;            // Player Type 0 - Lit 1 - Texture
        
        int weaponchams_alpha   = 255;  // Weapon Chams Alpha / opacity
        int handchams_alpha     = 255;  // Hand   Chams Alpha / opacity
        int playerchams_alpha   = 255;  // Player Chams Alpha / opacity
        
    }visuals;
    
    class cMisc
    {
    public:
        
        bool enabled        = true;     // Enabled
        bool antiuntrust    = true;     // Anti Untrust KEEP ON AT ALL TIMES UNLESS YOU KNOW WHAT YOURE DOING
        bool norecoil       = true;     // Basically RCS without slider
        bool novisual       = true;     // No visual recoil ofc
        bool bhop           = true;     // BunnyHop
        bool autostrafe     = true;     // Strafes for you ofc
        bool cstrafe        = false;    // Circle strafes
        bool airstuck       = false;    // Airstuck
        bool fovt           = false;    // Fov Changer Enabled
        int fov             = 10;       // FOV changer
        
        // Different Clantags
        bool clantag         = true;    // Enables clantag
        int clantagtype      = 0;       // different clantag types
        bool gamesense       = false;   // gamesense clan tag
        bool vangeme         = false;   // vange.me clan tag
        bool aimware         = false;   // aimware clan tag ;P
        
        bool showrank       = true;     // Show everyboys rank in MM
        bool spammer        = false;    // Chat spammer
        bool noflash        = true;     // Disabled flashbangs
        int flashalpha      = 255.f;    // How "flashed" you are
        bool noscope        = true;     // Noscope
        
        bool fakewalk       = true;     // Fake Walk
        bool fakelag        = false;    // Fake lag enable (WIP)
        int fakelagfactor   = 0;        // Fake Lag (WIP)
        int fakelagtype     = 0;        // 0 Normal - 1 Adaptive
        bool adaptive       = false;    //
    
        bool nightmode      = false;    // Night Mode
        bool asuswalls      = false;    // asuswalls - see through walls
        bool worldpaint     = false;    // World Paint
        bool changesky      = false;    // Changes Sky
        bool antiscreenshot = false;    // Anti screenshot
        bool showspectators = false;    // Spectator List
        
        // AntiAim
        bool antiaim        = false;    // Anti aims / "spinbot"
        bool thirdpersonmode= false;    // Thirdperson
        bool attargets      = true;     // AtTargets ofc
        bool fakeaa         = false;    // Fake anti aim
        int delta           = 115;      // LBY Delta
        int aaY             = 0;        // Yaw AntiAim
        int aaX             = 0;        // Pitch AntiAim
        int FaaY            = 0;        // Yaw Fake anti aim (Thnx Ziwiiz)
        int MaaY            = 0;        // Y Moving anti aim
        int AaaY            = 0;        // Air  Yaw Moving antiaim
        int Yoffset         = 0;        // Yaw Offset
        int FYoffset        = 0;        // Fake Yaw Offset
        bool antiResolverFlip= false;   //lby flip

    }misc;

    class cColors
    {
    public:
        
        int combo   = 0;
        
        Color ctchams;
        Color tchams;
        
        Color ctchams_ign;
        Color tchams_ign;
        
        Color tbox;
        Color tbox_ign;
        
        Color ctbox;
        Color ctbox_ign;
        
        Color hands;
        Color weapon;
        
        Color scope;
        Color sky;
        Color world;
        
        Color asus = Color(255, 255, 255, 150);
        
    }colors;
    
};

struct Corrections
{
    float x, y;
    bool whitelist;
    bool resolved;
    bool baim;
    
    int dropdown_x = 0;
    int dropdown_y = 0;
};


extern cVariables vars;
extern Corrections gCorrections[64];
