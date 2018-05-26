//
//  asuswalls.cpp
//  pwned
//
//  Created by Finn Le var on 8/05/17.
//  Copyright © 2017 vlone.cc. All rights reserved.
//

#include "asuswalls.h"

float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;

std::unordered_map<MaterialHandle_t, Color> worldMaterials;
std::unordered_map<MaterialHandle_t, Color> worldMaterials2;

void asuswalls(ClientFrameStage_t stage) {
    
    if(!vars.misc.asuswalls)
        return;
    
    if (!pEngine->IsInGame() && worldMaterials.size() > 0) {
        
        for (const auto& it : worldMaterials) {
            
            IMaterial* mat = pMatSystem->GetMaterial(it.first);
            
            if (!mat)
                continue;
            
            mat->GetColorModulate(&r, &g, &b);
            a = mat->GetAlphaModulation();
            
            mat->ColorModulate(r, g, b);
            mat->AlphaModulate(a);
        }
        
        worldMaterials.clear();
        worldMaterials2.clear();
    }
    
    if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
        return;
    
    for (MaterialHandle_t i = pMatSystem->FirstMaterial(); i != pMatSystem->InvalidMaterial(); i = pMatSystem->NextMaterial(i)) {
        
        IMaterial* mat = pMatSystem->GetMaterial(i);
        
        if (!mat || strcmp(mat->GetTextureGroupName(), TEXTURE_GROUP_WORLD) != 0)
            continue;
        
        if (worldMaterials.find(i) == worldMaterials.end())
        {
            mat->GetColorModulate(&r, &g, &b);
            a = mat->GetAlphaModulation();
            worldMaterials.emplace(i, Color(r, g, b, a));
            worldMaterials2.emplace(i, Color(r, g, b, a));
        }
        
        Color color = (vars.misc.asuswalls && vars.visuals.enabled) ? vars.colors.asus : worldMaterials2.find(i)->second;
        
        if (worldMaterials.at(i) != color) {
            
            float sc = 1.0f/255.0f;
            float w = (float)vars.colors.asus.a() * sc;
            
            mat->ColorModulate(color);
            mat->AlphaModulate(w);
            
            worldMaterials.at(i) = color;
        }
    }
}

/*void PerformNightmode()
{
    static bool bPerformed = false, bLastSetting;
    
    C_BasePlayer* pLocal = pLocal;
    
    static ConVar* sv_skyname = pCvar->FindVar("sv_skyname");
    sv_skyname->nFlags &= ~FCVAR_CHEAT; // something something dont force convars
    
    if(!pLocal || !pEngine->IsConnected() || !pEngine->IsInGame())
        return;
    
    if(!bPerformed)
    {
        for(auto i = pMatSystem->FirstMaterial(); i != pMatSystem->InvalidMaterial(); i = pMatSystem->NextMaterial(i))
        {
            static IMaterial* pMaterial = pMatSystem->GetMaterial(i);
            
            if(!pMaterial || pMaterial->IsErrorMaterial())
                continue;
            
            if(strstr((pMaterial->GetTextureGroupName(), "World") || strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
               {
                   if(bLastSetting)
                   {
                       sv_skyname->SetValue("sky_csgo_night02");
                       pMaterial->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, false); // walls were translucent for me for some odd reason, probably p100 codenz :/
                       pMaterial->ColorModulate(0.15, 0.15, 0.15);
                   }
                   else
                   {
                       sv_skyname->SetValue("vertigoblue_hdr"); // fixme: i was too lazy to backup old value
                       pMaterial->ColorModulate(1.00, 1.00, 1.00);
                   }
               }
               if(bLastSetting != Settings::bVisualNightmode)
               {
                   bLastSetting = Settings::bVisualNightmode;
               }
               }
               }
               */
                   

