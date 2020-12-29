#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include <bitset>
#include <iostream>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <zlib.h>
#include "GXCore.hpp"
#include "FileReader.hpp"


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

PrimeAssetID tempID = 0;

#pragma pack(push, 1)
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
    std::vector<std::array<float, 3>> dockDoordinates;
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
    uint32_t ColorChannelFlags;
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

struct MPSurface {
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
    void clearAll()
    {
        centerPoint[0] = 0;
        centerPoint[1] = 0;
        centerPoint[2] = 0;
        matIndex = 0;
        mantissa = 0;
        displayListSize = 0;
        parentModelPointer = 0;
        nextSurfacePointer = 0;
        extraDataSize = 0;
        surfaceNormal[0] = 0;
        surfaceNormal[1] = 0;
        surfaceNormal[2] = 0;
        GXFlags = 0;
        vertexCount = 0;
        pos_indices.clear();
        nml_indices.clear();
        uvc_indices.clear();
    }

};
struct MPGeometry {
    std::vector<glm::vec3> vertexCoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> floatUVCoords;
    std::vector<glm::vec2> shortUVCoords;
    uint32_t surfaceCount;
    std::vector<uint32_t> surfaceOffsets;
    std::vector<MPSurface> surfaces;
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
    MPGeometry geometry;
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
struct DXT1
{

};
struct TXTR
{
    uint32_t imageFormat;
    uint16_t imageWidth;
    uint16_t imageHeight;
    uint32_t mipMapCount;
    std::vector<unsigned char> PCpixels;
};
#pragma(pop)



std::unordered_map<PrimeAssetID, CMDL> CMDLMap;
std::unordered_map<PrimeAssetID, MLVL> MLVLMap;
std::unordered_map<PrimeAssetID, STRG> STRGMap;
std::unordered_map<PrimeAssetID, MREA> MREAMap;
std::unordered_map<PrimeAssetID, TXTR> TXTRMap;

CMDL* loadCMDL(PrimeAssetID assetID, std::string pakFile);
MLVL* loadMLVL(PrimeAssetID assetID, std::string pakFile);
STRG* loadSTRG(PrimeAssetID assetID, std::string pakFile);
MREA* loadMREA(PrimeAssetID assetID, std::string pakFile);
TXTR* loadTXTR(PrimeAssetID assetID, std::string pakFile);

void        loadCMDL(std::vector<char> rawFile, PrimeAssetID AssetID);
void        loadMLVL(std::vector<char> rawFile, PrimeAssetID AssetID);
void        loadSTRG(std::vector<char> rawFile, PrimeAssetID AssetID);
void        loadMREA(std::vector<char> rawFile, PrimeAssetID AssetID);
void        loadTXTR(std::vector<char> rawFile, PrimeAssetID AssetID);
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

    versionNumberMajor = _byteswap_ushort(versionNumberMajor);
    versionNumberMinor = _byteswap_ushort(versionNumberMinor);
    unused = _byteswap_ulong(unused);
    assetCount_namedResourcesTable = _byteswap_ulong(assetCount_namedResourcesTable);

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
        nameLength = _byteswap_ulong(nameLength);
        nameString.resize(nameLength);
        f.read(nameString.data(), nameLength);
        std::cout << nameLength << std::endl;


    }

    f.read(reinterpret_cast<char*>(&assetCount_resourcesTable), sizeof(assetCount_resourcesTable));

    assetCount_resourcesTable = _byteswap_ulong(assetCount_resourcesTable);
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
        compressionFlag = _byteswap_ulong(compressionFlag);
        AssetID = _byteswap_ulong(AssetID);
        size = _byteswap_ulong(size);
        offset = _byteswap_ulong(offset);
        //std::cout.write(fourCC, 4) << "_" << std::hex << AssetID <<std::dec<< std::endl;
    } while (AssetID != assetID);
    f.seekg(offset);
    if (compressionFlag == 1)
    {
        int32_t decompressedSize;

        f.read(reinterpret_cast<char*>(&decompressedSize), sizeof(decompressedSize));
        decompressedSize = _byteswap_ulong(decompressedSize);
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
TXTR* loadTXTR(PrimeAssetID assetID, std::string pakFile) {
    if ((TXTRMap.find(assetID) == TXTRMap.end()))
    {
        loadTXTR(findAsset(assetID, pakFile), assetID);
    }

    return &TXTRMap[assetID];
}





static int Unpack565(uint8_t const* packed, uint8_t* colour)
{
    // build the packed value - GCN: indices reversed
    int value = (int)packed[1] | ((int)packed[0] << 8);

    // get the components in the stored range
    uint8_t red = (uint8_t)((value >> 11) & 0x1f);
    uint8_t green = (uint8_t)((value >> 5) & 0x3f);
    uint8_t blue = (uint8_t)(value & 0x1f);

    // scale up to 8 bits
    colour[0] = (red << 3) | (red >> 2);
    colour[1] = (green << 2) | (green >> 4);
    colour[2] = (blue << 3) | (blue >> 2);
    colour[3] = 255;

    // return the value
    return value;
}

void DecompressColourGCN(uint32_t texWidth, uint8_t* rgba, void const* block)
{
    // get the block bytes
    uint8_t const* bytes = reinterpret_cast<uint8_t const*>(block);

    // unpack the endpoints
    uint8_t codes[16];
    int a = Unpack565(bytes, codes);
    int b = Unpack565(bytes + 2, codes + 4);

    // generate the midpoints
    for (int i = 0; i < 3; ++i)
    {
        int c = codes[i];
        int d = codes[4 + i];

        if (a <= b)
        {
            codes[8 + i] = (uint8_t)((c + d) / 2);
            // GCN: Use midpoint RGB rather than black
            codes[12 + i] = codes[8 + i];
        }
        else
        {
            // GCN: 3/8 blend rather than 1/3
            codes[8 + i] = (uint8_t)((c * 5 + d * 3) >> 3);
            codes[12 + i] = (uint8_t)((c * 3 + d * 5) >> 3);
        }
    }

    // fill in alpha for the intermediate values
    codes[8 + 3] = 255;
    codes[12 + 3] = (a <= b) ? 0 : 255;

    // unpack the indices
    uint8_t indices[16];
    for (int i = 0; i < 4; ++i)
    {
        uint8_t* ind = indices + 4 * i;
        uint8_t packed = bytes[4 + i];

        // GCN: indices reversed
        ind[3] = packed & 0x3;
        ind[2] = (packed >> 2) & 0x3;
        ind[1] = (packed >> 4) & 0x3;
        ind[0] = (packed >> 6) & 0x3;
    }

    // store out the colours
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
        {
            uint8_t offset = 4 * indices[y * 4 + x];
            for (int j = 0; j < 4; ++j)
            {
                rgba[4 * ((y * texWidth + x)) + (j)] = codes[offset + j];//+ (i - 8 < 0 ? 0 : 128)
            }// - i % 4
        }
}








void loadTXTR(std::vector<char> rawFile, PrimeAssetID AssetID)
{
    TXTRMap[AssetID].imageFormat = 0xBAD0DADA;
    uint64_t subGetLoc = 0;

    memcpy(&TXTRMap[AssetID].imageFormat, &rawFile[subGetLoc], sizeof(TXTRMap[AssetID].imageFormat));
    TXTRMap[AssetID].imageFormat = _byteswap_ulong(TXTRMap[AssetID].imageFormat);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(TXTRMap[AssetID].imageFormat)) << "] image format:" << TXTRMap[AssetID].imageFormat << std::dec << std::endl;
    subGetLoc += sizeof(TXTRMap[AssetID].imageFormat);

    memcpy(&TXTRMap[AssetID].imageWidth, &rawFile[subGetLoc], sizeof(TXTRMap[AssetID].imageWidth));
    TXTRMap[AssetID].imageWidth = _byteswap_ushort(TXTRMap[AssetID].imageWidth);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(TXTRMap[AssetID].imageWidth)) << "] image width:" << std::dec << TXTRMap[AssetID].imageWidth << std::endl;
    subGetLoc += sizeof(TXTRMap[AssetID].imageWidth);

    memcpy(&TXTRMap[AssetID].imageHeight, &rawFile[subGetLoc], sizeof(TXTRMap[AssetID].imageHeight));
    TXTRMap[AssetID].imageHeight = _byteswap_ushort(TXTRMap[AssetID].imageHeight);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(TXTRMap[AssetID].imageHeight)) << "] image height:" << std::dec << TXTRMap[AssetID].imageHeight << std::endl;
    subGetLoc += sizeof(TXTRMap[AssetID].imageHeight);

    memcpy(&TXTRMap[AssetID].mipMapCount, &rawFile[subGetLoc], sizeof(TXTRMap[AssetID].mipMapCount));
    TXTRMap[AssetID].mipMapCount = _byteswap_ulong(TXTRMap[AssetID].mipMapCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(TXTRMap[AssetID].mipMapCount)) << "] mipmap count:" << std::dec << TXTRMap[AssetID].mipMapCount << std::endl;
    subGetLoc += sizeof(TXTRMap[AssetID].mipMapCount);

    int HBlocks = (TXTRMap[AssetID].imageWidth + 8 - 1) / 8;
    int VBlocks = (TXTRMap[AssetID].imageHeight + 8 - 1) / 8;


    int HBlocksm1 = (TXTRMap[AssetID].imageWidth / 2 + 8 - 1) / 8;
    int VBlocksm1 = (TXTRMap[AssetID].imageHeight / 2 + 8 - 1) / 8;
    int HBlocksm2 = (TXTRMap[AssetID].imageWidth / 4 + 8 - 1) / 8;
    int VBlocksm2 = (TXTRMap[AssetID].imageHeight / 4 + 8 - 1) / 8;
    int HBlocksm3 = (TXTRMap[AssetID].imageWidth / 8 + 8 - 1) / 8;
    int VBlocksm3 = (TXTRMap[AssetID].imageHeight / 8 + 8 - 1) / 8;
    int numblocks = HBlocks * VBlocks;

    int blockSize = 32;

    int imageSize = numblocks * blockSize;

    std::cout << "texel data size: " << (rawFile.size() - subGetLoc) / 32 << std::endl;
    std::cout << "texel data size (predicted): " << imageSize / 32 << std::endl;

    TXTRMap[AssetID].PCpixels.resize(TXTRMap[AssetID].imageWidth * TXTRMap[AssetID].imageHeight * 4);

    for (int y = 0; y < TXTRMap[AssetID].imageHeight; y++)
    {
        for (int x = 0; x < TXTRMap[AssetID].imageWidth; x++)
        {
            TXTRMap[AssetID].PCpixels[(TXTRMap[AssetID].imageWidth * y + x) * 4 + 0] = (x + 1) % 16 < 2 || (y + 1) % 16 < 2 ? 0 : 255;
            TXTRMap[AssetID].PCpixels[(TXTRMap[AssetID].imageWidth * y + x) * 4 + 1] = (x + 1) % 16 < 2 || (y + 1) % 16 < 2 ? 255 : 0;
            TXTRMap[AssetID].PCpixels[(TXTRMap[AssetID].imageWidth * y + x) * 4 + 2] = 0;
            TXTRMap[AssetID].PCpixels[(TXTRMap[AssetID].imageWidth * y + x) * 4 + 3] = 0xff;
        }
    }

    //now that everything is red, let's fill in the stuff we know
    //uint16_t color565_1 = rawFile[subGetLoc++];
    //uint16_t color565_2 = rawFile[subGetLoc++];
    //
    //unsigned color1_r = (color565_1 & 0xF800) >> 11;
    //unsigned color1_g = (color565_1 & 0x07E0) >> 5;
    //unsigned color1_b = (color565_1 & 0x001F);
    //
    //unsigned color2_r = (color565_2 & 0xF800) >> 11;
    //unsigned color2_g = (color565_2 & 0x07E0) >> 5;
    //unsigned color2_b = (color565_2 & 0x001F);
    //
    //color1_r = (color1_r * 255) / 31;
    //color1_g = (color1_g * 255) / 63;
    //color1_b = (color1_b * 255) / 31;
    //
    //color2_r = (color2_r * 255) / 31;
    //color2_g = (color2_g * 255) / 63;
    //color2_b = (color2_b * 255) / 31;

    for (int y = 0; y < TXTRMap[AssetID].imageHeight; y += 8)
    {
        for (int x = 0; x < TXTRMap[AssetID].imageWidth; x += 8)
        {
            //decode full dxt1 block, (4 sub blocks)
            DecompressColourGCN(TXTRMap[AssetID].imageWidth, &TXTRMap[AssetID].PCpixels.data()[4 * (y * TXTRMap[AssetID].imageWidth + x)], &rawFile[subGetLoc]);
            subGetLoc += 8;
            DecompressColourGCN(TXTRMap[AssetID].imageWidth, &TXTRMap[AssetID].PCpixels.data()[4 * ((y)*TXTRMap[AssetID].imageWidth + (x + 4))], &rawFile[subGetLoc]);
            subGetLoc += 8;
            DecompressColourGCN(TXTRMap[AssetID].imageWidth, &TXTRMap[AssetID].PCpixels.data()[4 * ((y + 4) * TXTRMap[AssetID].imageWidth + (x))], &rawFile[subGetLoc]);
            subGetLoc += 8;
            DecompressColourGCN(TXTRMap[AssetID].imageWidth, &TXTRMap[AssetID].PCpixels.data()[4 * ((y + 4) * TXTRMap[AssetID].imageWidth + (x + 4))], &rawFile[subGetLoc]);
            subGetLoc += 8;
        }

    }



}
void loadGeometry(FileReader reader, MPGeometry* geometry, MaterialSet materialSet)
{
    /*
    * resize the vector holding the vertex coords based on the size of that section. this will add some extra space because of the 32B padding
    */

    geometry->vertexCoords.resize(reader.getSectionSize() / (sizeof(float) * 3));

    std::cout << "number of vert coords: " << geometry->vertexCoords.size() << std::endl;
    for (int i = 0; i < geometry->vertexCoords.size(); i++)
    {
        reader.readFloat(&geometry->vertexCoords[i].x);
        reader.readFloat(&geometry->vertexCoords[i].y);
        reader.readFloat(&geometry->vertexCoords[i].z);

    }

    //upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount];
    //subGetLoc = upperGetLoc;
    reader.toNextSection();
    bool halfPrecisionNormals = false;//TEMP!
    if (halfPrecisionNormals) 
    {
        geometry->normals.resize(reader.getSectionSize() / (sizeof(short) * 3));
    }
    else
    {
        geometry->normals.resize(reader.getSectionSize() / (sizeof(float) * 3));

    }

    std::cout << "number of normal coords: " << geometry->normals.size() << std::endl;

    if (halfPrecisionNormals) {
        uint16_t temp1, temp2, temp3;
        for (int ijk = 0; ijk < geometry->normals.size(); ijk++)
        {
            reader.readInt16(&temp1);
            reader.readInt16(&temp2);
            reader.readInt16(&temp3);
        }
    }
    else
    {
        for (int ijk = 0; ijk < geometry->normals.size(); ijk++)
        {
            reader.readFloat(&geometry->normals[ijk].x);
            reader.readFloat(&geometry->normals[ijk].y);
            reader.readFloat(&geometry->normals[ijk].z);
        }
    }
    reader.toNextSection();

    std::cout << std::hex << "[" << reader.getloc << " :: " << reader.getloc << "]" << std::dec << "skipping color data" << std::endl;

    //no need to read color data, it's all empty
    reader.toNextSection();

    geometry->floatUVCoords.resize(reader.getSectionSize() / (sizeof(float) * 2));

    std::cout << "number of float UV coords: " << geometry->floatUVCoords.size() << std::endl;

    for (int ijk = 0; ijk < geometry->floatUVCoords.size(); ijk++)
    {
        reader.readFloat(&geometry->floatUVCoords[ijk].x);
        reader.readFloat(&geometry->floatUVCoords[ijk].y);
    }
    reader.toNextSection();



    geometry->shortUVCoords.resize(reader.getSectionSize() / (sizeof(short) * 2));

    std::cout << "number of short UV coords: " << geometry->shortUVCoords.size() << std::endl;

    for (int ijk = 0; ijk < geometry->shortUVCoords.size(); ijk++)
    {
        reader.readInt16((uint16_t*)&geometry->shortUVCoords[ijk].x);
        reader.readInt16((uint16_t*)&geometry->shortUVCoords[ijk].y);
    }

    reader.toNextSection();

    std::cout << std::hex << "[" << reader.getloc << " :: " << reader.getloc << "]" << std::dec << "reading header data" << std::endl;
    //the moment of truth:
    reader.readInt32(&geometry->surfaceCount);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(geometry->surfaceCount)) << " :: " << (reader.getloc) << "] surface count:" << geometry->surfaceCount << std::dec << std::endl;

    geometry->surfaceOffsets.resize(geometry->surfaceCount);

    for (int ijk = 0; ijk < geometry->surfaceCount; ijk++)
    {
        reader.readInt32(&geometry->surfaceOffsets[ijk]);
        std::cout << "[" << (reader.getloc - sizeof(uint32_t)) << " :: " << (reader.getloc) << "] surface offset " << ijk << ": " << std::hex << geometry->surfaceOffsets[ijk] << std::dec << std::endl;
    }
    geometry->surfaceOffsets.push_back(reader.getSectionSize());
    //that's the end of this section, on to the next one
    reader.toNextSection();
    geometry->surfaces.resize(geometry->surfaceCount);
    _CrtDumpMemoryLeaks();
    //loop through each surface
    int surfaceAnchor = reader.getloc;
    for (int surfaceNum = 0; surfaceNum < geometry->surfaceCount; surfaceNum++)
    {
        MPSurface* surface = &geometry->surfaces[surfaceNum];
        surface->clearAll();
        int surfaceStartLoc = reader.getloc;
        for (int i = 0; i < 3; i++)
        {
            reader.readFloat(&surface->centerPoint[i]);
        }
        std::cout << "center point: " << surface->centerPoint[0] << ", " << surface->centerPoint[1] << ", " << surface->centerPoint[2] << std::endl;

        reader.readInt32(&(surface->matIndex));
        std::cout << std::hex << "[" << (reader.getloc - sizeof(surface->matIndex)) << " :: " << (reader.getloc) << "] matIndex:" << surface->matIndex << std::dec << std::endl;

        reader.readInt16(&(surface->mantissa));
        std::cout << std::hex << "[" << (reader.getloc - sizeof(surface->mantissa)) << " :: " << (reader.getloc) << "] mantissa:" << surface->mantissa << std::dec << std::endl;

        reader.readInt16(&(surface->displayListSize));
        std::cout << std::hex << "[" << (reader.getloc - sizeof(surface->displayListSize)) << " :: " << (reader.getloc) << "] displayListSize:" << surface->displayListSize << std::dec << std::endl;

        reader.readInt32(&(surface->parentModelPointer));
        std::cout << std::hex << "[" << (reader.getloc - sizeof(surface->parentModelPointer)) << " :: " << (reader.getloc) << "] parentModelPointer:" << surface->parentModelPointer << std::dec << std::endl;

        reader.readInt32(&(surface->nextSurfacePointer));
        std::cout << std::hex << "[" << (reader.getloc - sizeof(surface->nextSurfacePointer)) << " :: " << (reader.getloc) << "] nextSurfacePointer:" << surface->nextSurfacePointer << std::dec << std::endl;

        reader.readInt32(&(surface->extraDataSize));
        std::cout << std::hex << "[" << (reader.getloc - sizeof(surface->extraDataSize)) << " :: " << (reader.getloc) << "] extraDataSize:" << surface->extraDataSize << std::dec << std::endl;

        //TODO: what was this for?
        //surface->surfaces.resize(CMDLMap[AssetID].geometry.surfaceCount);

        for (int ijk = 0; ijk < 3; ijk++)
        {
            reader.readFloat(&surface->surfaceNormal[ijk]);
        }
        std::cout << "surface normal: " << surface->surfaceNormal[0] << ", " << surface->surfaceNormal[1] << ", " << surface->surfaceNormal[2] << std::endl;



        reader.getloc += surface->extraDataSize;

        //align get location to 32 bytes before reading primatives
        reader.seekBoundary32();



        //char a = -58;
        //std::cout << "a = " << std::bitset<8>(GXFlags) << std::endl;
        //the second one will have 73
        //todo: read until the gx flag hits zero or it hits the end of the section
        reader.readInt8(&surface->GXFlags);
        //std::cout << std::hex << "[" << reader.getloc << " :: " << (reader.getloc + sizeof(GXFlags)) << "] GXFlags:" << GXFlags << std::dec << std::endl;

        while (surface->GXFlags > 0)
        {
            std::bitset<8> GXFlagBits(surface->GXFlags);
            std::cout << std::endl;
            std::cout << GXFlagBits << std::endl;
            std::cout << "GX_VA_NRM type / size | GX_VA_TEX0 type / size" << std::endl;
            switch (0x7 & surface->GXFlags) {
            case 0:
                std::cout << " GX_NRM_XYZ / GX_F32  |   GX_TEX_ST / GX_F32" << std::endl;
                break;
            case 1:
                std::cout << " GX_NRM_XYZ / GX_S16  |   GX_TEX_ST / GX_F32" << std::endl;
                break;
            case 2:
                std::cout << " GX_NRM_XYZ / GX_S16  |   GX_TEX_ST / GX_S16" << std::endl;
                break;
            default:
                std::cout << "fatal error" << std::endl;
            }
            std::cout << "format: ";
            switch (surface->GXFlags & 0xF8)
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
            reader.readInt16(&surface->vertexCount);
            std::cout << std::hex << "[" << (reader.getloc - sizeof(surface->vertexCount)) << " :: " << (reader.getloc) << "] vertex count:" << std::dec << surface->vertexCount << std::dec << std::endl;

            //surface->pos_indices.resize(surface->pos_indices.size() + surface->vertexCount);
            //surface->nml_indices.resize(surface->nml_indices.size() + surface->vertexCount);
            //surface->uvc_indices.resize(surface->uvc_indices.size() + surface->vertexCount);

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

            uint16_t uvc3_index1before = 0;
            uint16_t uvc3_index2before = 0;
            uint16_t uvc3_indexwaybefore = 0;

            uint16_t uvc4_index1before = 0;
            uint16_t uvc4_index2before = 0;
            uint16_t uvc4_indexwaybefore = 0;

            uint16_t uvc5_index1before = 0;
            uint16_t uvc5_index2before = 0;
            uint16_t uvc5_indexwaybefore = 0;

            uint16_t uvc6_index1before = 0;
            uint16_t uvc6_index2before = 0;
            uint16_t uvc6_indexwaybefore = 0;

            uint16_t uvc7_index1before = 0;
            uint16_t uvc7_index2before = 0;
            uint16_t uvc7_indexwaybefore = 0;

            for (int ijk = 0; ijk < surface->vertexCount; ijk++)
            {


                uint16_t pos_vIndex = 0;
                uint16_t nml_vIndex = 0;
                uint16_t uvc1_vIndex = 0;
                uint16_t uvc2_vIndex = 0;
                uint16_t uvc3_vIndex = 0;
                uint16_t uvc4_vIndex = 0;
                uint16_t uvc5_vIndex = 0;
                uint16_t uvc6_vIndex = 0;
                uint16_t uvc7_vIndex = 0;



                if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x3) > 0) {
                    reader.readInt16(&pos_vIndex);
                }
                if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0xC) > 0) {
                    reader.readInt16(&nml_vIndex);
                }
                if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x300) > 0) {
                    reader.readInt16(&uvc1_vIndex);
                }
                if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0xC00) > 0)
                {
                    reader.readInt16(&uvc2_vIndex);
                }
                if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x3000) > 0)
                {
                    reader.readInt16(&uvc3_vIndex);
                }
                if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0xC000) > 0)
                {
                    reader.readInt16(&uvc4_vIndex);
                }
                if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x30000) > 0)
                {
                    reader.readInt16(&uvc5_vIndex);
                }
                if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0xC0000) > 0)
                {
                    reader.readInt16(&uvc6_vIndex);
                }
                if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x300000) > 0)
                {
                    reader.readInt16(&uvc7_vIndex);
                }
                if (ijk == 0) {
                    pos_indexwaybefore = pos_vIndex;
                    nml_indexwaybefore = nml_vIndex;
                    uvc1_indexwaybefore = uvc1_vIndex;
                    uvc2_indexwaybefore = uvc2_vIndex;
                    uvc3_indexwaybefore = uvc3_vIndex;
                    uvc4_indexwaybefore = uvc4_vIndex;
                    uvc5_indexwaybefore = uvc5_vIndex;
                    uvc6_indexwaybefore = uvc6_vIndex;
                    uvc7_indexwaybefore = uvc7_vIndex;
                }
                //std::cout << "vertex " << ijk << " position: " <<
                //    CMDLMap[AssetID].geometry.vertexCoords.data()[vIndex * 3 + 0] << ", " <<
                //    CMDLMap[AssetID].geometry.vertexCoords.data()[vIndex * 3 + 1] << ", " <<
                //    CMDLMap[AssetID].geometry.vertexCoords.data()[vIndex * 3 + 2] <<
                //    std::endl;
                if (((surface->GXFlags & 0xF8) == 0xA0)) {
                    if (ijk > 1)
                    {
                        if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x3) > 0)
                        {
                            surface->pos_indices.push_back((pos_indexwaybefore));
                            surface->pos_indices.push_back((pos_index1before));
                            surface->pos_indices.push_back((pos_vIndex));
                        }
                        if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0xC) > 0)
                        {
                            surface->nml_indices.push_back((nml_indexwaybefore));
                            surface->nml_indices.push_back((nml_index1before));
                            surface->nml_indices.push_back((nml_vIndex));
                        }
                        if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x300) > 0)
                        {
                            surface->uvc_indices.push_back((uvc1_indexwaybefore));
                            surface->uvc_indices.push_back((uvc1_index1before));
                            surface->uvc_indices.push_back((uvc1_vIndex));
                        }
                    }
                }
                else if (((surface->GXFlags & 0xF8) == 0x90))
                {
                    if (ijk > 1 && (ijk + 1) % 3 == 0) {
                        if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x3) > 0)
                        {
                            surface->pos_indices.push_back((pos_index1before));
                            surface->pos_indices.push_back((pos_index2before));
                            surface->pos_indices.push_back((pos_vIndex));
                        }
                        if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0xC) > 0)
                        {
                            surface->nml_indices.push_back((nml_index1before));
                            surface->nml_indices.push_back((nml_index2before));
                            surface->nml_indices.push_back((nml_vIndex));
                        }
                        if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x300) > 0)
                        {
                            surface->uvc_indices.push_back((uvc1_index1before));
                            surface->uvc_indices.push_back((uvc1_index2before));
                            surface->uvc_indices.push_back((uvc1_vIndex));
                        }
                    }
                }
                else if (((surface->GXFlags & 0xF8) == 0x98))
                {
                    if (ijk > 1) {
                        if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x3) > 0)
                        {
                            surface->pos_indices.push_back((pos_index2before));
                            surface->pos_indices.push_back((pos_index1before));
                            surface->pos_indices.push_back((pos_vIndex));
                        }
                        if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0xC) > 0)
                        {
                            surface->nml_indices.push_back((nml_index2before));
                            surface->nml_indices.push_back((nml_index1before));
                            surface->nml_indices.push_back((nml_vIndex));
                        }
                        if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0x300) > 0)
                        {
                            surface->uvc_indices.push_back((uvc1_index2before));
                            surface->uvc_indices.push_back((uvc1_index1before));
                            surface->uvc_indices.push_back((uvc1_vIndex));
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
                uvc2_index2before = uvc2_index1before;
                uvc2_index1before = uvc2_vIndex;
                uvc3_index2before = uvc3_index1before;
                uvc3_index1before = uvc3_vIndex;
                uvc4_index2before = uvc4_index1before;
                uvc4_index1before = uvc4_vIndex;
                uvc5_index2before = uvc5_index1before;
                uvc5_index1before = uvc5_vIndex;
                uvc6_index2before = uvc6_index1before;
                uvc6_index1before = uvc6_vIndex;
                uvc7_index2before = uvc7_index1before;
                uvc7_index1before = uvc7_vIndex;


                //if ((materialSet.materials[surface->matIndex].vertexAtributeFlags & 0xC) > 0)
                //{
                //    uint16_t vIndex;variable 'pos_vIndex' is being used
                //    memcpy(&vIndex, &rawFile[subGetLoc], sizeof(vIndex));
                //    vIndex = _byteswap_ushort(vIndex);
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
                //if ((CMDLMap[AssetID].materialSets.data()[0/*surface->matIndex*/].vertexAtributeFlags & 0x300) > 0)
                //{
                //    uint16_t vIndex;
                //    memcpy(&vIndex, &rawFile[subGetLoc], sizeof(vIndex));
                //    vIndex = _byteswap_ushort(vIndex);
                //    std::cout << "vertex " << ijk << " UV: " <<
                //        CMDLMap[AssetID].geometry.floatUVCoords.data()[vIndex * 2 + 0] << ", " <<
                //        CMDLMap[AssetID].geometry.floatUVCoords.data()[vIndex * 2 + 1] <<
                //        std::endl;
                //    subGetLoc += sizeof(vIndex);
                //}
                //if ((CMDLMap[AssetID].materialSets.data()[0/*surface->matIndex*/].vertexAtributeFlags & 0xC00) > 0)
                //{
                //    uint16_t vIndex;
                //    memcpy(&vIndex, &rawFile[subGetLoc], sizeof(vIndex));
                //    vIndex = _byteswap_ushort(vIndex);
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
            //std::cout << (CMDLMap[AssetID].geometry.surfaceOffsets[surfaceNum]) - (subGetLoc - upperGetLoc) << std::endl;
            //break;
            //if the amount of data left to read for this surface is less than one byte, go to the next surface
            /*
            * find: the amount left to the current surface
            * 
            * data I have:
            * current location
            * location where the surfaces started
            * location where the current surface started
            * location where each surface starts
            */
            //TODO: calculate display list size without the file's built in one
            if (reader.getloc - surfaceStartLoc + 5 > reader.getSectionSize()) {
            //if (reader.getloc - surfaceStartLoc + 5 > geometry->surfaceOffsets[surfaceNum+1] - geometry->surfaceOffsets[surfaceNum]) {

                std::cout << __LINE__ << " hit end of display list" << std::endl;
                //TODO: still needs to jump to the start of the next section!

                //reader.getloc = surfaceAnchor + geometry->surfaceOffsets[surfaceNum];
                reader.toNextSection();
                //return;
                break;

            }

            reader.readInt8(&surface->GXFlags);

            if (surface->GXFlags == 0)
            {
                std::cout << __LINE__ << " GXFlags hit 0" << std::endl;
                //reader.getloc = surfaceAnchor + geometry->surfaceOffsets[surfaceNum];
                reader.toNextSection();
                break;
            }
        }
    }
    
}
void loadMREA(std::vector<char> rawFile, PrimeAssetID AssetID)
{
    FileReader reader;
    reader.init((uint8_t*)&(rawFile[0]));
    MREAMap[AssetID].magic = 0xBAD0DADA;

    reader.readInt32(&MREAMap[AssetID].magic);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].magic)) << " :: " << (reader.getloc) << "] magic:" << MREAMap[AssetID].magic << std::dec << std::endl;

    reader.readInt32(&MREAMap[AssetID].version);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].version)) << " :: " << (reader.getloc) << "] version:" << MREAMap[AssetID].version << std::dec << std::endl;

    
    for (int i = 0; i < 12; i++) {
        reader.readFloat(&MREAMap[AssetID].areaTransform[i]);
    }
    std::cout << "| " << MREAMap[AssetID].areaTransform[0] << "\t" << MREAMap[AssetID].areaTransform[1] << "\t" << MREAMap[AssetID].areaTransform[2] << "\t" << MREAMap[AssetID].areaTransform[3] << "\t|"<< std::endl;
    std::cout << "| " << MREAMap[AssetID].areaTransform[4] << "\t" << MREAMap[AssetID].areaTransform[5] << "\t" << MREAMap[AssetID].areaTransform[6] << "\t" << MREAMap[AssetID].areaTransform[7] << "\t|"<< std::endl;
    std::cout << "| " << MREAMap[AssetID].areaTransform[8] << "\t" << MREAMap[AssetID].areaTransform[9] << "\t" << MREAMap[AssetID].areaTransform[10] << "\t" << MREAMap[AssetID].areaTransform[11] << "\t|"<< std::endl;


    reader.readInt32(&MREAMap[AssetID].worldModelCount);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].worldModelCount)) << " :: " << (reader.getloc) << "] worldModelCount:" << std::dec << MREAMap[AssetID].worldModelCount << std::dec << std::endl;

    reader.readInt32(&MREAMap[AssetID].dataSectionCount);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].dataSectionCount)) << " :: " << (reader.getloc) << "] dataSectionCount:" << std::dec << MREAMap[AssetID].dataSectionCount << std::dec << std::endl;

    reader.readInt32(&MREAMap[AssetID].worldGeometrySection);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].worldGeometrySection)) << " :: " << (reader.getloc) << "] worldGeometrySection:" << std::dec << MREAMap[AssetID].worldGeometrySection << std::dec << std::endl;

    reader.readInt32(&MREAMap[AssetID].scriptLayersSection);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].scriptLayersSection)) << " :: " << (reader.getloc) << "] scriptLayersSection:" << std::dec << MREAMap[AssetID].scriptLayersSection << std::dec << std::endl;

    reader.readInt32(&MREAMap[AssetID].collisionSection);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].collisionSection)) << " :: " << (reader.getloc) << "] collisionSection:" << std::dec << MREAMap[AssetID].collisionSection << std::dec << std::endl;

    reader.readInt32(&MREAMap[AssetID].unknownSection);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].unknownSection)) << " :: " << (reader.getloc) << "] unknownSection:" << std::dec << MREAMap[AssetID].unknownSection << std::dec << std::endl;

    reader.readInt32(&MREAMap[AssetID].lightsSection);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].lightsSection)) << " :: " << (reader.getloc) << "] lightsSection:" << std::dec << MREAMap[AssetID].lightsSection << std::dec << std::endl;

    reader.readInt32(&MREAMap[AssetID].visibilityTreeSection);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].visibilityTreeSection)) << " :: " << (reader.getloc) << "] visibilityTreeSection:" << std::dec << MREAMap[AssetID].visibilityTreeSection << std::dec << std::endl;

    reader.readInt32(&MREAMap[AssetID].pathSection);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].pathSection)) << " :: " << (reader.getloc) << "] pathSection:" << std::dec << MREAMap[AssetID].pathSection << std::dec << std::endl;

    reader.readInt32(&MREAMap[AssetID].areaOctreeSection);
    std::cout << std::hex << "[" << (reader.getloc - sizeof(MREAMap[AssetID].areaOctreeSection)) << " :: " << (reader.getloc) << "] areaOctreeSection:" << std::dec << MREAMap[AssetID].areaOctreeSection << std::dec << std::endl;

    MREAMap[AssetID].dataSectionSizes.resize(MREAMap[AssetID].dataSectionCount);
    for (int i = 0; i < MREAMap[AssetID].dataSectionCount; i++)
    {
        reader.readInt32(&MREAMap[AssetID].dataSectionSizes[i]);
    }
    
}
void loadMLVL(std::vector<char> rawFile, PrimeAssetID AssetID)
{
    MLVLMap[AssetID].magic = 0xBAD0DADA;
    uint64_t subGetLoc = 0;
    memcpy(&MLVLMap[AssetID].magic, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].magic));
    MLVLMap[AssetID].magic = _byteswap_ulong(MLVLMap[AssetID].magic);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].magic)) << "] magic:" << MLVLMap[AssetID].magic << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].magic);

    memcpy(&MLVLMap[AssetID].version, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].version));
    MLVLMap[AssetID].version = _byteswap_ulong(MLVLMap[AssetID].version);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].version)) << "] version:" << MLVLMap[AssetID].version << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].version);

    memcpy(&MLVLMap[AssetID].worldNameID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].worldNameID));
    MLVLMap[AssetID].worldNameID = _byteswap_ulong(MLVLMap[AssetID].worldNameID);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].worldNameID)) << "] worldNameID:" << MLVLMap[AssetID].worldNameID << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].worldNameID);

    memcpy(&MLVLMap[AssetID].worldSaveInfoID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].worldSaveInfoID));
    MLVLMap[AssetID].worldSaveInfoID = _byteswap_ulong(MLVLMap[AssetID].worldSaveInfoID);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].worldSaveInfoID)) << "] worldSaveInfoID:" << MLVLMap[AssetID].worldSaveInfoID << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].worldSaveInfoID);

    memcpy(&MLVLMap[AssetID].defaultSkyboxID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].defaultSkyboxID));
    MLVLMap[AssetID].defaultSkyboxID = _byteswap_ulong(MLVLMap[AssetID].defaultSkyboxID);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].defaultSkyboxID)) << "] defaultSkyboxID:" << MLVLMap[AssetID].defaultSkyboxID << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].defaultSkyboxID);

    memcpy(&MLVLMap[AssetID].memoryRelayCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].memoryRelayCount));
    MLVLMap[AssetID].memoryRelayCount = _byteswap_ulong(MLVLMap[AssetID].memoryRelayCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].memoryRelayCount)) << std::dec << "] memoryRelayCount:" << MLVLMap[AssetID].memoryRelayCount << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].memoryRelayCount);
    MLVLMap[AssetID].memoryRelayArray.resize(MLVLMap[AssetID].memoryRelayCount);
    for (int i = 0; i < MLVLMap[AssetID].memoryRelayCount; i++)
    {
        MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID = 99;//initialize key

        memcpy(&MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID));
        MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID = _byteswap_ulong(MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID)) << "] instace id:" << MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].memoryRelayArray[i].memoryRelayInstanceID);

        memcpy(&MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID));
        MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID = _byteswap_ulong(MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID)) << "] targetInstanceID:" << MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].memoryRelayArray[i].targetInstanceID);

        memcpy(&MLVLMap[AssetID].memoryRelayArray[i].message, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].memoryRelayArray[i].message));
        MLVLMap[AssetID].memoryRelayArray[i].message = _byteswap_ushort(MLVLMap[AssetID].memoryRelayArray[i].message);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].memoryRelayArray[i].message)) << std::dec << "] message:" << MLVLMap[AssetID].memoryRelayArray[i].message << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].memoryRelayArray[i].message);

        memcpy(&MLVLMap[AssetID].memoryRelayArray[i].active, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].memoryRelayArray[i].active));
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].memoryRelayArray[i].active)) << std::dec << "] active:" << MLVLMap[AssetID].memoryRelayArray[i].active << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].memoryRelayArray[i].active);
    }

    memcpy(&MLVLMap[AssetID].areaCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaCount));
    MLVLMap[AssetID].areaCount = _byteswap_ulong(MLVLMap[AssetID].areaCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaCount)) << std::dec << "] areaCount:" << MLVLMap[AssetID].areaCount << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].areaCount);

    memcpy(&MLVLMap[AssetID].garbage1, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].garbage1));
    MLVLMap[AssetID].garbage1 = _byteswap_ulong(MLVLMap[AssetID].garbage1);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].garbage1)) << std::dec << "] garbage1 (always 1):" << MLVLMap[AssetID].garbage1 << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].garbage1);

    MLVLMap[AssetID].areaArray.resize(MLVLMap[AssetID].areaCount);
    for (int i = 0; i < MLVLMap[AssetID].areaCount; i++)
    {
        memcpy(&MLVLMap[AssetID].areaArray[i].areaNameID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].areaNameID));
        MLVLMap[AssetID].areaArray[i].areaNameID = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].areaNameID);
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
        MLVLMap[AssetID].areaArray[i].areaMREA_ID = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].areaMREA_ID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].areaMREA_ID)) << "] area MREA ID:" << MLVLMap[AssetID].areaArray[i].areaMREA_ID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].areaMREA_ID);

        memcpy(&MLVLMap[AssetID].areaArray[i].internalAreaID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].internalAreaID));
        MLVLMap[AssetID].areaArray[i].internalAreaID = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].internalAreaID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].internalAreaID)) << "] internalAreaID:" << MLVLMap[AssetID].areaArray[i].internalAreaID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].internalAreaID);

        memcpy(&MLVLMap[AssetID].areaArray[i].attachedAreaCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaCount));
        MLVLMap[AssetID].areaArray[i].attachedAreaCount = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].attachedAreaCount);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaCount)) << "] attachedAreaCount:" << std::dec << MLVLMap[AssetID].areaArray[i].attachedAreaCount << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaCount);


        MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray.resize(MLVLMap[AssetID].areaArray[i].attachedAreaCount);
        for (int j = 0; j < MLVLMap[AssetID].areaArray[i].attachedAreaCount; j++)
        {
            memcpy(&MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j], &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j]));
            MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j] = _byteswap_ushort(MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j]);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j])) << "] attachedAreaIndex:" << std::dec << MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j] << std::endl;
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].attachedAreaIndexArray[j]);
        }

        memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.garbage, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dependencies.garbage));
        MLVLMap[AssetID].areaArray[i].dependencies.garbage = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dependencies.garbage);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.garbage)) << "] garbage (always 0):" << std::dec << MLVLMap[AssetID].areaArray[i].dependencies.garbage << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dependencies.garbage);

        memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount));
        MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount)) << "] dependencyCount:" << std::dec << MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount);

        MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray.resize(MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount);
        for (int j = 0; j < MLVLMap[AssetID].areaArray[i].dependencies.dependencyCount; j++)
        {
            memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID));
            MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID);
            //std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID)) << "] dependency ID:" << MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID << std::dec << std::endl;
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyAssetID);

            memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyType, &rawFile[subGetLoc], 4);
            //std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyType)) << "] dependency type:"; std::cout.write(MLVLMap[AssetID].areaArray[i].dependencies.dependecyArray[j].dependencyType, 4) << std::endl;
            subGetLoc += 4;
        }

        memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount));
        MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount)) << "] dependecyOffsetCount:" << std::dec << MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount);

        MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray.resize(MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount);
        for (int j = 0; j < MLVLMap[AssetID].areaArray[i].dependencies.dependecyOffsetCount; j++)
        {
            memcpy(&MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j], &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j]));
            MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j] = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j]);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j])) << "] dependecy offset:" << std::dec << MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j] << std::endl;
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dependencies.dependencyOffsetArray[j]);
        }

        memcpy(&MLVLMap[AssetID].areaArray[i].dockCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockCount));
        MLVLMap[AssetID].areaArray[i].dockCount = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dockCount);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dockCount)) << "] dockCount:" << std::dec << MLVLMap[AssetID].areaArray[i].dockCount << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockCount);

        MLVLMap[AssetID].areaArray[i].dockArray.resize(MLVLMap[AssetID].areaArray[i].dockCount);
        for (int j = 0; j < MLVLMap[AssetID].areaArray[i].dockCount; j++)
        {
            memcpy(&MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount));
            MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount)) << "] dockCount:" << std::dec << MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount << std::endl;
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount);

            MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray.resize(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount);
            for (int k = 0; k < MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockCount; k++)
            {
                memcpy(&MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex));
                MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex);
                std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex)) << "] connecting Dock Area Index:" << std::dec << MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex << std::endl;
                subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].areaIndex);

                memcpy(&MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex));
                MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex);
                std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex)) << "] connecting Dock Index:" << std::dec << MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex << std::endl;
                subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].connectingDockArray[k].dockIndex);
            }

            memcpy(&MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount));
            MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount)) << "] dockCoordinateCount:" << std::dec << MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount << std::endl;
            subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount);


            MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates.resize(MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount);

            for (int k = 0; k < MLVLMap[AssetID].areaArray[i].dockArray[j].dockCoordinateCount; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    memcpy(&MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][l], &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][l]));
                    MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][l] = _byteswap_ulong(MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][l]);
                    subGetLoc += sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][l]);
                }
                std::cout << std::hex << "[" << (subGetLoc - sizeof(MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][0]) * 3) << " :: " << (subGetLoc) << "] dockCoordinates:" << std::dec << MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][0] << ", " << MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][0] << ", " << MLVLMap[AssetID].areaArray[i].dockArray[j].dockDoordinates[k][0] << std::endl;

            }
        }


    }

    memcpy(&MLVLMap[AssetID].worldMapID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].worldMapID));
    MLVLMap[AssetID].worldMapID = _byteswap_ulong(MLVLMap[AssetID].worldMapID);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].worldMapID)) << "] worldMapID:" << MLVLMap[AssetID].worldMapID << std::dec << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].worldMapID);

    memcpy(&MLVLMap[AssetID].garbage2, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].garbage2));
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].garbage2)) << "] garbage2 (always 0):" << std::dec << MLVLMap[AssetID].garbage2 << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].garbage2);

    memcpy(&MLVLMap[AssetID].scriptInstanceCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].scriptInstanceCount));
    MLVLMap[AssetID].scriptInstanceCount = _byteswap_ulong(MLVLMap[AssetID].scriptInstanceCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].scriptInstanceCount)) << "] scriptInstanceCount:" << std::dec << MLVLMap[AssetID].scriptInstanceCount << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].scriptInstanceCount);

    memcpy(&MLVLMap[AssetID].audioGroupCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].audioGroupCount));
    MLVLMap[AssetID].audioGroupCount = _byteswap_ulong(MLVLMap[AssetID].audioGroupCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].audioGroupCount)) << "] audioGroupCount:" << std::dec << MLVLMap[AssetID].audioGroupCount << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].audioGroupCount);

    MLVLMap[AssetID].audioGroupArray.resize(MLVLMap[AssetID].audioGroupCount);

    for (int i = 0; i < MLVLMap[AssetID].audioGroupCount; i++)
    {
        memcpy(&MLVLMap[AssetID].audioGroupArray[i].groupID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].audioGroupArray[i].groupID));
        MLVLMap[AssetID].audioGroupArray[i].groupID = _byteswap_ulong(MLVLMap[AssetID].audioGroupArray[i].groupID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].audioGroupArray[i].groupID)) << "] audio group ID:" << MLVLMap[AssetID].audioGroupArray[i].groupID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].audioGroupArray[i].groupID);

        memcpy(&MLVLMap[AssetID].audioGroupArray[i].AGSC_ID, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].audioGroupArray[i].AGSC_ID));
        MLVLMap[AssetID].audioGroupArray[i].AGSC_ID = _byteswap_ulong(MLVLMap[AssetID].audioGroupArray[i].AGSC_ID);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].audioGroupArray[i].AGSC_ID)) << "] AGSC_ID:" << MLVLMap[AssetID].audioGroupArray[i].AGSC_ID << std::dec << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].audioGroupArray[i].AGSC_ID);
    }

    memcpy(&MLVLMap[AssetID].garbage3, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].garbage3));
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].garbage3)) << "] garbage3 (always 0):" << std::dec << MLVLMap[AssetID].garbage3 << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].garbage3);

    memcpy(&MLVLMap[AssetID].garbage4, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].garbage4));
    MLVLMap[AssetID].garbage4 = _byteswap_ulong(MLVLMap[AssetID].garbage4);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].garbage4)) << "] garbage4 (equal to area count):" << std::dec << MLVLMap[AssetID].garbage4 << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].garbage4);

    MLVLMap[AssetID].areaLayerFlags.resize(MLVLMap[AssetID].areaCount);
    for (int i = 0; i < MLVLMap[AssetID].areaCount; i++)
    {
        memcpy(&MLVLMap[AssetID].areaLayerFlags[i].layerCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaLayerFlags[i].layerCount));
        MLVLMap[AssetID].areaLayerFlags[i].layerCount = _byteswap_ulong(MLVLMap[AssetID].areaLayerFlags[i].layerCount);
        subGetLoc += sizeof(MLVLMap[AssetID].areaLayerFlags[i].layerCount);

        memcpy(&MLVLMap[AssetID].areaLayerFlags[i].layerFlags, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaLayerFlags[i].layerFlags));
        MLVLMap[AssetID].areaLayerFlags[i].layerFlags = _byteswap_uint64(MLVLMap[AssetID].areaLayerFlags[i].layerFlags);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaLayerFlags[i].layerFlags)) << "] layer " << MLVLMap[AssetID].areaLayerFlags[i].layerCount << " flags:" << std::dec << MLVLMap[AssetID].areaLayerFlags[i].layerFlags << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaLayerFlags[i].layerFlags);
    }

    memcpy(&MLVLMap[AssetID].layerNameCount, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].layerNameCount));
    MLVLMap[AssetID].layerNameCount = _byteswap_ulong(MLVLMap[AssetID].layerNameCount);
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
        std::cout << std::hex << "[" << tempAnchor << " :: " << subGetLoc << "] layer name " << i << ": " << std::dec << MLVLMap[AssetID].layerNameArray[i] << std::endl;
    }

    memcpy(&MLVLMap[AssetID].garbage5, &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].garbage5));
    MLVLMap[AssetID].garbage5 = _byteswap_ulong(MLVLMap[AssetID].garbage5);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].garbage5)) << "] garbage5 (equal to area count):" << std::dec << MLVLMap[AssetID].garbage5 << std::endl;
    subGetLoc += sizeof(MLVLMap[AssetID].garbage5);


    MLVLMap[AssetID].areaLayerNameOffsetArray.resize(MLVLMap[AssetID].areaCount);
    for (int i = 0; i < MLVLMap[AssetID].areaCount; i++)
    {
        memcpy(&MLVLMap[AssetID].areaLayerNameOffsetArray[i], &rawFile[subGetLoc], sizeof(MLVLMap[AssetID].areaLayerNameOffsetArray[i]));
        MLVLMap[AssetID].areaLayerNameOffsetArray[i] = _byteswap_ulong(MLVLMap[AssetID].areaLayerNameOffsetArray[i]);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(MLVLMap[AssetID].areaLayerNameOffsetArray[i])) << "] areaLayerNameOffset:" << std::dec << MLVLMap[AssetID].areaLayerNameOffsetArray[i] << std::endl;
        subGetLoc += sizeof(MLVLMap[AssetID].areaLayerNameOffsetArray[i]);
    }

}
void loadSTRG(std::vector<char> rawFile, PrimeAssetID AssetID)
{
    uint32_t subGetLoc = 0;
    //int32_t magic;
    STRGMap[AssetID].magic = 0xBAD0DADA;

    memcpy(&STRGMap[AssetID].magic, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].magic));
    STRGMap[AssetID].magic = _byteswap_ulong(STRGMap[AssetID].magic);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].magic)) << "] magic:" << STRGMap[AssetID].magic << std::dec << std::endl;
    subGetLoc += sizeof(STRGMap[AssetID].magic);

    memcpy(&STRGMap[AssetID].version, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].version));
    STRGMap[AssetID].version = _byteswap_ulong(STRGMap[AssetID].version);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].version)) << "] version:" << STRGMap[AssetID].version << std::dec << std::endl;
    subGetLoc += sizeof(STRGMap[AssetID].version);

    memcpy(&STRGMap[AssetID].langCount, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].langCount));
    STRGMap[AssetID].langCount = _byteswap_ulong(STRGMap[AssetID].langCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].langCount)) << "] langCount:" << STRGMap[AssetID].langCount << std::dec << std::endl;
    subGetLoc += sizeof(STRGMap[AssetID].langCount);

    memcpy(&STRGMap[AssetID].stringCount, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].stringCount));
    STRGMap[AssetID].stringCount = _byteswap_ulong(STRGMap[AssetID].stringCount);
    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].stringCount)) << "] stringCount:" << STRGMap[AssetID].stringCount << std::dec << std::endl;
    subGetLoc += sizeof(STRGMap[AssetID].stringCount);


    STRGMap[AssetID].langTable.resize(STRGMap[AssetID].langCount);

    for (int i = 0; i < STRGMap[AssetID].langCount; i++) {
        memcpy(&STRGMap[AssetID].langTable[i].langCode, &rawFile[subGetLoc], 4);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].langTable[i].langCode)) << "] Language Code:" << std::dec; std::cout.write(STRGMap[AssetID].langTable[i].langCode, 4) << std::endl;
        subGetLoc += 4;

        memcpy(&STRGMap[AssetID].langTable[i].langStringOffset, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].langTable[i].langStringOffset));
        STRGMap[AssetID].langTable[i].langStringOffset = _byteswap_ulong(STRGMap[AssetID].langTable[i].langStringOffset);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].langTable[i].langStringOffset)) << "] posOffset:" << STRGMap[AssetID].langTable[i].langStringOffset << std::dec << std::endl;
        subGetLoc += sizeof(STRGMap[AssetID].langTable[i].langStringOffset);
    }
    STRGMap[AssetID].stringTables.resize(STRGMap[AssetID].langCount);
    for (int i = 0; i < STRGMap[AssetID].langCount; i++)
    {
        STRGMap[AssetID].stringTables[i].STRGTableSize = 0;
        //uint32_t stringTableSize;

        memcpy(&STRGMap[AssetID].stringTables[i].STRGTableSize, &rawFile[subGetLoc], sizeof(STRGMap[AssetID].stringTables[i].STRGTableSize));
        STRGMap[AssetID].stringTables[i].STRGTableSize = _byteswap_ulong(STRGMap[AssetID].stringTables[i].STRGTableSize);
        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].stringTables[i].STRGTableSize)) << "] STRGTableSize:" << std::dec << STRGMap[AssetID].stringTables[i].STRGTableSize << std::endl;
        subGetLoc += sizeof(STRGMap[AssetID].stringTables[i].STRGTableSize);

        uint32_t disjointOffset = subGetLoc;

        STRGMap[AssetID].stringTables[i].stringOffsets.resize(STRGMap[AssetID].langCount * STRGMap[AssetID].stringCount);
        for (int j = 0; j < STRGMap[AssetID].stringCount; j++)
        {

            memcpy(&STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j], &rawFile[subGetLoc], sizeof(STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j]));
            STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j] = _byteswap_ulong(STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j]);
            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(STRGMap[AssetID].stringTables[i].stringOffsets[j])) << "] stringOffsets:" << std::dec << STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j] << std::endl;
            subGetLoc += sizeof(STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j]);
        }

        STRGMap[AssetID].stringTables[i].stringArray.resize(STRGMap[AssetID].langCount * STRGMap[AssetID].stringCount);
        for (int j = 0; j < STRGMap[AssetID].stringCount; j++)
        {
            subGetLoc = STRGMap[AssetID].stringTables[i].stringOffsets[i * STRGMap[AssetID].stringCount + j] + disjointOffset + 1;


            char temp;
            std::string tempstr = "";

            temp = rawFile[subGetLoc];
            subGetLoc += 2;
            while (temp != '\0')
            {
                tempstr += temp;
                temp = rawFile[subGetLoc];
                subGetLoc += 2;
            }

            STRGMap[AssetID].stringTables[i].stringArray[i * STRGMap[AssetID].stringCount + j] = tempstr;
            std::cout << "string: " << STRGMap[AssetID].stringTables[i].stringArray[i * STRGMap[AssetID].stringCount + j] << std::endl;
        }
    }

}
void loadCMDL(std::vector<char> rawFile, PrimeAssetID AssetID)
{
    CMDLMap[AssetID].magic = 0xBAD0DADA;
    CMDLMap[AssetID].geometry.shortUVCoords.reserve(9999);
    CMDLMap[AssetID].geometry.vertexCoords.reserve(9999);
    CMDLMap[AssetID].geometry.surfaces.reserve(9999);


    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    FileReader reader;
    reader.init((uint8_t*)rawFile.data());

    reader.readInt32(&CMDLMap[AssetID].magic);
    std::cout << std::hex << "[" << reader.getloc << " :: " << (reader.getloc + sizeof(CMDLMap[AssetID].magic)) << "] magic:" << CMDLMap[AssetID].magic << std::dec << std::endl;

    reader.readInt32(&CMDLMap[AssetID].version); 
    std::cout << std::hex << "[" << reader.getloc << " :: " << (reader.getloc + sizeof(CMDLMap[AssetID].version)) << "] version:" << CMDLMap[AssetID].version << std::dec << std::endl;
    
    reader.readInt32(&CMDLMap[AssetID].flags);
    std::cout << std::hex << "[" << reader.getloc << " :: " << (reader.getloc + sizeof(CMDLMap[AssetID].flags)) << "] flags:" << std::endl;
    std::cout << "\tIndicates the model is skinned: " << ((CMDLMap[AssetID].flags & 0x1) > 0 ? "1" : "0") << std::endl;
    std::cout << "\tToggle short normals:           " << ((CMDLMap[AssetID].flags & 0x2) > 0 ? "1" : "0") << std::endl;
    std::cout << "\tEnable short UV array:          " << ((CMDLMap[AssetID].flags & 0x4) > 0 ? "1" : "0") << std::endl;
    bool halfPrecisionNormals = ((CMDLMap[AssetID].flags & 0x2) > 0);
    bool halfPrecisionUVs = ((CMDLMap[AssetID].flags & 0x4) > 0);

    std::cout << std::hex << "[" << reader.getloc << " :: " << (reader.getloc + sizeof(float) * 6) << "] Model Axis-Aligned Bounding Box:";
    for (int ijk = 0; ijk < 6; ijk++)
    {
        reader.readFloat(&(CMDLMap[AssetID].ModelAxisAlignedBoundingBox[ijk]));
        std::cout << CMDLMap[AssetID].ModelAxisAlignedBoundingBox[ijk];
    }
    std::cout << std::dec << std::endl;

    reader.readInt32(&CMDLMap[AssetID].dataSectionCount);
    std::cout << std::hex << "[" << reader.getloc << " :: " << (reader.getloc + sizeof(CMDLMap[AssetID].dataSectionCount)) << "] data Section Count:" << CMDLMap[AssetID].dataSectionCount << std::dec << std::endl;

    reader.readInt32(&CMDLMap[AssetID].MaterialSetCount);
    std::cout << std::hex << "[" << reader.getloc << " :: " << (reader.getloc + sizeof(CMDLMap[AssetID].MaterialSetCount)) << "] Material Set Count:" << CMDLMap[AssetID].MaterialSetCount << std::dec << std::endl;

    CMDLMap[AssetID].materialSets.resize(CMDLMap[AssetID].MaterialSetCount);

    CMDLMap[AssetID].dataSectionSizes.resize(CMDLMap[AssetID].dataSectionCount);

    for (int ijk = 0; ijk < CMDLMap[AssetID].dataSectionCount; ijk++)
    {
        reader.readInt32(&CMDLMap[AssetID].dataSectionSizes[ijk]);
        reader.addSectionSize(CMDLMap[AssetID].dataSectionSizes[ijk]);

        std::cout << std::hex << "[" << reader.getloc - sizeof(uint32_t) << " :: " << reader.getloc << "]" << "data section " << std::dec << ijk << " size: " << CMDLMap[AssetID].dataSectionSizes[ijk] << std::endl;

    }
    reader.seekBoundary32();

    //uint32_t upperGetLoc = reader.getloc;
    reader.sectionAncor = reader.getloc;
    std::cout << "reading material data from " << std::hex << reader.getloc << std::dec << std::endl;


    for (int imat = 0; imat < CMDLMap[AssetID].MaterialSetCount; imat++)
    {
        reader.readInt32(&CMDLMap[AssetID].materialSets[imat].textureCount);
        std::cout << "textures: " << CMDLMap[AssetID].materialSets[imat].textureCount << std::endl;
        CMDLMap[AssetID].materialSets[imat].textureFileIDs.resize(CMDLMap[AssetID].materialSets[imat].textureCount);
        
        for (int tx = 0; tx < CMDLMap[AssetID].materialSets[imat].textureCount; tx++) {
            reader.readInt32(&CMDLMap[AssetID].materialSets[imat].textureFileIDs[tx]);
            std::cout << "texture used: " << std::hex << CMDLMap[AssetID].materialSets[imat].textureFileIDs[tx] << std::dec << std::endl;
        }


        reader.readInt32(&(CMDLMap[AssetID].materialSets[imat].materialCount));
        std::cout << CMDLMap[AssetID].materialSets[imat].materialCount << std::endl;
        
        CMDLMap[AssetID].materialSets[imat].materialEndOffsets.resize(CMDLMap[AssetID].materialSets[imat].materialCount);
        for (int mc = 0; mc < CMDLMap[AssetID].materialSets[imat].materialCount; mc++) {
            reader.readInt32(&CMDLMap[AssetID].materialSets[imat].materialEndOffsets[mc]);
            std::cout << "material end offset: " << std::hex << CMDLMap[AssetID].materialSets[imat].materialEndOffsets[mc] << std::dec << std::endl;
        }

        uint32_t materialStartingMarker = reader.getloc;

        CMDLMap[AssetID].materialSets[imat].materials.resize(CMDLMap[AssetID].materialSets[imat].materialCount + 5);
        for (int ijk = 0; ijk < CMDLMap[AssetID].materialSets[imat].materialCount; ijk++)
        {
            uint32_t flags;
            reader.readInt32(&flags);
            std::cout << "offset: " << std::hex << reader.getloc << std::dec << std::endl;
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
            uint32_t TC;
            reader.readInt32(&TC);
            std::cout << "Texture Count: " << TC << std::endl;

            while (TC > 100) {}//safety to prevent crahes
            CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices.resize(TC);
            std::cout << "textures:" << std::endl;
            for (int tx = 0; tx < TC; tx++) {
                reader.readInt32(&CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices[tx]);
                std::cout << "\ttexture: " << std::hex << CMDLMap[AssetID].materialSets[imat].textureFileIDs[CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices[tx]] << std::dec << std::endl;
            }


            reader.readInt32(&CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags);
            std::cout << "vertex atributes: " << std::endl;
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
            uint32_t groupIndex;
            reader.readInt32(&groupIndex);
            std::cout << "group index: " << groupIndex << std::endl;
            if ((flags & 0x08) > 0)
            {
                uint32_t KonstCount;
                reader.readInt32(&KonstCount);
                std::cout << "KonstCount: " << KonstCount << std::endl;
                CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors.resize(KonstCount);

                for (int mc = 0; mc < KonstCount; mc++) {
                    reader.readInt32(&CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors[mc]);
                    std::cout << "konst color " << mc << ": " << std::hex << CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors[mc] << std::dec << std::endl;

                }
            }



            uint16_t blendDestFactor;
            reader.readInt16(&blendDestFactor);
            std::cout << "blendDestFactor: " << blendDestFactor << std::endl;

            uint16_t blendSourceFactor;
            reader.readInt16(&blendSourceFactor);
            std::cout << "blendSourceFactor: " << blendSourceFactor << std::endl;

            if ((flags & 0x400) != 0)
            {
                uint32_t reflectionIndirectTextureIndex;
                reader.readInt32(&reflectionIndirectTextureIndex);
                std::cout << "reflection Indirect Texture Index: " << reflectionIndirectTextureIndex << std::endl;
            }


            reader.readInt32(&CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount);
            std::cout << "color channel count: " << CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount << std::endl;

            reader.readInt32(&CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags);
            std::cout << "color channel flags: " << CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags << std::dec << std::endl;



            uint32_t TEVStageCount;
            reader.readInt32(&TEVStageCount);
            std::cout << "TEV Stage Count: " << TEVStageCount << std::endl;

            for (int ijkl = 0; ijkl < TEVStageCount; ijkl++)
            {
                std::cout << std::hex << "[" << reader.getloc << "] TEV stage " << std::dec << ijkl << ": " << std::endl;
                uint32_t colorInputFlags;
                reader.readInt32(&colorInputFlags);
                std::cout << "\tColor input flags (color0): ";
                        if ((colorInputFlags & 0x1f) == 0x0) std::cout << "Previous stage RGB"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0x1) std::cout << "Previous stage AAA"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0x2) std::cout << "Color 0 RGB"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0x3) std::cout << "Color 0 AAA"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0x4) std::cout << "Color 1 RGB"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0x5) std::cout << "Color 1 AAA"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0x6) std::cout << "Color 2 RGB"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0x7) std::cout << "Color 2 AAA"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0x8) std::cout << "Texture RGB"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0x9) std::cout << "Texture AAA"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0xa) std::cout << "Rasterized RGB"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0xb) std::cout << "Rasterized AAA"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0xc) std::cout << "One"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0xd) std::cout << "Half"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0xe) std::cout << "Konstant RGB"<<std::endl;
                else if ((colorInputFlags & 0x1f) == 0xf) std::cout << "Zero"<<std::endl;

                std::cout << "\tColor input flags (color1): ";
                        if (((colorInputFlags & 0x3E0) >> 5) == 0x0) std::cout << "Previous stage RGB" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0x1) std::cout << "Previous stage AAA" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0x2) std::cout << "Color 0 RGB" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0x3) std::cout << "Color 0 AAA" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0x4) std::cout << "Color 1 RGB" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0x5) std::cout << "Color 1 AAA" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0x6) std::cout << "Color 2 RGB" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0x7) std::cout << "Color 2 AAA" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0x8) std::cout << "Texture RGB" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0x9) std::cout << "Texture AAA" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0xa) std::cout << "Rasterized RGB" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0xb) std::cout << "Rasterized AAA" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0xc) std::cout << "One" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0xd) std::cout << "Half" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0xe) std::cout << "Konstant RGB" << std::endl;
                else if (((colorInputFlags & 0x3E0) >> 5) == 0xf) std::cout << "Zero" << std::endl;

                std::cout << "\tColor input flags (color2): ";
                        if (((colorInputFlags & 0x7C00) >> 10) == 0x0) std::cout << "Previous stage RGB" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0x1) std::cout << "Previous stage AAA" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0x2) std::cout << "Color 0 RGB" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0x3) std::cout << "Color 0 AAA" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0x4) std::cout << "Color 1 RGB" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0x5) std::cout << "Color 1 AAA" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0x6) std::cout << "Color 2 RGB" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0x7) std::cout << "Color 2 AAA" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0x8) std::cout << "Texture RGB" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0x9) std::cout << "Texture AAA" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0xa) std::cout << "Rasterized RGB" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0xb) std::cout << "Rasterized AAA" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0xc) std::cout << "One" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0xd) std::cout << "Half" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0xe) std::cout << "Konstant RGB" << std::endl;
                else if (((colorInputFlags & 0x7C00) >> 10) == 0xf) std::cout << "Zero" << std::endl;
                    
                std::cout << "\tColor input flags (color3): ";
                        if (((colorInputFlags & 0xF8000) >> 15) == 0x0) std::cout << "Previous stage RGB" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0x1) std::cout << "Previous stage AAA" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0x2) std::cout << "Color 0 RGB" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0x3) std::cout << "Color 0 AAA" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0x4) std::cout << "Color 1 RGB" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0x5) std::cout << "Color 1 AAA" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0x6) std::cout << "Color 2 RGB" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0x7) std::cout << "Color 2 AAA" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0x8) std::cout << "Texture RGB" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0x9) std::cout << "Texture AAA" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0xa) std::cout << "Rasterized RGB" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0xb) std::cout << "Rasterized AAA" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0xc) std::cout << "One" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0xd) std::cout << "Half" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0xe) std::cout << "Konstant RGB" << std::endl;
                else if (((colorInputFlags & 0xF8000) >> 15) == 0xf) std::cout << "Zero" << std::endl;


                    
                uint32_t alphaInputFlags;
                reader.readInt32(&alphaInputFlags);
                std::cout << "\tAlpha input flags (color0): ";
                        if ((alphaInputFlags & 0x1f) == 0x0) std::cout << "Previous stage alpha" << std::endl;
                else if ((alphaInputFlags & 0x1f) == 0x1) std::cout << "Color 0 alpha" << std::endl;
                else if ((alphaInputFlags & 0x1f) == 0x2) std::cout << "Color 1 alpha" << std::endl;
                else if ((alphaInputFlags & 0x1f) == 0x3) std::cout << "Color 2 alpha" << std::endl;
                else if ((alphaInputFlags & 0x1f) == 0x4) std::cout << "Texture alpha" << std::endl;
                else if ((alphaInputFlags & 0x1f) == 0x5) std::cout << "Rasterized alpha" << std::endl;
                else if ((alphaInputFlags & 0x1f) == 0x6) std::cout << "Konstant alpha" << std::endl;
                else if ((alphaInputFlags & 0x1f) == 0x7) std::cout << "Zero" << std::endl;

                std::cout << "\tAlpha input flags (color1): ";
                        if (((alphaInputFlags & 0x3E0) >> 5) == 0x0) std::cout << "Previous stage alpha" << std::endl;
                else if (((alphaInputFlags & 0x3E0) >> 5) == 0x1) std::cout << "Color 0 alpha" << std::endl;
                else if (((alphaInputFlags & 0x3E0) >> 5) == 0x2) std::cout << "Color 1 alpha" << std::endl;
                else if (((alphaInputFlags & 0x3E0) >> 5) == 0x3) std::cout << "Color 2 alpha" << std::endl;
                else if (((alphaInputFlags & 0x3E0) >> 5) == 0x4) std::cout << "Texture alpha" << std::endl;
                else if (((alphaInputFlags & 0x3E0) >> 5) == 0x5) std::cout << "Rasterized alpha" << std::endl;
                else if (((alphaInputFlags & 0x3E0) >> 5) == 0x6) std::cout << "Konstant alpha" << std::endl;
                else if (((alphaInputFlags & 0x3E0) >> 5) == 0x7) std::cout << "Zero" << std::endl;

                std::cout << "\tAlpha input flags (color2): ";
                        if (((alphaInputFlags & 0x7C00) >> 10) == 0x0) std::cout << "Previous stage alpha" << std::endl;
                else if (((alphaInputFlags & 0x7C00) >> 10) == 0x1) std::cout << "Color 0 alpha" << std::endl;
                else if (((alphaInputFlags & 0x7C00) >> 10) == 0x2) std::cout << "Color 1 alpha" << std::endl;
                else if (((alphaInputFlags & 0x7C00) >> 10) == 0x3) std::cout << "Color 2 alpha" << std::endl;
                else if (((alphaInputFlags & 0x7C00) >> 10) == 0x4) std::cout << "Texture alpha" << std::endl;
                else if (((alphaInputFlags & 0x7C00) >> 10) == 0x5) std::cout << "Rasterized alpha" << std::endl;
                else if (((alphaInputFlags & 0x7C00) >> 10) == 0x6) std::cout << "Konstant alpha" << std::endl;
                else if (((alphaInputFlags & 0x7C00) >> 10) == 0x7) std::cout << "Zero" << std::endl;

                std::cout << "\tAlpha input flags (color3): ";
                        if (((alphaInputFlags & 0xF8000) >> 15) == 0x0) std::cout << "Previous stage alpha" << std::endl;
                else if (((alphaInputFlags & 0xF8000) >> 15) == 0x1) std::cout << "Color 0 alpha" << std::endl;
                else if (((alphaInputFlags & 0xF8000) >> 15) == 0x2) std::cout << "Color 1 alpha" << std::endl;
                else if (((alphaInputFlags & 0xF8000) >> 15) == 0x3) std::cout << "Color 2 alpha" << std::endl;
                else if (((alphaInputFlags & 0xF8000) >> 15) == 0x4) std::cout << "Texture alpha" << std::endl;
                else if (((alphaInputFlags & 0xF8000) >> 15) == 0x5) std::cout << "Rasterized alpha" << std::endl;
                else if (((alphaInputFlags & 0xF8000) >> 15) == 0x6) std::cout << "Konstant alpha" << std::endl;
                else if (((alphaInputFlags & 0xF8000) >> 15) == 0x7) std::cout << "Zero" << std::endl;

                uint32_t colorCombineFlags;
                reader.readInt32(&colorCombineFlags);
                std::cout << "\tcolor combine flags: " << std::endl;
                std::cout << "\tCombiner operator:   " << ((colorCombineFlags & 0x0000000F) >> 0) << std::endl;
                std::cout << "\tBias:                " << ((colorCombineFlags & 0x00000030) >> 4) << std::endl;
                std::cout << "\tScale:               " << ((colorCombineFlags & 0x000000C0) >> 6) << std::endl;
                std::cout << "\tClamp flag:          " << ((colorCombineFlags & 0x00000100) >> 8) << std::endl;
                std::cout << "\tOutput register:     " << ((colorCombineFlags & 0x00000600) >> 9) << std::endl;
                std::cout << "\tUnused:              " << ((colorCombineFlags & 0xFFFFF800) >> 11) << std::endl;

                uint32_t alphaCombineFlags;
                reader.readInt32(&alphaCombineFlags);
                std::cout << "\talpha combine flags: " << std::endl;
                std::cout << "\tCombiner operator:   " << ((alphaCombineFlags & 0x0000000F) >> 0) << std::endl;
                std::cout << "\tBias:                " << ((alphaCombineFlags & 0x00000030) >> 4) << std::endl;
                std::cout << "\tScale:               " << ((alphaCombineFlags & 0x000000C0) >> 6) << std::endl;
                std::cout << "\tClamp flag:          " << ((alphaCombineFlags & 0x00000100) >> 8) << std::endl;
                std::cout << "\tOutput register:     " << ((alphaCombineFlags & 0x00000600) >> 9) << std::endl;
                std::cout << "\tUnused:              " << ((alphaCombineFlags & 0xFFFFF800) >> 11) << std::endl;



                uint8_t padding;
                reader.readInt8(&padding);

                uint8_t konstAlphaInput;
                reader.readInt8(&konstAlphaInput);

                uint8_t konstColorInput;
                reader.readInt8(&konstColorInput);

                uint8_t rasterizedColorInput;
                reader.readInt8(&rasterizedColorInput);
            }
            for (int ijkl = 0; ijkl < TEVStageCount; ijkl++)
            {
                uint16_t padding;
                reader.readInt16(&padding);

                uint8_t textureTEVInput;
                reader.readInt8(&textureTEVInput);
                std::cout << "texture TEV Input: " << (uint32_t)textureTEVInput << std::endl;

                uint8_t texCoordTEVInput;
                reader.readInt8(&texCoordTEVInput);
                std::cout << "texture coord TEV Input: " << (uint32_t)texCoordTEVInput << std::endl;
            }

            uint32_t texGenCount;
            reader.readInt32(&texGenCount);
            std::cout << "texGen Count: " << texGenCount << std::endl;

            for (int ijkl = 0; ijkl < texGenCount; ijkl++)
            {
                uint32_t texGenFlag;
                reader.readInt32(&texGenFlag);
                std::cout << "texGen flag "<<ijkl<<": " << std::endl;
                std::cout << "\ttexCoord gen type: ";
                switch (ijkl&0xF)
                {
                    case GX_TG_BUMP0:   std::cout << "GX_TG_BUMP0"  << std::endl; break;
                    case GX_TG_BUMP1:   std::cout << "GX_TG_BUMP1"  << std::endl; break;
                    case GX_TG_BUMP2:   std::cout << "GX_TG_BUMP2"  << std::endl; break;
                    case GX_TG_BUMP3:   std::cout << "GX_TG_BUMP3"  << std::endl; break;
                    case GX_TG_BUMP4:   std::cout << "GX_TG_BUMP4"  << std::endl; break;
                    case GX_TG_BUMP5:   std::cout << "GX_TG_BUMP5"  << std::endl; break;
                    case GX_TG_BUMP6:   std::cout << "GX_TG_BUMP6"  << std::endl; break;
                    case GX_TG_BUMP7:   std::cout << "GX_TG_BUMP7"  << std::endl; break;
                    case GX_TG_MTX2x4:  std::cout << "GX_TG_MTX2x4" << std::endl; break;
                    case GX_TG_MTX3x4:  std::cout << "GX_TG_MTX3x4" << std::endl; break;
                    case GX_TG_SRTG:    std::cout << "GX_TG_SRTG"   << std::endl; break;
                }
                std::cout << "\ttexCoord src: ";
                switch ((ijkl & 0x1F0) >> 4)
                {
                    case GX_TG_BINRM    : std::cout << "GX_TG_BINRM     " << std::endl;break;
                    case GX_TG_COLOR0   : std::cout << "GX_TG_COLOR0    " << std::endl;break;
                    case GX_TG_COLOR1   : std::cout << "GX_TG_COLOR1    " << std::endl;break;
                    case GX_TG_NRM      : std::cout << "GX_TG_NRM       " << std::endl;break;
                    case GX_TG_POS      : std::cout << "GX_TG_POS       " << std::endl;break;
                    case GX_TG_TANGENT  : std::cout << "GX_TG_TANGENT   " << std::endl;break;
                    case GX_TG_TEX0     : std::cout << "GX_TG_TEX0      " << std::endl;break;
                    case GX_TG_TEX1     : std::cout << "GX_TG_TEX1      " << std::endl;break;
                    case GX_TG_TEX2     : std::cout << "GX_TG_TEX2      " << std::endl;break;
                    case GX_TG_TEX3     : std::cout << "GX_TG_TEX3      " << std::endl;break;
                    case GX_TG_TEX4     : std::cout << "GX_TG_TEX4      " << std::endl;break;
                    case GX_TG_TEX5     : std::cout << "GX_TG_TEX5      " << std::endl;break;
                    case GX_TG_TEX6     : std::cout << "GX_TG_TEX6      " << std::endl;break;
                    case GX_TG_TEX7     : std::cout << "GX_TG_TEX7      " << std::endl;break;
                    case GX_TG_TEXCOORD0: std::cout << "GX_TG_TEXCOORD0 " << std::endl;break;
                    case GX_TG_TEXCOORD1: std::cout << "GX_TG_TEXCOORD1 " << std::endl;break;
                    case GX_TG_TEXCOORD2: std::cout << "GX_TG_TEXCOORD2 " << std::endl;break;
                    case GX_TG_TEXCOORD3: std::cout << "GX_TG_TEXCOORD3 " << std::endl;break;
                    case GX_TG_TEXCOORD4: std::cout << "GX_TG_TEXCOORD4 " << std::endl;break;
                    case GX_TG_TEXCOORD5: std::cout << "GX_TG_TEXCOORD5 " << std::endl;break;
                    case GX_TG_TEXCOORD6: std::cout << "GX_TG_TEXCOORD6 " << std::endl;break;
                }
                std::cout << "\ttex matrix index: ";
                switch (((ijkl & 0x3E00) >> 9) + 30)
                {
                    case GX_IDENTITY: std::cout << "GX_IDENTITY" << std::endl;break;
                    case GX_TEXMTX0 : std::cout << "GX_TEXMTX0 " << std::endl;break;
                    case GX_TEXMTX1 : std::cout << "GX_TEXMTX1 " << std::endl;break;
                    case GX_TEXMTX2 : std::cout << "GX_TEXMTX2 " << std::endl;break;
                    case GX_TEXMTX3 : std::cout << "GX_TEXMTX3 " << std::endl;break;
                    case GX_TEXMTX4 : std::cout << "GX_TEXMTX4 " << std::endl;break;
                    case GX_TEXMTX5 : std::cout << "GX_TEXMTX5 " << std::endl;break;
                    case GX_TEXMTX6 : std::cout << "GX_TEXMTX6 " << std::endl;break;
                    case GX_TEXMTX7 : std::cout << "GX_TEXMTX7 " << std::endl;break;
                    case GX_TEXMTX8 : std::cout << "GX_TEXMTX8 " << std::endl;break;
                    case GX_TEXMTX9 : std::cout << "GX_TEXMTX9 " << std::endl;break;
                }
                std::cout << "\tnormalize flag: " << ((ijkl&0x4000)>0?"on":"off") << std::endl;
                std::cout << "\tpost transform tex matrix index: ";
                switch (((ijkl & 0x1F8000) >> 15)+64)
                {
                    case GX_DTTIDENTITY: std::cout << "GX_DTTIDENTITY" << std::endl;break;
                    case GX_DTTMTX0    : std::cout << "GX_DTTMTX0    " << std::endl;break;
                    case GX_DTTMTX1    : std::cout << "GX_DTTMTX1    " << std::endl;break;
                    case GX_DTTMTX10   : std::cout << "GX_DTTMTX10   " << std::endl;break;
                    case GX_DTTMTX11   : std::cout << "GX_DTTMTX11   " << std::endl;break;
                    case GX_DTTMTX12   : std::cout << "GX_DTTMTX12   " << std::endl;break;
                    case GX_DTTMTX13   : std::cout << "GX_DTTMTX13   " << std::endl;break;
                    case GX_DTTMTX14   : std::cout << "GX_DTTMTX14   " << std::endl;break;
                    case GX_DTTMTX15   : std::cout << "GX_DTTMTX15   " << std::endl;break;
                    case GX_DTTMTX16   : std::cout << "GX_DTTMTX16   " << std::endl;break;
                    case GX_DTTMTX17   : std::cout << "GX_DTTMTX17   " << std::endl;break;
                    case GX_DTTMTX18   : std::cout << "GX_DTTMTX18   " << std::endl;break;
                    case GX_DTTMTX19   : std::cout << "GX_DTTMTX19   " << std::endl;break;
                    case GX_DTTMTX2    : std::cout << "GX_DTTMTX2    " << std::endl;break;
                    case GX_DTTMTX3    : std::cout << "GX_DTTMTX3    " << std::endl;break;
                    case GX_DTTMTX4    : std::cout << "GX_DTTMTX4    " << std::endl;break;
                    case GX_DTTMTX5    : std::cout << "GX_DTTMTX5    " << std::endl;break;
                    case GX_DTTMTX6    : std::cout << "GX_DTTMTX6    " << std::endl;break;
                    case GX_DTTMTX7    : std::cout << "GX_DTTMTX7    " << std::endl;break;
                    case GX_DTTMTX8    : std::cout << "GX_DTTMTX8    " << std::endl;break;
                    case GX_DTTMTX9    : std::cout << "GX_DTTMTX9    " << std::endl;break;
                }
            }

            reader.getloc = materialStartingMarker+ CMDLMap[AssetID].materialSets[imat].materialEndOffsets[ijk];

        }
        //upperGetLoc += CMDLMap[AssetID].dataSectionSizes[imat];
        //subGetLoc = upperGetLoc;
        reader.toNextSection();
    }

    std::cout << "reading geometry data from " << std::hex << reader.getloc << std::dec << std::endl;
    loadGeometry(reader, &CMDLMap[AssetID].geometry, CMDLMap[AssetID].materialSets[0]);//TEMP


    
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

    versionNumberMajor = _byteswap_ushort(versionNumberMajor);
    versionNumberMinor = _byteswap_ushort(versionNumberMinor);
    unused = _byteswap_ulong(unused);
    assetCount_namedResourcesTable = _byteswap_ulong(assetCount_namedResourcesTable);

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
        nameLength = _byteswap_ulong(nameLength);
        nameString.resize(nameLength);
        f.read(nameString.data(), nameLength);
        std::cout << nameLength << std::endl;


        std::cout << "\tAsset Type              "; std::cout.write(fourCC, 4) << std::endl;
        std::cout << "\tAsset ID                " << AssetID << std::endl;
        std::cout << "\tAsset name              "; std::cout.write(nameString.data(), nameLength) << std::endl;
    }

    f.read(reinterpret_cast<char*>(&assetCount_resourcesTable), sizeof(assetCount_resourcesTable));

    assetCount_resourcesTable = _byteswap_ulong(assetCount_resourcesTable);
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



        compressionFlag = _byteswap_ulong(compressionFlag);
        AssetID = _byteswap_ulong(AssetID);
        size = _byteswap_ulong(size);
        offset = _byteswap_ulong(offset);

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
            decompressedSize = _byteswap_ulong(decompressedSize);
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
                txtrFormat = _byteswap_ulong(txtrFormat);
                std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrFormat)) << "] texture format:" << txtrFormat << std::dec << std::endl;
                subGetLoc += sizeof(txtrFormat);

                uint16_t txtrWidth;

                memcpy(&txtrWidth, &rawFile[subGetLoc], sizeof(txtrWidth));
                txtrWidth = _byteswap_ushort(txtrWidth);
                std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrWidth)) << "] texture width:" << txtrWidth << std::dec << std::endl;
                subGetLoc += sizeof(txtrWidth);

                uint16_t txtrHeight;

                memcpy(&txtrHeight, &rawFile[subGetLoc], sizeof(txtrHeight));
                txtrHeight = _byteswap_ushort(txtrHeight);
                std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrHeight)) << "] texture height:" << txtrHeight << std::dec << std::endl;
                subGetLoc += sizeof(txtrHeight);

                uint32_t mipCount;

                memcpy(&mipCount, &rawFile[subGetLoc], sizeof(mipCount));
                mipCount = _byteswap_ulong(mipCount);
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