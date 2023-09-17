#pragma once

#include <map>
#include <string>
#include "GameMap.hpp"
#include "TileLayer.hpp"
#include "tinyxml.h"


class MapParser
{
public:
    bool Load();
    void Clean();
    inline GameMap* GetMaps(std::string id){return m_MapDict[id]; }
    inline static MapParser* GetInstance(){return s_Instance = (s_Instance != nullptr ) ? s_Instance: new MapParser();}




private:
    MapParser(){};
    static MapParser* s_Instance;
    std::map<std::string, GameMap*> m_MapDict;
    bool Parse(std::string id, std::string source);
    Tileset ParseTileset(TiXmlElement * xmlTileset);
    TileLayer* ParseTileLayer(TiXmlElement * xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);

};