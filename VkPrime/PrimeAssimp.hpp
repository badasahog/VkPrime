#define _SILENCE_CXX17_STRSTREAM_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include <strstream>
#include <bitset>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include<iostream>
#include<fstream>
#include <zlib.h>
typedef uint32_t PrimeAssetID;
uint32_t rawFileLength;
template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}
int ihj = 1;



PrimeAssetID tempID = 0;
struct STRGLang {
    char langCode[4];
    uint32_t langStringOffset;
};
struct STRGTable
{
    uint32_t STRGTableSize;
    std::vector<uint32_t> stringOffsets;
    std::vector<std::string> stringArray;
};
struct STRG 
{
    uint32_t magic;
    uint32_t version;
    uint32_t langCount;
    uint32_t stringCount;
    std::vector<STRGLang> langTable;
    std::vector<STRGTable> stringTables;
};
struct MemoryRelay {
    uint32_t memoryRelayInstanceID;
    uint32_t targetInstanceID;
    uint16_t message;
    bool active;
};
struct AreaDependency {
    PrimeAssetID dependencyAssetID;
    char dependencyType[4];
};

struct AreaDependencies {
    uint32_t garbage;
    uint32_t dependencyCount;
    std::vector<AreaDependency> dependecyArray;
    uint32_t dependecyOffsetCount;
    std::vector<uint32_t> dependencyOffsetArray;
};
struct ConnectingDock {
    uint32_t areaIndex;
    uint32_t dockIndex;
};
struct Dock {
    uint32_t connectingDockCount;
    std::vector<ConnectingDock> connectingDockArray;
    uint32_t dockCoordinateCount;
    std::vector<std::array<float,3>> dockDoordinates;
};
struct AreaModuleDependencies
{
    uint32_t RELModuleCount;
    std::vector<std::string> RELModuleArray;
    uint32_t RELOffsetCount;
    std::vector<uint32_t> RELOffsetArray;
};

struct Area {
    PrimeAssetID areaNameID;
    float areaTransform[12];
    float areaBoundingBox[6];
    PrimeAssetID areaMREA_ID;
    PrimeAssetID internalAreaID;
    uint32_t attachedAreaCount;
    std::vector<uint16_t> attachedAreaIndexArray;
    AreaDependencies dependencies;
    uint32_t dockCount;
    std::vector<Dock> dockArray;
};
struct AudioGroup {
    uint32_t groupID;
    PrimeAssetID AGSC_ID;
};
struct AreaLayerFlags {
    uint32_t layerCount;
    uint64_t layerFlags;
};
struct MLVL {
    uint32_t magic;
    uint32_t version;
    PrimeAssetID worldNameID;
    PrimeAssetID worldSaveInfoID;
    PrimeAssetID defaultSkyboxID;
    uint32_t memoryRelayCount;
    std::vector<MemoryRelay> memoryRelayArray;
    uint32_t areaCount;
    uint32_t garbage1;
    std::vector<Area> areaArray;
    PrimeAssetID worldMapID;
    uint8_t garbage2;
    uint32_t scriptInstanceCount;
    uint32_t audioGroupCount;
    std::vector<AudioGroup> audioGroupArray;
    uint8_t garbage3;
    uint32_t garbage4;
    std::vector<AreaLayerFlags> areaLayerFlags;
    uint32_t layerNameCount;
    std::vector<std::string> layerNameArray;
    uint32_t garbage5;
    std::vector<uint32_t> areaLayerNameOffsetArray;
};
struct Material {
    std::vector<PrimeAssetID> textureFileIDs;
    std::vector<uint32_t> materialEndOffsets;
    std::vector<uint32_t> textureFileIndices;
    std::vector<uint32_t> konstColors;
    std::vector<uint32_t> ColorChannelFlags;
    uint32_t textureCount;
    uint32_t materialCount;
    uint32_t vertexAtributeFlags;
    uint32_t ColorChannelCount;
};

struct MaterialSet {
    uint32_t textureCount;
    std::vector<uint32_t> textureFileIDs;
    uint32_t materialCount;
    std::vector<uint32_t> materialEndOffsets;
    std::vector<Material> materials;
};

struct CMDLSurface {
    float centerPoint[3];
    uint32_t matIndex;
    uint16_t mantissa;
    uint16_t displayListSize;
    uint32_t parentModelPointer;
    uint32_t nextSurfacePointer;
    uint32_t extraDataSize;
    float surfaceNormal[3];
    uint8_t GXFlags;
    uint16_t vertexCount;
    std::vector<uint16_t> pos_indices;
    std::vector<uint16_t> nml_indices;
    std::vector<uint16_t> uvc_indices;

};
struct CMDLGeometry {
    std::vector<glm::vec3> vertexCoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> floatUVCoords;
    std::vector<glm::vec2> shortUVCoords;
    uint32_t surfaceCount;
    std::vector<uint32_t> surfaceOffsets;
    std::vector<CMDLSurface> surfaces;
};

struct CMDL {
    uint32_t magic;
    uint32_t version;
    uint32_t flags;
    float ModelAxisAlignedBoundingBox[6];
    uint32_t dataSectionCount;
    uint32_t MaterialSetCount;
    std::vector<uint32_t> dataSectionSizes;
    std::vector<MaterialSet> materialSets;
    CMDLGeometry geometry;
};

struct MREA {
    uint32_t magic;
    uint32_t version;
    float areaTransform[12];
    uint32_t worldModelCount;
    uint32_t dataSectionCount;
    uint32_t worldGeometrySection;
    uint32_t scriptLayersSection;
    uint32_t collisionSection;
    uint32_t unknownSection;
    uint32_t lightsSection;
    uint32_t visibilityTreeSection;
    uint32_t pathSection;
    uint32_t areaOctreeSection;
    std::vector<uint32_t> dataSectionSizes;
};

struct TXTR 
{
    uint32_t imageFormat;
    uint16_t imageWidth;
    uint16_t imageHeight;
    uint32_t mipMapCount;
};

std::unordered_map<PrimeAssetID, CMDL> CMDLMap;
std::unordered_map<PrimeAssetID, MLVL> MLVLMap;
std::unordered_map<PrimeAssetID, STRG> STRGMap;
std::unordered_map<PrimeAssetID, MREA> MREAMap;

CMDL*       loadCMDL(PrimeAssetID assetID, std::string pakFile); 
MLVL*       loadMLVL(PrimeAssetID assetID, std::string pakFile); 
STRG*       loadSTRG(PrimeAssetID assetID, std::string pakFile);
MREA*       loadMREA(PrimeAssetID assetID, std::string pakFile);

void        loadCMDL(std::vector<char> rawFile, PrimeAssetID AssetID);
void        loadMLVL(std::vector<char> rawFile, PrimeAssetID AssetID);
void        loadSTRG(std::vector<char> rawFile, PrimeAssetID AssetID);
void        loadMREA(std::vector<char> rawFile, PrimeAssetID AssetID);
void loadPak(std::string filename);


std::vector<char> findAsset(PrimeAssetID assetID, std::string pakFile) {
    std::ifstream f("prime/" + pakFile, std::ios::binary);
    if (!f.is_open())
        throw std::invalid_argument("pak file not found");
    int16_t versionNumberMajor;
    int16_t versionNumberMinor;
    int32_t unused;
    int32_t assetCount_namedResourcesTable;
    int32_t assetCount_resourcesTable;


    f.read(reinterpret_cast<char*>(&versionNumberMajor), sizeof(versionNumberMajor));
    f.read(reinterpret_cast<char*>(&versionNumberMinor), sizeof(versionNumberMinor));
    f.read(reinterpret_cast<char*>(&unused), sizeof(unused));
    f.read(reinterpret_cast<char*>(&assetCount_namedResourcesTable), sizeof(assetCount_namedResourcesTable));

    versionNumberMajor = swap_endian<int16_t>(versionNumberMajor);
    versionNumberMinor = swap_endian<int16_t>(versionNumberMinor);
    unused = swap_endian<int32_t>(unused);
    assetCount_namedResourcesTable = swap_endian<int32_t>(assetCount_namedResourcesTable);

    std::cout << "Version Number (Major)    " << versionNumberMajor << std::endl;
    std::cout << "Version Number (Minor)    " << versionNumberMinor << std::endl;
    std::cout << "Unused (should be zero)   " << unused << std::endl;
    std::cout << "assets in table           " << assetCount_namedResourcesTable << std::endl;

    std::cout << f.tellg() << std::endl;

    for (int i = 0; i < assetCount_namedResourcesTable; i++) {
        char fourCC[4];
        int32_t AssetID;
        int32_t nameLength;
        std::vector<char> nameString;

        f.read(fourCC, 4);
        f.read(reinterpret_cast<char*>(&AssetID), sizeof(AssetID));
        f.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        nameLength = swap_endian<int32_t>(nameLength);
        nameString.resize(nameLength);
        f.read(nameString.data(), nameLength);
        std::cout << nameLength << std::endl;


    }

    f.read(reinterpret_cast<char*>(&assetCount_resourcesTable), sizeof(assetCount_resourcesTable));

    assetCount_resourcesTable = swap_endian<int32_t>(assetCount_resourcesTable);
    std::cout << "asset count (resource table)  " << assetCount_resourcesTable << std::endl;
    int32_t compressionFlag;
    char fourCC[4];
    PrimeAssetID AssetID;
    int32_t size;
    int32_t offset;
    uint64_t getLoc = f.tellg();
    do {
        f.read(reinterpret_cast<char*>(&compressionFlag), sizeof(compressionFlag));
        f.read(fourCC, 4);
        f.read(reinterpret_cast<char*>(&AssetID), sizeof(AssetID));
        f.read(reinterpret_cast<char*>(&size), sizeof(size));
        f.read(reinterpret_cast<char*>(&offset), sizeof(offset));
        compressionFlag = swap_endian<int32_t>(compressionFlag);
        AssetID = swap_endian<int32_t>(AssetID);
        size = swap_endian<int32_t>(size);
        offset = swap_endian<int32_t>(offset);
        //std::cout.write(fourCC, 4) << "_" << std::hex << AssetID <<std::dec<< std::endl;
    } while (AssetID != assetID);
    f.seekg(offset);
    if (compressionFlag == 1)
    {
        int32_t decompressedSize;

        f.read(reinterpret_cast<char*>(&decompressedSize), sizeof(decompressedSize));
        decompressedSize = swap_endian<int32_t>(decompressedSize);
        uLong ucompSize = decompressedSize;
        std::vector<char> zlibdata;
        zlibdata.resize(size);

        f.read(zlibdata.data(), size);


        std::vector<char> rawFile;
        rawFile.resize(decompressedSize);

        switch (uncompress((Bytef*)rawFile.data(), &ucompSize, (Bytef*)zlibdata.data(), size))
        {
#ifndef NDEBUG
        case Z_OK:std::cout << "successfully extracted" << std::endl; break;
#endif
        case Z_STREAM_END:std::cout << "FATAL ERROR Z_STREAM_END" << std::endl; break;
        case Z_NEED_DICT:std::cout << "FATAL ERROR Z_NEED_DICT" << std::endl; break;
        case Z_ERRNO:std::cout << "FATAL ERROR Z_ERRNO" << std::endl; break;
        case Z_STREAM_ERROR:std::cout << "FATAL ERROR Z_STREAM_ERROR" << std::endl; break;
        case Z_DATA_ERROR:std::cout << "FATAL ERROR Z_DATA_ERROR" << std::endl; break;
        case Z_MEM_ERROR:std::cout << "FATAL ERROR Z_MEM_ERROR" << std::endl; break;
        case Z_BUF_ERROR:std::cout << "FATAL ERROR Z_BUF_ERROR" << std::endl; break;
        case Z_VERSION_ERROR:std::cout << "FATAL ERROR Z_VERSION_ERROR" << std::endl; break;
        }

        
        rawFileLength = rawFile.size();
        std::cout << rawFileLength << std::endl;
        std::ofstream wf("new_data.dat", std::ios::out | std::ios::binary);
        ihj++;
        for (int i = 0; i < rawFileLength; i++)
            wf.write(&rawFile[i], sizeof(char));
        wf.close();
        return(rawFile);
    }
    else if (compressionFlag == 0)
    {
        std::vector<char> rawFile;
        rawFile.resize(size);

        f.read(rawFile.data(), size);

        //rawFileLength = rawFile.size();
        //std::cout << rawFileLength << std::endl;
        //std::ofstream wf("mlvl.dat", std::ios::out | std::ios::binary);
        //ihj++;
        //for (int i = 0; i < rawFileLength; i++)
        //    wf.write(&rawFile[i], sizeof(char));
        //wf.close();

        return rawFile;
    }
    else
    {
        std::cout << "FLAG READ ERROR: compression flag: " << std::hex << compressionFlag << std::dec << std::endl;
    }
}
STRG* loadSTRG(PrimeAssetID assetID, std::string pakFile)
{
    if ((STRGMap.find(assetID) == STRGMap.end()))
    {
        loadSTRG(findAsset(assetID, pakFile), assetID);
    }

    return &STRGMap[assetID];
}
CMDL* loadCMDL(PrimeAssetID assetID, std::string pakFile) {

    if ((CMDLMap.find(assetID) == CMDLMap.end()))
    {
        loadCMDL(findAsset(assetID, pakFile), assetID);
    }

    return &CMDLMap[assetID];
}

MLVL* loadMLVL(PrimeAssetID assetID, std::string pakFile) {
    if ((MLVLMap.find(assetID) == MLVLMap.end()))
    {
        loadMLVL(findAsset(assetID, pakFile), assetID);
    }

    return &MLVLMap[assetID];
}
MREA* loadMREA(PrimeAssetID assetID, std::string pakFile) {
    if ((MREAMap.find(assetID) == MREAMap.end()))
    {
        loadMREA(findAsset(assetID, pakFile), assetID);
    }

    return &MREAMap[assetID];
}
void loadMREA(std::vector<char> rawFile, PrimeAssetID AssetID)
{
    MREAMap[AssetID].magic = 0xBAD0DADA;
}
void loadMLVL(std::vector<char> rawFile, PrimeAssetID AssetID)
{
    MLVLMap[AssetID].magic = 0xbad0dada;
    uint64_t subGetLoc = 0;
    std::cout << rawFile.size()<<std::endl;
    memcpy(&MLVLMap[AssetID].magic, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].magic));
    MLVLMap[AssetID].magic = swap_endian<int32_t>(MLVLMap[AssetID].magic);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].magic)) << "] magic:" << MLVLMap[AssetID].magic << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].magic);

    memcpy(&MLVLMap[AssetID].version, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].version));
    MLVLMap[AssetID].version = swap_endian<int32_t>(MLVLMap[AssetID].version);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].version)) << "] version:" << MLVLMap[AssetID].version << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].version);

    memcpy(&MLVLMap[AssetID].worldNameID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].worldNameID));
    MLVLMap[AssetID].worldNameID = swap_endian<PrimeAssetID>(MLVLMap[AssetID].worldNameID);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].worldNameID)) << "] worldNameID:" << MLVLMap[AssetID].worldNameID << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].worldNameID);

    memcpy(&MLVLMap[AssetID].worldSaveInfoID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].worldSaveInfoID));
    MLVLMap[AssetID].worldSaveInfoID = swap_endian<PrimeAssetID>(MLVLMap[AssetID].worldSaveInfoID);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].worldSaveInfoID)) << "] worldSaveInfoID:" << MLVLMap[AssetID].worldSaveInfoID << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].worldSaveInfoID);

    memcpy(&MLVLMap[AssetID].defaultSkyboxID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].defaultSkyboxID));
    MLVLMap[AssetID].defaultSkyboxID = swap_endian<PrimeAssetID>(MLVLMap[AssetID].defaultSkyboxID);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].defaultSkyboxID)) << "] defaultSkyboxID:" << MLVLMap[AssetID].defaultSkyboxID << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].defaultSkyboxID);

    memcpy(&MLVLMap[AssetID].memoryRelayCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].memoryRelayCount));
    MLVLMap[AssetID].memoryRelayCount = swap_endian<int32_t>(MLVLMap[AssetID].memoryRelayCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].memoryRelayCount)) <<std::dec<< "] memoryRelayCount:" << MLVLMap[AssetID].memoryRelayCount << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].memoryRelayCount);
    MLVLMap[AssetID].memoryRelayArray.resize(MLVLMap[AssetID].memoryRelayCount);
    for (int i = 0; i < MLVLMap[AssetID].memoryRelayCount; i++)
    {
        MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID = 99;//initialize key

        memcpy(&MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID));
        MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID = swap_endian<int32_t>(MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID)) << "] instace id:" << MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID);

        memcpy(&MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID));
        MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID = swap_endian<int32_t>(MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID))<< "] targetInstanceID:" << MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID);

        memcpy(&MLVLMap[AssetID].memoryRelayArray[i].message, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].memoryRelayArray[i].message));
        MLVLMap[AssetID].memoryRelayArray[i].message = swap_endian<int16_t>(MLVLMap[AssetID].memoryRelayArray[i].message);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].memoryRelayArray[i].message)) << std::dec << "] message:" << MLVLMap[AssetID].memoryRelayArray[i].message << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].memoryRelayArray[i].message);

        memcpy(&MLVLMap[AssetID].memoryRelayArray[i].active, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].memoryRelayArray[i].active));
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].memoryRelayArray[i].active)) << std::dec << "] active:" << MLVLMap[AssetID].memoryRelayArray[i].active << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].memoryRelayArray[i].active);
    }

    memcpy(&MLVLMap[AssetID].areaCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaCount));
    MLVLMap[AssetID].areaCount = swap_endian<int32_t>(MLVLMap[AssetID].areaCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaCount)) << std::dec << "] areaCount:" << MLVLMap[AssetID].areaCount << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].areaCount);

    memcpy(&MLVLMap[AssetID].garbage1, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].garbage1));
    MLVLMap[AssetID].garbage1 = swap_endian<int32_t>(MLVLMap[AssetID].garbage1);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].garbage1)) << std::dec << "] garbage1 (always 1):" << MLVLMap[AssetID].garbage1 << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].garbage1);

    MLVLMap[AssetID].areaArray.resize(MLVLMap[AssetID].areaCount);
    for (int i = 0; i < MLVLMap[AssetID].areaCount; i++)
    {
        memcpy(&MLVLMap[AssetID].areaArray[i].areaNameID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].areaNameID));
        MLVLMap[AssetID].areaArray[i].areaNameID = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].areaNameID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].areaNameID)) << "] area name ID:" << MLVLMap[AssetID].areaArray[i].areaNameID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].areaNameID);

        for (int j = 0; j < 12; j++)
        {
            memcpy(&MLVLMap[AssetID].areaArray[i].areaTransform[j], &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].areaTransform[j]));
            MLVLMap[AssetID].areaArray[i].areaTransform[j] = swap_endian<float>(MLVLMap[AssetID].areaArray[i].areaTransform[j]);
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].areaTransform[j]);
        }

        for (int j = 0; j < 6; j++)
        {
            memcpy(&MLVLMap[AssetID].areaArray[i].areaBoundingBox[j], &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].areaBoundingBox[j]));
            MLVLMap[AssetID].areaArray[i].areaBoundingBox[j] = swap_endian<float>(MLVLMap[AssetID].areaArray[i].areaBoundingBox[j]);
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].areaBoundingBox[j]);
        }

        memcpy(&MLVLMap[AssetID].areaArray[i].areaMREA_ID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].areaMREA_ID));
        MLVLMap[AssetID].areaArray[i].areaMREA_ID = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].areaMREA_ID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].areaMREA_ID)) << "] area MREA ID:" << MLVLMap[AssetID].areaArray[i].areaMREA_ID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].areaMREA_ID);

        memcpy(&MLVLMap[AssetID].areaArray[i].internalAreaID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].internalAreaID));
        MLVLMap[AssetID].areaArray[i].internalAreaID = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].internalAreaID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].internalAreaID)) << "] internalAreaID:" << MLVLMap[AssetID].areaArray[i].internalAreaID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].internalAreaID);

        memcpy(&MLVLMap[AssetID].areaArray[i].attachedAreaCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaCount));
        MLVLMap[AssetID].areaArray[i].attachedAreaCount = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].attachedAreaCount);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaCount)) << "] attachedAreaCount:" << std::dec << MLVLMap[AssetID].areaArray[i].attachedAreaCount << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaCount);


        MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray.resize(MLVLMap[AssetID].areaArray[i].attachedAreaCount);
        for (int j = 0; j < MLVLMap[AssetID].areaArray[i].attachedAreaCount; j++)
        {
            memcpy(&MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j], &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j]));
            MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j] = swap_endian<uint16_t>(MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j]);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j])) << "] attachedAreaIndex:" << std::dec << MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j] << std::endl;
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j]);
        }

        memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.garbage, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dependencies.garbage));
        MLVLMap[AssetID].areaArray[i].dependencies.garbage = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dependencies.garbage);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.garbage)) << "] garbage (always 0):" << std::dec << MLVLMap[AssetID].areaArray[i].dependencies.garbage << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dependencies.garbage);

        memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount));
        MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount)) << "] dependencyCount:" << std::dec << MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount);
        
        MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray.resize(MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount);
        for (int j = 0; j < MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount; j++)
        {
            memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID));
            MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID);
            //std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID)) << "] dependency ID:" << MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID << std::dec << std::endl;
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID);

            memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyType, &rawFile[subGetLoc], 4);
            //std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyType)) << "] dependency type:"; std::cout.write(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyType, 4) << std::endl;
            subGetLoc += 4;
        }

        memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount));
        MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount)) << "] dependecyOffsetCount:" << std::dec << MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount);
        
        MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray.resize(MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount);
        for (int j = 0; j < MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount; j++)
        {
            memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j], &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j]));
            MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j] = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j]);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j])) << "] dependecy offset:" << std::dec << MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j] << std::endl;
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j]);
        }

        memcpy(&MLVLMap[AssetID].areaArray[i].dockCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockCount));
        MLVLMap[AssetID].areaArray[i].dockCount = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dockCount);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dockCount)) << "] dockCount:" << std::dec << MLVLMap[AssetID].areaArray[i].dockCount << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockCount);

        MLVLMap[AssetID].areaArray[i].dockArray.resize(MLVLMap[AssetID].areaArray[i].dockCount);
        for (int j = 0; j < MLVLMap[AssetID].areaArray[i].dockCount; j++)
        {
            memcpy(&MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount));
            MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount)) << "] dockCount:" << std::dec << MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount << std::endl;
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount);

            MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray.resize(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount);
            for (int k = 0; k < MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount; k++)
            {
                memcpy(&MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex));
                MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex);
                std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex)) << "] connecting Dock Area Index:" << std::dec << MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex << std::endl;
                subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex);

                memcpy(&MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex));
                MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex);
                std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex)) << "] connecting Dock Index:" << std::dec << MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex << std::endl;
                subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex);
            }

            memcpy(&MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount));
            MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount)) << "] dockCoordinateCount:" << std::dec << MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount << std::endl;
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount);


            MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates.resize(MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount);

            for (int k = 0; k < MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    memcpy(&MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][l], &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][l]));
                    MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][l] = swap_endian<int32_t>(MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][l]);
                    subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][l]);
                }
                std::cout << std::hex << "[" << (subGetLoc-sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][0]) * 3) << " :: " << (subGetLoc) << "] dockCoordinates:" << std::dec << MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][0] << ", " << MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][0] <<", "<< MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][0]<< std::endl;

            }
        }


    }

    memcpy(&MLVLMap[AssetID].worldMapID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].worldMapID));
    MLVLMap[AssetID].worldMapID = swap_endian<PrimeAssetID>(MLVLMap[AssetID].worldMapID);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].worldMapID)) << "] worldMapID:" << MLVLMap[AssetID].worldMapID << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].worldMapID);
    
    memcpy(&MLVLMap[AssetID].garbage2, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].garbage2));
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].garbage2)) << "] garbage2 (always 0):" << std::dec << MLVLMap[AssetID].garbage2 << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].garbage2);

    memcpy(&MLVLMap[AssetID].scriptInstanceCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].scriptInstanceCount));
    MLVLMap[AssetID].scriptInstanceCount = swap_endian<uint32_t>(MLVLMap[AssetID].scriptInstanceCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].scriptInstanceCount)) << "] scriptInstanceCount:" << std::dec << MLVLMap[AssetID].scriptInstanceCount << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].scriptInstanceCount);

    memcpy(&MLVLMap[AssetID].audioGroupCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].audioGroupCount));
    MLVLMap[AssetID].audioGroupCount = swap_endian<uint32_t>(MLVLMap[AssetID].audioGroupCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].audioGroupCount)) << "] audioGroupCount:" << std::dec << MLVLMap[AssetID].audioGroupCount << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].audioGroupCount);
    
    MLVLMap[AssetID].audioGroupArray.resize(MLVLMap[AssetID].audioGroupCount);

    for (int i = 0; i < MLVLMap[AssetID].audioGroupCount; i++)
    {
        memcpy(&MLVLMap[AssetID].audioGroupArray[i].groupID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].audioGroupArray[i].groupID));
        MLVLMap[AssetID].audioGroupArray[i].groupID = swap_endian<uint32_t>(MLVLMap[AssetID].audioGroupArray[i].groupID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].audioGroupArray[i].groupID)) << "] audio group ID:" << MLVLMap[AssetID].audioGroupArray[i].groupID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].audioGroupArray[i].groupID);

        memcpy(&MLVLMap[AssetID].audioGroupArray[i].AGSC_ID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].audioGroupArray[i].AGSC_ID));
        MLVLMap[AssetID].audioGroupArray[i].AGSC_ID = swap_endian<PrimeAssetID>(MLVLMap[AssetID].audioGroupArray[i].AGSC_ID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].audioGroupArray[i].AGSC_ID)) << "] AGSC_ID:" << MLVLMap[AssetID].audioGroupArray[i].AGSC_ID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].audioGroupArray[i].AGSC_ID);
    }

    memcpy(&MLVLMap[AssetID].garbage3, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].garbage3));
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].garbage3)) << "] garbage3 (always 0):" << std::dec << MLVLMap[AssetID].garbage3 << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].garbage3);

    memcpy(&MLVLMap[AssetID].garbage4, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].garbage4));
    MLVLMap[AssetID].garbage4 = swap_endian<uint32_t>(MLVLMap[AssetID].garbage4);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].garbage4)) << "] garbage4 (equal to area count):" << std::dec << MLVLMap[AssetID].garbage4 << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].garbage4);

    MLVLMap[AssetID].areaLayerFlags.resize(MLVLMap[AssetID].areaCount);
    for (int i = 0; i < MLVLMap[AssetID].areaCount; i++)
    {
        memcpy(&MLVLMap[AssetID].areaLayerFlags[i].layerCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaLayerFlags[i].layerCount));
        MLVLMap[AssetID].areaLayerFlags[i].layerCount = swap_endian<uint32_t>(MLVLMap[AssetID].areaLayerFlags[i].layerCount);
        subGetLoc += sizeof(MLVLMap[AssetID].areaLayerFlags[i].layerCount);

        memcpy(&MLVLMap[AssetID].areaLayerFlags[i].layerFlags, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaLayerFlags[i].layerFlags));
        MLVLMap[AssetID].areaLayerFlags[i].layerFlags = swap_endian<uint64_t>(MLVLMap[AssetID].areaLayerFlags[i].layerFlags);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaLayerFlags[i].layerFlags)) << "] layer "<< MLVLMap[AssetID].areaLayerFlags[i].layerCount <<" flags:" << std::dec << MLVLMap[AssetID].areaLayerFlags[i].layerFlags << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaLayerFlags[i].layerFlags);
    }

    memcpy(&MLVLMap[AssetID].layerNameCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].layerNameCount));
    MLVLMap[AssetID].layerNameCount = swap_endian<uint32_t>(MLVLMap[AssetID].layerNameCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].layerNameCount)) << "] layerNameCount:" << std::dec << MLVLMap[AssetID].layerNameCount << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].layerNameCount);

    MLVLMap[AssetID].layerNameArray.resize(MLVLMap[AssetID].layerNameCount);
    for (int i = 0; i < MLVLMap[AssetID].layerNameCount; i++)
    {
        char temp;
        std::string tempstr = "";
        uint64_t tempAnchor = subGetLoc;
        temp = rawFile[subGetLoc];
        subGetLoc++;
        while (temp != '\0')
        {
            tempstr += temp;
            temp = rawFile[subGetLoc];
            subGetLoc++;
        }

        MLVLMap[AssetID].layerNameArray[i] = tempstr;
        std::cout << std::hex << "[" << tempAnchor << " :: " << subGetLoc << "] layer name "<<i<<": " << std::dec << MLVLMap[AssetID].layerNameArray[i] << std::endl;
    }

    memcpy(&MLVLMap[AssetID].garbage5, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].garbage5));
    MLVLMap[AssetID].garbage5 = swap_endian<uint32_t>(MLVLMap[AssetID].garbage5);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].garbage5)) << "] garbage5 (equal to area count):" << std::dec << MLVLMap[AssetID].garbage5 << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].garbage5);


    MLVLMap[AssetID].areaLayerNameOffsetArray.resize(MLVLMap[AssetID].areaCount);
    for (int i = 0; i < MLVLMap[AssetID].areaCount; i++)
    {
        memcpy(&MLVLMap[AssetID].areaLayerNameOffsetArray[i], &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaLayerNameOffsetArray[i]));
        MLVLMap[AssetID].areaLayerNameOffsetArray[i] = swap_endian<uint32_t>(MLVLMap[AssetID].areaLayerNameOffsetArray[i]);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaLayerNameOffsetArray[i])) << "] areaLayerNameOffset:" << std::dec << MLVLMap[AssetID].areaLayerNameOffsetArray[i] << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaLayerNameOffsetArray[i]);
    }

}
void loadSTRG(std::vector<char> rawFile, PrimeAssetID AssetID)
{
    uint32_t subGetLoc=0;
    //int32_t magic;
    STRGMap[AssetID].magic = 0xBAD0DADA;

    memcpy(&STRGMap[AssetID].magic, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].magic));
    STRGMap[AssetID].magic = swap_endian<int32_t>(STRGMap[AssetID].magic);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].magic)) << "] magic:" << STRGMap[AssetID].magic << std::dec << std::endl;
    subGetLoc += sizeof(STRGMap[AssetID].magic);

    memcpy(&STRGMap[AssetID].version, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].version));
    STRGMap[AssetID].version = swap_endian<int32_t>(STRGMap[AssetID].version);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].version)) << "] version:" << STRGMap[AssetID].version << std::dec << std::endl;
    subGetLoc += sizeof(STRGMap[AssetID].version);

    memcpy(&STRGMap[AssetID].langCount, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].langCount));
    STRGMap[AssetID].langCount = swap_endian<int32_t>(STRGMap[AssetID].langCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].langCount)) << "] langCount:" << STRGMap[AssetID].langCount << std::dec << std::endl;
    subGetLoc += sizeof(STRGMap[AssetID].langCount);

    memcpy(&STRGMap[AssetID].stringCount, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].stringCount));
    STRGMap[AssetID].stringCount = swap_endian<int32_t>(STRGMap[AssetID].stringCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].stringCount)) << "] stringCount:" << STRGMap[AssetID].stringCount << std::dec << std::endl;
    subGetLoc += sizeof(STRGMap[AssetID].stringCount);


    STRGMap[AssetID].langTable.resize(STRGMap[AssetID].langCount);

    for (int i = 0; i < STRGMap[AssetID].langCount; i++) {
        memcpy(&STRGMap[AssetID].langTable[i].langCode, &rawFile[subGetLoc], 4);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].langTable[i].langCode)) << "] Language Code:" << std::dec;std::cout.write(STRGMap[AssetID].langTable[i].langCode,4) << std::endl;
        subGetLoc += 4;

        memcpy(&STRGMap[AssetID].langTable[i].langStringOffset, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].langTable[i].langStringOffset));
        STRGMap[AssetID].langTable[i].langStringOffset = swap_endian<int32_t>(STRGMap[AssetID].langTable[i].langStringOffset);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].langTable[i].langStringOffset)) << "] posOffset:" << STRGMap[AssetID].langTable[i].langStringOffset << std::dec << std::endl;
        subGetLoc += sizeof(STRGMap[AssetID].langTable[i].langStringOffset);
    }
    STRGMap[AssetID].stringTables.resize(STRGMap[AssetID].langCount);
    for (int i = 0; i < STRGMap[AssetID].langCount; i++)
    {
        STRGMap[AssetID].stringTables[i].STRGTableSize = 0;
        //uint32_t stringTableSize;

        memcpy(&STRGMap[AssetID].stringTables[i].STRGTableSize, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].stringTables[i].STRGTableSize));
        STRGMap[AssetID].stringTables[i].STRGTableSize = swap_endian<int32_t>(STRGMap[AssetID].stringTables[i].STRGTableSize);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].stringTables[i].STRGTableSize)) << "] STRGTableSize:" << std::dec << STRGMap[AssetID].stringTables[i].STRGTableSize << std::endl;
        subGetLoc += sizeof(STRGMap[AssetID].stringTables[i].STRGTableSize);

        uint32_t disjointOffset = subGetLoc;

        STRGMap[AssetID].stringTables[i].stringOffsets.resize(STRGMap[AssetID].langCount * STRGMap[AssetID].stringCount);
        for (int j = 0; j < STRGMap[AssetID].stringCount; j++)
        {

            memcpy(&STRGMap[AssetID].stringTables[i].stringOffsets[i*STRGMap[AssetID].stringCount+j], &rawFile[subGetLoc], sizeof(STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j]));
            STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j] = swap_endian<int32_t>(STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j]);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].stringTables[i].stringOffsets[j])) << "] stringOffsets:" << std::dec << STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j] << std::endl;
            subGetLoc += sizeof(STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j]);
        }

        STRGMap[AssetID].stringTables[i].stringArray.resize(STRGMap[AssetID].langCount * STRGMap[AssetID].stringCount);
        for (int j = 0; j < STRGMap[AssetID].stringCount; j++)
        {
            subGetLoc = STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j] + disjointOffset+1;


            char temp;
            std::string tempstr = "";
            
            temp = rawFile[subGetLoc];
            subGetLoc+=2;
            while (temp != '\0')
            {
                tempstr += temp;
                temp = rawFile[subGetLoc];
                subGetLoc+=2;
            }
            
            STRGMap[AssetID].stringTables[i].stringArray[i * STRGMap[AssetID].stringCount + j] = tempstr;
            std::cout << "string: " << STRGMap[AssetID].stringTables[i].stringArray[i * STRGMap[AssetID].stringCount + j] << std::endl;
        }
    }
    
}
void loadCMDL(std::vector<char> rawFile, PrimeAssetID AssetID)
{
    CMDLMap[AssetID].magic = 0xbad0dada;
    uint64_t subGetLoc = 0;
    memcpy(&CMDLMap[AssetID].magic, &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].magic));
    CMDLMap[AssetID].magic = swap_endian<int32_t>(CMDLMap[AssetID].magic);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].magic)) << "] magic:" << CMDLMap[AssetID].magic << std::dec << std::endl;

    subGetLoc += sizeof(CMDLMap[AssetID].magic);

    memcpy(&CMDLMap[AssetID].version, &rawFile[subGetLoc], 4);
    CMDLMap[AssetID].version = swap_endian<int32_t>(CMDLMap[AssetID].version);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].version)) << "] version:" << CMDLMap[AssetID].version << std::dec << std::endl;
    subGetLoc += sizeof(CMDLMap[AssetID].version);

    memcpy(&CMDLMap[AssetID].flags, &rawFile[subGetLoc], 4);
    CMDLMap[AssetID].flags = swap_endian<int32_t>(CMDLMap[AssetID].flags);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].flags)) << "] flags:" << std::endl;
    subGetLoc += sizeof(CMDLMap[AssetID].flags);
    std::cout << "\tIndicates the model is skinned: "<<((CMDLMap[AssetID].flags & 0x1)>0?"1":"0") << std::endl;
    std::cout << "\tToggle short normals:           "<<((CMDLMap[AssetID].flags & 0x2)>0?"1":"0") << std::endl;
    std::cout << "\tEnable short UV array:          "<<((CMDLMap[AssetID].flags & 0x4)>0?"1":"0") << std::endl;
    bool halfPrecisionNormals = ((CMDLMap[AssetID].flags & 0x2) > 0);
    bool halfPrecisionUVs     = ((CMDLMap[AssetID].flags & 0x4) > 0);

    memcpy(CMDLMap[AssetID].ModelAxisAlignedBoundingBox, &rawFile[subGetLoc], sizeof(float) * 6);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(float) * 6) << "] Model Axis-Aligned Bounding Box:";
    for (int ijk = 0; ijk < 6; ijk++)
    {
        CMDLMap[AssetID].ModelAxisAlignedBoundingBox[ijk] = swap_endian<float>(CMDLMap[AssetID].ModelAxisAlignedBoundingBox[ijk]);
        std::cout << CMDLMap[AssetID].ModelAxisAlignedBoundingBox[ijk];
    }
    std::cout << std::dec << std::endl;
    subGetLoc += sizeof(float) * 6;

    memcpy(&CMDLMap[AssetID].dataSectionCount, &rawFile[subGetLoc], 4);
    CMDLMap[AssetID].dataSectionCount = swap_endian<int32_t>(CMDLMap[AssetID].dataSectionCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].dataSectionCount)) << "] data Section Count:" << CMDLMap[AssetID].dataSectionCount << std::dec << std::endl;
    subGetLoc += sizeof(CMDLMap[AssetID].dataSectionCount);

    memcpy(&CMDLMap[AssetID].MaterialSetCount, &rawFile[subGetLoc], 4);
    CMDLMap[AssetID].MaterialSetCount = swap_endian<int32_t>(CMDLMap[AssetID].MaterialSetCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].MaterialSetCount)) << "] Material Set Count:" << CMDLMap[AssetID].MaterialSetCount << std::dec << std::endl;
    subGetLoc += sizeof(CMDLMap[AssetID].MaterialSetCount);

    CMDLMap[AssetID].materialSets.resize(CMDLMap[AssetID].MaterialSetCount);

    CMDLMap[AssetID].dataSectionSizes.resize(CMDLMap[AssetID].dataSectionCount);

    for (int ijk = 0; ijk < CMDLMap[AssetID].dataSectionCount; ijk++)
    {
        memcpy(&CMDLMap[AssetID].dataSectionSizes[ijk], &rawFile[subGetLoc], sizeof(uint32_t));
        CMDLMap[AssetID].dataSectionSizes[ijk] = swap_endian<uint32_t>(CMDLMap[AssetID].dataSectionSizes[ijk]);
        std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc + sizeof(uint32_t) << "]" << "data section " << std::dec << ijk << " size: " << CMDLMap[AssetID].dataSectionSizes[ijk] << std::endl;
        subGetLoc += sizeof(uint32_t);

    }

    subGetLoc += 32 - subGetLoc % 32;

    uint32_t upperGetLoc = subGetLoc;
    std::cout << "reading material data from " << std::hex << subGetLoc << std::dec << std::endl;


    if (true)
        for (int imat = 0; imat < CMDLMap[AssetID].MaterialSetCount; imat++)
        {

            memcpy(&(CMDLMap[AssetID].materialSets[imat].textureCount), &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].materialSets[imat].textureCount));
            CMDLMap[AssetID].materialSets[imat].textureCount = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].textureCount);
            std::cout << "textures: " << CMDLMap[AssetID].materialSets[imat].textureCount << std::endl;
            CMDLMap[AssetID].materialSets[imat].textureFileIDs.resize(CMDLMap[AssetID].materialSets[imat].textureCount);
            memcpy(CMDLMap[AssetID].materialSets[imat].textureFileIDs.data(), &rawFile[subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].textureCount)], sizeof(CMDLMap[AssetID].materialSets[imat].textureFileIDs.data()) * CMDLMap[AssetID].materialSets[imat].textureFileIDs.size());
            for (int tx = 0; tx < CMDLMap[AssetID].materialSets[imat].textureCount; tx++) {
                memcpy(&(CMDLMap[AssetID].materialSets[imat].textureFileIDs[tx]), &rawFile[subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].textureCount) + tx * sizeof(uint32_t)], sizeof(uint32_t));
                CMDLMap[AssetID].materialSets[imat].textureFileIDs[tx] = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].textureFileIDs[tx]);
                std::cout << "texture used: " << std::hex << CMDLMap[AssetID].materialSets[imat].textureFileIDs[tx] << std::dec << std::endl;
            }


            memcpy(&(CMDLMap[AssetID].materialSets[imat].materialCount), &rawFile[subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].textureCount) + CMDLMap[AssetID].materialSets[imat].textureCount * sizeof(uint32_t)], sizeof(CMDLMap[AssetID].materialSets[imat].materialCount));
            CMDLMap[AssetID].materialSets[imat].materialCount = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materialCount);
            std::cout << CMDLMap[AssetID].materialSets[imat].materialCount << std::endl;
            CMDLMap[AssetID].materialSets[imat].materialEndOffsets.resize(CMDLMap[AssetID].materialSets[imat].materialCount);
            for (int mc = 0; mc < CMDLMap[AssetID].materialSets[imat].materialCount; mc++) {
                memcpy(&(CMDLMap[AssetID].materialSets[imat].materialEndOffsets[mc]), &rawFile[subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].textureCount) + CMDLMap[AssetID].materialSets[imat].textureCount * sizeof(uint32_t) + sizeof(CMDLMap[AssetID].materialSets[imat].materialCount) + mc * sizeof(uint32_t)], sizeof(uint32_t));
                CMDLMap[AssetID].materialSets[imat].materialEndOffsets[mc] = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materialEndOffsets[mc]);
                std::cout << "material end offset: " << std::hex << CMDLMap[AssetID].materialSets[imat].materialEndOffsets[mc] << std::dec << std::endl;
            }
            subGetLoc = subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].textureCount) + CMDLMap[AssetID].materialSets[imat].textureCount * sizeof(uint32_t) + sizeof(CMDLMap[AssetID].materialSets[imat].materialCount) + CMDLMap[AssetID].materialSets[imat].materialCount * sizeof(uint32_t);

            uint32_t materialStartingMarker = subGetLoc;

            CMDLMap[AssetID].materialSets[imat].materials.resize(CMDLMap[AssetID].materialSets[imat].materialCount + 5);
            for (int ijk = 0; ijk < CMDLMap[AssetID].materialSets[imat].materialCount; ijk++)
            {
                uint32_t flags;
                memcpy(&flags, &rawFile[subGetLoc], sizeof(flags));
                flags = swap_endian<uint32_t>(flags);
                std::cout << "offset: " << std::hex << subGetLoc << std::dec << std::endl;
                std::cout << "material properties:" << std::endl;
                std::cout << "\tUnused, always set:                                " << ((flags & 0x01) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tUnused, always set:                                " << ((flags & 0x02) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tUnused, never set:                                 " << ((flags & 0x04) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tHas Konst values:                                  " << ((flags & 0x08) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tIs transparent:                                    " << ((flags & 0x10) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tMasked alpha:                                      " << ((flags & 0x20) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tEnable Samus's reflection:                         " << ((flags & 0x40) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tEnable Z-writes:                                   " << ((flags & 0x80) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tEnable Samus's reflection, using the eye position: " << ((flags & 0x100) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tShadow occluder mesh:                              " << ((flags & 0x200) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tEnable indirect texture stage for reflections:     " << ((flags & 0x400) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tIndicates a lightmap is present:                   " << ((flags & 0x800) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tUnused, always set:                                " << ((flags & 0x1000) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tEnable first UV coordinate to use short array:     " << ((flags & 0x2000) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tunused, never set:                                 " << ((flags & 0x4000) > 0 ? "on" : "off") << std::endl;
                std::cout << "\tunused, never set:                                 " << ((flags & 0x8000) > 0 ? "on" : "off") << std::endl;
                subGetLoc += sizeof(flags);
                int32_t TC;
                memcpy(&TC, &rawFile[subGetLoc], sizeof(TC));
                TC = swap_endian<int32_t>(TC);
                std::cout << "Texture Count: " << TC << std::endl;
                subGetLoc += sizeof(TC);
                while (TC > 100) {}
                CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices.resize(TC);
                std::cout << "textures:" << std::endl;
                for (int tx = 0; tx < TC; tx += sizeof(uint32_t)) {
                    memcpy(&(CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices[tx]), &rawFile[subGetLoc + tx], sizeof(uint32_t));
                    CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices[tx] = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices[tx]);
                    //std::cout << CMDLMap[AssetID].materialSets[imat].textureFileIndices[tx] << std::endl;
                    std::cout << "\ttexture: " << std::hex << CMDLMap[AssetID].materialSets[imat].textureFileIDs[CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices[tx]] << std::dec << std::endl;
                }

                subGetLoc += TC * sizeof(uint32_t);

                //uint32_t vertexAtributeFlags;
                memcpy(&CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags, &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags));
                CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags);
                std::cout << "vertex atributes: " << std::endl;
                std::cout << CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags << std::endl;
                std::cout << "\tPosition: " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x000003) > 0 ? "1" : "0") << std::endl;
                std::cout << "\tNormal:   " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x00000C) > 0 ? "1" : "0") << std::endl;
                std::cout << "\tColor 0:  " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x000030) > 0 ? "1" : "0") << std::endl;
                std::cout << "\tColor 1:  " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x0000C0) > 0 ? "1" : "0") << std::endl;
                std::cout << "\tTex 0:    " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x000300) > 0 ? "1" : "0") << std::endl;
                std::cout << "\tTex 1:    " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x000C00) > 0 ? "1" : "0") << std::endl;
                std::cout << "\tTex 2:    " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x003000) > 0 ? "1" : "0") << std::endl;
                std::cout << "\tTex 3:    " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x00C000) > 0 ? "1" : "0") << std::endl;
                std::cout << "\tTex 4:    " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x030000) > 0 ? "1" : "0") << std::endl;
                std::cout << "\tTex 5:    " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x0C0000) > 0 ? "1" : "0") << std::endl;
                std::cout << "\tTex 6:    " << ((CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags & 0x300000) > 0 ? "1" : "0") << std::endl;
                subGetLoc += sizeof(CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags);
                uint32_t groupIndex;
                memcpy(&groupIndex, &rawFile[subGetLoc], sizeof(groupIndex));
                groupIndex = swap_endian<uint32_t>(groupIndex);
                std::cout << "group index: " << groupIndex << std::endl;
                subGetLoc += sizeof(groupIndex);
                if ((flags & 0x08) > 0)
                {
                    uint32_t KonstCount;
                    memcpy(&KonstCount, &rawFile[subGetLoc], sizeof(KonstCount));
                    KonstCount = swap_endian<uint32_t>(KonstCount);
                    std::cout << KonstCount << std::endl;
                    CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors.resize(KonstCount);
                    for (int mc = 0; mc < KonstCount; mc++) {
                        memcpy(&(CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors[mc]), &rawFile[subGetLoc + sizeof(KonstCount) + mc * sizeof(uint32_t)], sizeof(uint32_t));
                        CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors[mc] = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors[mc]);
                        std::cout << "konst color " << mc << ": " << std::hex << CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors[mc] << std::dec << std::endl;
                    }
                    subGetLoc += sizeof(KonstCount) + KonstCount * sizeof(uint32_t);
                }
                std::cout << "offset: " << std::hex << subGetLoc << std::dec << std::endl;
                short blendDestFactor;
                memcpy(&blendDestFactor, &rawFile[subGetLoc], sizeof(blendDestFactor));
                blendDestFactor = swap_endian<short>(blendDestFactor);
                std::cout << "blendDestFactor: " << blendDestFactor << std::endl;
                subGetLoc += sizeof(blendDestFactor);

                short blendSourceFactor;
                memcpy(&blendSourceFactor, &rawFile[subGetLoc], sizeof(blendSourceFactor));
                blendSourceFactor = swap_endian<short>(blendSourceFactor);
                std::cout << "blendSourceFactor: " << blendSourceFactor << std::endl;
                subGetLoc += sizeof(blendSourceFactor);

                if ((flags & 0x400) != 0)
                {
                    uint32_t reflectionIndirectTextureIndex;
                    memcpy(&reflectionIndirectTextureIndex, &rawFile[subGetLoc], sizeof(reflectionIndirectTextureIndex));
                    reflectionIndirectTextureIndex = swap_endian<uint32_t>(reflectionIndirectTextureIndex);
                    std::cout << "reflection Indirect Texture Index: " << reflectionIndirectTextureIndex << std::endl;
                    subGetLoc += sizeof(reflectionIndirectTextureIndex);
                }


                memcpy(&(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount), &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount));
                CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount);
                std::cout << "color channel count: " << CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount << std::endl;
                std::cout << "offset: " << std::hex << subGetLoc << std::dec << std::endl;
                CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags.resize(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount);
                for (int mc = 0; mc < CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount; mc++) {
                    memcpy(&(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags[mc]), &rawFile[subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount) + mc * sizeof(uint32_t)], sizeof(uint32_t));
                    CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags[mc] = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags[mc]);
                    std::cout << "color channel flags: " << CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags[mc] << std::dec << std::endl;
                }
                subGetLoc += sizeof(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount) + CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount * sizeof(uint32_t);


                uint32_t TEVStageCount;
                memcpy(&TEVStageCount, &rawFile[subGetLoc], sizeof(TEVStageCount));
                TEVStageCount = swap_endian<uint32_t>(TEVStageCount);
                std::cout << "TEV Stage Count: " << TEVStageCount << std::endl;
                subGetLoc += sizeof(TEVStageCount);

                subGetLoc = materialStartingMarker + CMDLMap[AssetID].materialSets[imat].materialEndOffsets[ijk];

            }
            upperGetLoc += CMDLMap[AssetID].dataSectionSizes[imat];
            subGetLoc = upperGetLoc;
        }
    else
        for (int ijk = 0; ijk < CMDLMap[AssetID].MaterialSetCount; ijk++)
        {
            subGetLoc += CMDLMap[AssetID].dataSectionSizes[ijk];
        }

    std::cout << "reading geometry data from " << std::hex << subGetLoc << std::dec << std::endl;
    upperGetLoc = subGetLoc;


    CMDLMap[AssetID].geometry.vertexCoords.resize((CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount])/(sizeof(float)*3));

    std::cout << "number of vert coords: " << CMDLMap[AssetID].geometry.vertexCoords.size() << std::endl;
    for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.vertexCoords.size(); ijk++)
    {
        memcpy(&CMDLMap[AssetID].geometry.vertexCoords[ijk].x, &rawFile[subGetLoc], sizeof(float)); subGetLoc += sizeof(float);
        memcpy(&CMDLMap[AssetID].geometry.vertexCoords[ijk].y, &rawFile[subGetLoc], sizeof(float)); subGetLoc += sizeof(float);
        memcpy(&CMDLMap[AssetID].geometry.vertexCoords[ijk].z, &rawFile[subGetLoc], sizeof(float)); subGetLoc += sizeof(float);

        CMDLMap[AssetID].geometry.vertexCoords[ijk].x = swap_endian<float>(CMDLMap[AssetID].geometry.vertexCoords[ijk].x);
        CMDLMap[AssetID].geometry.vertexCoords[ijk].y = swap_endian<float>(CMDLMap[AssetID].geometry.vertexCoords[ijk].y);
        CMDLMap[AssetID].geometry.vertexCoords[ijk].z = swap_endian<float>(CMDLMap[AssetID].geometry.vertexCoords[ijk].z);
    }

    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount];
    subGetLoc = upperGetLoc;

    if(halfPrecisionNormals)
        CMDLMap[AssetID].geometry.normals.resize(CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 1]/(sizeof(short)*3));
    else
        CMDLMap[AssetID].geometry.normals.resize(CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 1]/(sizeof(float)*3));

    std::cout << "number of normal coords: " << CMDLMap[AssetID].geometry.normals.size() << std::endl;

    if (halfPrecisionNormals) {
        short temp1, temp2, temp3;
        for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.normals.size(); ijk++)
        {
            memcpy(&temp1, &rawFile[subGetLoc], sizeof(short)); subGetLoc += sizeof(short);
            memcpy(&temp2, &rawFile[subGetLoc], sizeof(short)); subGetLoc += sizeof(short);
            memcpy(&temp3, &rawFile[subGetLoc], sizeof(short)); subGetLoc += sizeof(short);

            CMDLMap[AssetID].geometry.normals[ijk].x = static_cast<float>(swap_endian<short>(temp1));
            CMDLMap[AssetID].geometry.normals[ijk].y = static_cast<float>(swap_endian<short>(temp2));
            CMDLMap[AssetID].geometry.normals[ijk].z = static_cast<float>(swap_endian<short>(temp3));
        }
    }
    else
    {
        for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.normals.size(); ijk++)
        {
            memcpy(&CMDLMap[AssetID].geometry.normals[ijk].x, &rawFile[subGetLoc], sizeof(float)); subGetLoc += sizeof(float);
            memcpy(&CMDLMap[AssetID].geometry.normals[ijk].y, &rawFile[subGetLoc], sizeof(float)); subGetLoc += sizeof(float);
            memcpy(&CMDLMap[AssetID].geometry.normals[ijk].z, &rawFile[subGetLoc], sizeof(float)); subGetLoc += sizeof(float);

            CMDLMap[AssetID].geometry.normals[ijk].x = swap_endian<float>(CMDLMap[AssetID].geometry.normals[ijk].x);
            CMDLMap[AssetID].geometry.normals[ijk].y = swap_endian<float>(CMDLMap[AssetID].geometry.normals[ijk].y);
            CMDLMap[AssetID].geometry.normals[ijk].z = swap_endian<float>(CMDLMap[AssetID].geometry.normals[ijk].z);
        }
    }
    subGetLoc += sizeof(float) * CMDLMap[AssetID].geometry.normals.size();
    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 1];
    subGetLoc = upperGetLoc;


    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "skipping color data" << std::endl;

    //no need to read color data, it's all empty

    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 2];
    subGetLoc = upperGetLoc;

    CMDLMap[AssetID].geometry.floatUVCoords.resize(CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 3] / (sizeof(float) * 2));

    std::cout << "number of float UV coords: " << CMDLMap[AssetID].geometry.floatUVCoords.size() << std::endl;

    for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.floatUVCoords.size(); ijk++)
    {
        memcpy(&CMDLMap[AssetID].geometry.floatUVCoords[ijk].x, &rawFile[subGetLoc], sizeof(float)); subGetLoc += sizeof(float);
        memcpy(&CMDLMap[AssetID].geometry.floatUVCoords[ijk].y, &rawFile[subGetLoc], sizeof(float)); subGetLoc += sizeof(float);

        CMDLMap[AssetID].geometry.floatUVCoords[ijk].x = swap_endian<float>(CMDLMap[AssetID].geometry.floatUVCoords[ijk].x);
        CMDLMap[AssetID].geometry.floatUVCoords[ijk].y = swap_endian<float>(CMDLMap[AssetID].geometry.floatUVCoords[ijk].y);
    }

    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 3];
    subGetLoc = upperGetLoc;



    CMDLMap[AssetID].geometry.shortUVCoords.resize(CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 4] / (sizeof(short) * 2));

    std::cout << "number of short UV coords: " << CMDLMap[AssetID].geometry.shortUVCoords.size() << std::endl;

    for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.shortUVCoords.size(); ijk++)
    {
        memcpy(&CMDLMap[AssetID].geometry.shortUVCoords[ijk].x, &rawFile[subGetLoc], sizeof(short)); subGetLoc += sizeof(short);
        memcpy(&CMDLMap[AssetID].geometry.shortUVCoords[ijk].y, &rawFile[subGetLoc], sizeof(short)); subGetLoc += sizeof(short);

        CMDLMap[AssetID].geometry.shortUVCoords[ijk].x = swap_endian<short>(CMDLMap[AssetID].geometry.shortUVCoords[ijk].x);
        CMDLMap[AssetID].geometry.shortUVCoords[ijk].y = swap_endian<short>(CMDLMap[AssetID].geometry.shortUVCoords[ijk].y);
    }


    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 4];
    subGetLoc = upperGetLoc;

    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "reading header data" << std::endl;
    //the moment of truth:

    memcpy(&CMDLMap[AssetID].geometry.surfaceCount, &rawFile[subGetLoc], 4);
    CMDLMap[AssetID].geometry.surfaceCount = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaceCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaceCount)) << "] surface count:" << CMDLMap[AssetID].geometry.surfaceCount << std::dec << std::endl;
    subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaceCount);

    CMDLMap[AssetID].geometry.surfaceOffsets.resize(CMDLMap[AssetID].geometry.surfaceCount);

    for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.surfaceCount; ijk++)
    {
        memcpy(&CMDLMap[AssetID].geometry.surfaceOffsets[ijk], &rawFile[subGetLoc], sizeof(uint32_t));
        CMDLMap[AssetID].geometry.surfaceOffsets[ijk] = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaceOffsets[ijk]);
        std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(uint32_t)) << "] surface offset " << ijk << ": " << std::hex << CMDLMap[AssetID].geometry.surfaceOffsets[ijk] << std::dec << std::endl;
        subGetLoc += sizeof(uint32_t);
    }

    //that's the end of this section, on to the next one
    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 5];
    subGetLoc = upperGetLoc;
    CMDLMap[AssetID].geometry.surfaces.resize(CMDLMap[AssetID].geometry.surfaceCount);

    //loop through each surface
    for (int surfaceNum = 0; surfaceNum < CMDLMap[AssetID].geometry.surfaceCount; surfaceNum++)
    {

        for (int ijk = 0; ijk < 3; ijk++)
        {
            memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[ijk], &rawFile[subGetLoc], sizeof(float));
            CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[ijk] = swap_endian<float>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[ijk]);
            subGetLoc += sizeof(float);
        }
        std::cout << "center point: " << CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[0] << ", " << CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[1] << ", " << CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[2] << std::endl;

        memcpy(
            &CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex,
            &rawFile[subGetLoc],
            sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex)
        );
        CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex)) << "] matIndex:" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex << std::dec << std::endl;
        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex);

        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa, &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa));
        CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa = swap_endian<uint16_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa)) << "] mantissa:" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa << std::dec << std::endl;
        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa);

        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize, &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize));
        CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize = swap_endian<uint16_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize)) << "] display list size:" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize << std::dec << std::endl;
        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize);

        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer, &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer));
        CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer)) << "] parentModelPointer (always 0):" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer << std::dec << std::endl;
        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer);

        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer, &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer));
        CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer)) << "] nextSurfacePointer (always 0):" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer << std::dec << std::endl;
        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer);

        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize, &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize));
        CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize)) << "] extraDataSize (always 0):" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize << std::dec << std::endl;
        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize);

        CMDLMap[AssetID].geometry.surfaces.resize(CMDLMap[AssetID].geometry.surfaceCount);
        for (int ijk = 0; ijk < 3; ijk++)
        {
            memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].surfaceNormal[ijk], &rawFile[subGetLoc], sizeof(float));
            CMDLMap[AssetID].geometry.surfaces[surfaceNum].surfaceNormal[ijk] = swap_endian<float>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].surfaceNormal[ijk]);
            subGetLoc += sizeof(float);
        }
        std::cout << "surface normal: " << CMDLMap[AssetID].geometry.surfaces[surfaceNum].surfaceNormal[0] << ", " << CMDLMap[AssetID].geometry.surfaces[surfaceNum].surfaceNormal[1] << ", " << CMDLMap[AssetID].geometry.surfaces[surfaceNum].surfaceNormal[2] << std::endl;



        subGetLoc += CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize;

        //align get location to 32 bytes before reading primatives
        subGetLoc += 32 - subGetLoc % 32;



        //char a = -58;
        //std::cout << "a = " << std::bitset<8>(GXFlags) << std::endl;
        //the second one will have 73
        //todo: read until the gx flag hits zero or it hits the end of the section

        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags, &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags));
        //std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(GXFlags)) << "] GXFlags:" << GXFlags << std::dec << std::endl;
        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags);

        while (CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags > 0)
        {


            std::bitset<8> GXFlagBits(CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags);
            std::cout << std::endl;
            //std::cout << GXFlagBits << std::endl;
            std::cout << "GX_VA_NRM type / size | GX_VA_TEX0 type / size" << std::endl;
            switch (0x7 & CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags) {
            case 0:
                std::cout << " GX_NRM_XYZ / GX_F32  |   GX_TEX_ST / GX_F32" << std::endl;
                break;
            case 1:
                std::cout << " GX_NRM_XYZ / GX_S16  |   GX_TEX_ST / GX_F32" << std::endl;
                break;
            case 2:
                std::cout << " GX_NRM_XYZ / GX_S16  |   GX_TEX_ST / GX_S16" << std::endl;
                break;
            }
            std::cout << "format: ";
            switch (CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags & 0xF8)
            {
            case 0x80:
                std::cout << "Quads" << std::endl;
                break;
            case 0x90:
                std::cout << "Triangles" << std::endl;
                break;
            case 0x98:
                std::cout << "Triangle Strip" << std::endl;
                break;
            case 0xA0:
                std::cout << "Triangle Fan" << std::endl;
                break;
            }
            memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount, &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount));
            CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount = swap_endian<uint16_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount)) << "] vertex count:" << std::dec << CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount << std::dec << std::endl;
            subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount);

            uint16_t pos_index1before = 0;
            uint16_t pos_index2before = 0;
            uint16_t pos_indexwaybefore = 0;

            uint16_t nml_index1before = 0;
            uint16_t nml_index2before = 0;
            uint16_t nml_indexwaybefore = 0;

            uint16_t uvc1_index1before = 0;
            uint16_t uvc1_index2before = 0;
            uint16_t uvc1_indexwaybefore = 0;
            uint16_t uvc2_index1before = 0;
            uint16_t uvc2_index2before = 0;
            uint16_t uvc2_indexwaybefore = 0;
            for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount; ijk++)
            {


                uint16_t pos_vIndex;
                uint16_t nml_vIndex;
                uint16_t uvc1_vIndex;
                uint16_t uvc2_vIndex;
                uint16_t uvc3_vIndex;
                uint16_t uvc4_vIndex;
                uint16_t uvc5_vIndex;
                uint16_t uvc6_vIndex;
                uint16_t uvc7_vIndex;



                if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x3) > 0) {
                    memcpy(&pos_vIndex, &rawFile[subGetLoc], sizeof(pos_vIndex));
                    pos_vIndex = swap_endian<uint16_t>(pos_vIndex);
                    subGetLoc += sizeof(pos_vIndex);
                }
                else
                {
                    std::cout << "epic failure" << std::endl;
                }
                if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC) > 0) {
                    memcpy(&nml_vIndex, &rawFile[subGetLoc], sizeof(nml_vIndex));
                    nml_vIndex = swap_endian<uint16_t>(nml_vIndex);
                    subGetLoc += sizeof(nml_vIndex);
                }
                if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x300) > 0) {
                    memcpy(&uvc1_vIndex, &rawFile[subGetLoc], sizeof(uvc1_vIndex));
                    uvc1_vIndex = swap_endian<uint16_t>(uvc1_vIndex);
                    subGetLoc += sizeof(uvc1_vIndex);
                }
                if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC00) > 0)
                {
                    memcpy(&uvc2_vIndex, &rawFile[subGetLoc], sizeof(uvc2_vIndex));
                    uvc2_vIndex = swap_endian<uint16_t>(uvc2_vIndex);
                    subGetLoc += sizeof(uvc2_vIndex);
                }
                if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x3000) > 0)
                {
                    memcpy(&uvc3_vIndex, &rawFile[subGetLoc], sizeof(uvc3_vIndex));
                    uvc3_vIndex = swap_endian<uint16_t>(uvc3_vIndex);
                    subGetLoc += sizeof(uvc3_vIndex);
                }
                if (ijk == 0) {
                    pos_indexwaybefore = pos_vIndex;
                    nml_indexwaybefore = nml_vIndex;
                    uvc1_indexwaybefore = uvc1_vIndex;
                }
                //std::cout << "vertex " << ijk << " position: " <<
                //    CMDLMap[AssetID].geometry.vertexCoords.data()[vIndex * 3 + 0] << ", " <<
                //    CMDLMap[AssetID].geometry.vertexCoords.data()[vIndex * 3 + 1] << ", " <<
                //    CMDLMap[AssetID].geometry.vertexCoords.data()[vIndex * 3 + 2] <<
                //    std::endl;
                if (((CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags & 0xF8) == 0xA0)) {
                    if (ijk > 1)
                    {
                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x3) > 0)
                        {
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back((pos_indexwaybefore));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back((pos_index1before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back((pos_vIndex));
                        }
                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC) > 0)
                        {
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back((nml_indexwaybefore));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back((nml_index1before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back((nml_vIndex));
                        }
                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x300) > 0)
                        {
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back((uvc1_indexwaybefore));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back((uvc1_index1before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back((uvc1_vIndex));
                        }
                    }
                }
                else if (((CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags & 0xF8) == 0x90))
                {
                    if (ijk > 1 && (ijk + 1) % 3 == 0) {
                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x3) > 0)
                        {
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back((pos_index1before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back((pos_index2before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back((pos_vIndex));
                        }
                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC) > 0)
                        {
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back((nml_index1before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back((nml_index2before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back((nml_vIndex));
                        }
                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x300) > 0)
                        {
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back((uvc1_index1before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back((uvc1_index2before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back((uvc1_vIndex));
                        }
                    }
                }
                else if (((CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags & 0xF8) == 0x98))
                {
                    if (ijk > 1) {
                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x3) > 0)
                        {
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back((pos_index2before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back((pos_index1before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back((pos_vIndex));
                        }
                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC) > 0)
                        {
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back((nml_index2before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back((nml_index1before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back((nml_vIndex));
                        }
                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x300) > 0)
                        {
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back((uvc1_index2before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back((uvc1_index1before));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back((uvc1_vIndex));
                        }

                    }
                }
                else
                {
                    std::cout << "unsupported primitive" << std::endl;
                }
                pos_index2before = pos_index1before;
                pos_index1before = pos_vIndex;
                nml_index2before = nml_index1before;
                nml_index1before = nml_vIndex;
                uvc1_index2before = uvc1_index1before;
                uvc1_index1before = uvc1_vIndex;
                //uvc2_index2before = uvc2_index1before;
                //uvc2_index1before = uvc2_vIndex;


                //if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC) > 0)
                //{
                //    uint16_t vIndex;variable 'pos_vIndex' is being used
                //    memcpy(&vIndex, &rawFile[subGetLoc], sizeof(vIndex));
                //    vIndex = swap_endian<uint16_t>(vIndex);
                //    std::cout << "vertex " << ijk << " normal: " <<
                //        CMDLMap[AssetID].geometry.normals.data()[vIndex * 3 + 0] << ", " <<
                //        CMDLMap[AssetID].geometry.normals.data()[vIndex * 3 + 1] << ", " <<
                //        CMDLMap[AssetID].geometry.normals.data()[vIndex * 3 + 2] <<
                //        std::endl;
                //    subGetLoc += sizeof(vIndex);
                //}
                //
                //
                ////todo: color inputs
                //
                //
                //if ((CMDLMap[AssetID].materialSets.data()[0/*CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0x300) > 0)
                //{
                //    uint16_t vIndex;
                //    memcpy(&vIndex, &rawFile[subGetLoc], sizeof(vIndex));
                //    vIndex = swap_endian<uint16_t>(vIndex);
                //    std::cout << "vertex " << ijk << " UV: " <<
                //        CMDLMap[AssetID].geometry.floatUVCoords.data()[vIndex * 2 + 0] << ", " <<
                //        CMDLMap[AssetID].geometry.floatUVCoords.data()[vIndex * 2 + 1] <<
                //        std::endl;
                //    subGetLoc += sizeof(vIndex);
                //}
                //if ((CMDLMap[AssetID].materialSets.data()[0/*CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0xC00) > 0)
                //{
                //    uint16_t vIndex;
                //    memcpy(&vIndex, &rawFile[subGetLoc], sizeof(vIndex));
                //    vIndex = swap_endian<uint16_t>(vIndex);
                //    std::cout << "vertex " << ijk << " UV: " <<
                //        CMDLMap[AssetID].geometry.floatUVCoords.data()[vIndex * 2 + 0] << ", " <<
                //        CMDLMap[AssetID].geometry.floatUVCoords.data()[vIndex * 2 + 1] <<
                //        std::endl;
                //    subGetLoc += sizeof(vIndex);
                //}
                //


            }
            //0x3       position
            //0xC       normal
            //0x30      color 0
            //0xC0      color 1
            //0x300     texture 0
            //0xC00     texture 1
            //0x3000    texture 2
            //0xC000    texture 3
            //0x30000   texture 4
            //0xC0000   texture 5
            //0x30000   texture 6

            memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags, &rawFile[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags));
            //std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(GXFlags)) << "] GXFlags:" << GXFlags << std::dec << std::endl;

            subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags);


            if (CMDLMap[AssetID].geometry.surfaceOffsets[surfaceNum] < (subGetLoc - upperGetLoc) + 2 * sizeof(uint16_t)) {

                //upperGetLoc += CMDLMap[AssetID].geometry.surfaceOffsets[surfaceNum];
                //subGetLoc = upperGetLoc;
                //subGetLoc = upperGetLoc+ CMDLMap[AssetID].geometry.surfaceOffsets[surfaceNum]+1;
                std::cout << "TRIGGERED TRIGGERED TRIGGERED" << std::endl;
                break;

            }
        }





    }

    //m.startIndex = indices.size();
    //m.vertOffset = vertices.size();
    //
    //vertices.insert(vertices.end(), m.vertices.begin(), m.vertices.end());
    //indices.insert(indices.end(), m.indices.begin(), m.indices.end());
    //
    //m.num_indices = indices.size() - m.startIndex;
    //objects.push_back(m);

    //TODO: temporary:
    //return;
}

void loadPak(std::string filename)
{
    int tempcounter = 0;
    std::ifstream f("prime/" + filename, std::ios::binary);
    if (!f.is_open())
        throw std::invalid_argument("pak file not found");
    int16_t versionNumberMajor;
    int16_t versionNumberMinor;
    int32_t unused;
    int32_t assetCount_namedResourcesTable;
    int32_t assetCount_resourcesTable;


    f.read(reinterpret_cast<char*>(&versionNumberMajor), sizeof(versionNumberMajor));
    f.read(reinterpret_cast<char*>(&versionNumberMinor), sizeof(versionNumberMinor));
    f.read(reinterpret_cast<char*>(&unused), sizeof(unused));
    f.read(reinterpret_cast<char*>(&assetCount_namedResourcesTable), sizeof(assetCount_namedResourcesTable));

    versionNumberMajor = swap_endian<int16_t>(versionNumberMajor);
    versionNumberMinor = swap_endian<int16_t>(versionNumberMinor);
    unused = swap_endian<int32_t>(unused);
    assetCount_namedResourcesTable = swap_endian<int32_t>(assetCount_namedResourcesTable);

    std::cout << "Version Number (Major)    " << versionNumberMajor << std::endl;
    std::cout << "Version Number (Minor)    " << versionNumberMinor << std::endl;
    std::cout << "Unused (should be zero)   " << unused << std::endl;
    std::cout << "assets in table           " << assetCount_namedResourcesTable << std::endl;

    std::cout << f.tellg() << std::endl;

    for (int i = 0; i < assetCount_namedResourcesTable; i++) {
        char fourCC[4];
        int32_t AssetID;
        int32_t nameLength;
        std::vector<char> nameString;

        f.read(fourCC, 4);
        f.read(reinterpret_cast<char*>(&AssetID), sizeof(AssetID));
        f.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        nameLength = swap_endian<int32_t>(nameLength);
        nameString.resize(nameLength);
        f.read(nameString.data(), nameLength);
        std::cout << nameLength << std::endl;


        std::cout << "\tAsset Type              "; std::cout.write(fourCC, 4) << std::endl;
        std::cout << "\tAsset ID                " << AssetID << std::endl;
        std::cout << "\tAsset name              "; std::cout.write(nameString.data(), nameLength) << std::endl;
    }

    f.read(reinterpret_cast<char*>(&assetCount_resourcesTable), sizeof(assetCount_resourcesTable));

    assetCount_resourcesTable = swap_endian<int32_t>(assetCount_resourcesTable);
    std::cout << "asset count (resource table)  " << assetCount_resourcesTable << std::endl;
    //for (int i = 0; i < assetCount_resourcesTable; i++) {
    for (int i = 0; i < 200; i++) {
        int32_t compressionFlag;
        char fourCC[4];
        PrimeAssetID AssetID;
        int32_t size;
        int32_t offset;

        f.read(reinterpret_cast<char*>(&compressionFlag), sizeof(compressionFlag));
        f.read(fourCC, 4);
        f.read(reinterpret_cast<char*>(&AssetID), sizeof(AssetID));
        f.read(reinterpret_cast<char*>(&size), sizeof(size));
        f.read(reinterpret_cast<char*>(&offset), sizeof(offset));



        compressionFlag = swap_endian<int32_t>(compressionFlag);
        AssetID = swap_endian<int32_t>(AssetID);
        size = swap_endian<int32_t>(size);
        offset = swap_endian<int32_t>(offset);

        std::cout << "\tcompression flag        " << compressionFlag << std::endl;
        std::cout << "\tAsset Type              "; std::cout.write(fourCC, 4) << std::endl;
        std::cout << "\tAsset ID                " << std::hex << AssetID << std::dec << std::endl;
        std::cout << "\tsize                    " << size << std::endl;
        std::cout << "\toffset                  " << std::hex << offset << std::dec << std::endl;
        uint64_t getLoc = f.tellg();
        f.seekg(offset);
        if (compressionFlag == 1)
        {
            int32_t decompressedSize;

            f.read(reinterpret_cast<char*>(&decompressedSize), sizeof(decompressedSize));
            decompressedSize = swap_endian<int32_t>(decompressedSize);
            //std::cout << "\t\tdecompressed size: " << decompressedSize << std::endl;
            uLong ucompSize = decompressedSize;
            std::vector<char> zlibdata;
            zlibdata.resize(size);

            f.read(zlibdata.data(), size);


            std::vector<char> rawFile;
            rawFile.resize(decompressedSize);

            switch (uncompress((Bytef*)rawFile.data(), &ucompSize, (Bytef*)zlibdata.data(), size))
            {
#ifndef NDEBUG
            case Z_OK:std::cout << "successfully extracted" << std::endl; break;
#endif
            case Z_STREAM_END:std::cout << "FATAL ERROR Z_STREAM_END" << std::endl; break;
            case Z_NEED_DICT:std::cout << "FATAL ERROR Z_NEED_DICT" << std::endl; break;
            case Z_ERRNO:std::cout << "FATAL ERROR Z_ERRNO" << std::endl; break;
            case Z_STREAM_ERROR:std::cout << "FATAL ERROR Z_STREAM_ERROR" << std::endl; break;
            case Z_DATA_ERROR:std::cout << "FATAL ERROR Z_DATA_ERROR" << std::endl; break;
            case Z_MEM_ERROR:std::cout << "FATAL ERROR Z_MEM_ERROR" << std::endl; break;
            case Z_BUF_ERROR:std::cout << "FATAL ERROR Z_BUF_ERROR" << std::endl; break;
            case Z_VERSION_ERROR:std::cout << "FATAL ERROR Z_VERSION_ERROR" << std::endl; break;
            }
            if (fourCC[0] == 'S' && fourCC[1] == 'T' && fourCC[2] == 'R' && fourCC[3] == 'G')
            {
                int32_t txtrFormat = (rawFile[0] << 24) | (rawFile[1] << 16) | (rawFile[2] << 8) | rawFile[3];
                //std::cout << "\t\ttexture format: " << std::hex << txtrFormat << std::dec << std::endl;
                uint16_t txtrWidth = (rawFile[4] << 8) | rawFile[5];
                //std::cout << "\t\ttexture width: " << txtrWidth << std::endl;
                uint16_t txtrHeight = (rawFile[6] << 8) | rawFile[7];
                //std::cout << "\t\ttexture height: " << txtrHeight << std::endl;
                int32_t mipCount = (rawFile[8] << 24) | (rawFile[9] << 16) | (rawFile[10] << 8) | rawFile[11];
                //std::cout << "\t\tmip count: " << mipCount << std::endl;
            }
            else if (fourCC[0] == 'M' && fourCC[1] == 'L' && fourCC[2] == 'V' && fourCC[3] == 'L')
            {
                std::cout << "mlevel found****************************************" << std::endl;
            }
            else if (fourCC[0] == 'T' && fourCC[1] == 'X' && fourCC[2] == 'T' && fourCC[3] == 'R')
            {
                uint64_t subGetLoc = 0;

                uint32_t txtrFormat;

                memcpy(&txtrFormat, &rawFile[subGetLoc], sizeof(txtrFormat));
                txtrFormat = swap_endian<uint32_t>(txtrFormat);
                std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrFormat)) << "] texture format:" << txtrFormat << std::dec << std::endl;
                subGetLoc += sizeof(txtrFormat);

                uint16_t txtrWidth;

                memcpy(&txtrWidth, &rawFile[subGetLoc], sizeof(txtrWidth));
                txtrWidth = swap_endian<uint16_t>(txtrWidth);
                std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrWidth)) << "] texture width:" << txtrWidth << std::dec << std::endl;
                subGetLoc += sizeof(txtrWidth);

                uint16_t txtrHeight;

                memcpy(&txtrHeight, &rawFile[subGetLoc], sizeof(txtrHeight));
                txtrHeight = swap_endian<uint16_t>(txtrHeight);
                std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrHeight)) << "] texture height:" << txtrHeight << std::dec << std::endl;
                subGetLoc += sizeof(txtrHeight);

                uint32_t mipCount;

                memcpy(&mipCount, &rawFile[subGetLoc], sizeof(mipCount));
                mipCount = swap_endian<uint32_t>(mipCount);
                std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(mipCount)) << "] mip count:" << mipCount << std::dec << std::endl;
                subGetLoc += sizeof(mipCount);

                if (txtrFormat == 0x4 || txtrFormat == 0x5)
                {
                    //TODO: read pallettes
                }

                // if (txtrFormat == 0xa)
                // {
                //     std::vector<uint8_t> textureChunk;
                //     textureChunk.resize(32);
                //     memcpy(&textureChunk, &rawFile[subGetLoc], 32);
                //     std::vector<uint8_t> imageChunk;
                //     imageChunk.resize(8 * 8);
                //
                //     //squish::Decompress(&imageChunk.data()[0], &textureChunk.data()[0], txtrFormat);
                //
                // }

            }
            else if (fourCC[0] == 'C' && fourCC[1] == 'M' && fourCC[2] == 'D' && fourCC[3] == 'L')
            {
                //if (tempcounter > 0)
                //    continue;
                //else
                loadCMDL(rawFile, AssetID);
                rawFileLength = rawFile.size();
                std::ofstream wf(ihj + "_data.dat", std::ios::out | std::ios::binary);
                ihj++;
                for (int i = 0; i < rawFileLength; i++)
                    wf.write(&rawFile[i], sizeof(char));
                wf.close();

                tempcounter++;
            }
        }
        else if (compressionFlag == 0)
        {
            if (fourCC[0] == 'S' && fourCC[1] == 'T' && fourCC[2] == 'R' && fourCC[3] == 'G')
            {
                //TODO
            }
            else {
                std::cout << fourCC[0] << fourCC[1] << fourCC[2] << fourCC[3] << std::endl;
            }
        }
        else
        {
            std::cout << "compression flag: " << std::hex << compressionFlag << std::dec << std::endl;
            break;
        }
        f.seekg(getLoc);
    }
}