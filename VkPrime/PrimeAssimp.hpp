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

#include <zlib.h>
typedef uint32_t PrimeAssetID;

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
    //todo: how big is a Vector3?
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
    std::vector<uint32_t> pos_indices;
    std::vector<uint32_t> nml_indices;
    std::vector<uint32_t> uvc_indices;

};
struct CMDLGeometry {
    std::vector<float> vertexCoords;
    std::vector<float> normals;
    std::vector<float> floatUVCoords;
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
std::unordered_map<PrimeAssetID, CMDL> CMDLMap;


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
        for (int i = 0; i < 500; i++) {
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

                    memcpy(&txtrFormat, &rawFile.data()[subGetLoc], sizeof(txtrFormat));
                    txtrFormat = swap_endian<uint32_t>(txtrFormat);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrFormat)) << "] texture format:" << txtrFormat << std::dec << std::endl;
                    subGetLoc += sizeof(txtrFormat);

                    uint16_t txtrWidth;

                    memcpy(&txtrWidth, &rawFile.data()[subGetLoc], sizeof(txtrWidth));
                    txtrWidth = swap_endian<uint16_t>(txtrWidth);
                    std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrWidth)) << "] texture width:" << txtrWidth << std::dec << std::endl;
                    subGetLoc += sizeof(txtrWidth);

                    uint16_t txtrHeight;

                    memcpy(&txtrHeight, &rawFile.data()[subGetLoc], sizeof(txtrHeight));
                    txtrHeight = swap_endian<uint16_t>(txtrHeight);
                    std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrHeight)) << "] texture height:" << txtrHeight << std::dec << std::endl;
                    subGetLoc += sizeof(txtrHeight);

                    uint32_t mipCount;

                    memcpy(&mipCount, &rawFile.data()[subGetLoc], sizeof(mipCount));
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
                   //     memcpy(&textureChunk, &rawFile.data()[subGetLoc], 32);
                   //     std::vector<uint8_t> imageChunk;
                   //     imageChunk.resize(8 * 8);
                   //
                   //     //squish::Decompress(&imageChunk.data()[0], &textureChunk.data()[0], txtrFormat);
                   //
                   // }

                }
                else if (fourCC[0] == 'C' && fourCC[1] == 'M' && fourCC[2] == 'D' && fourCC[3] == 'L' && tempcounter==0)
                {
                    
                    //std::cout << "model found!" << std::endl;
                    
                    //dumpToFile("dump.cmdl", rawFile.data(),rawFile.size());
                    if (tempcounter > 0)
                        continue;
                    tempcounter++;
                    uint64_t subGetLoc = 0;
                    memcpy(&CMDLMap[AssetID].magic, &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].magic));
                    CMDLMap[AssetID].magic = swap_endian<int32_t>(CMDLMap[AssetID].magic);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].magic)) << "] magic:" << CMDLMap[AssetID].magic << std::dec << std::endl;
                    
                    subGetLoc += sizeof(CMDLMap[AssetID].magic);
                    tempID = AssetID;

                    memcpy(&CMDLMap[AssetID].version, &rawFile.data()[subGetLoc], 4);
                    CMDLMap[AssetID].version = swap_endian<int32_t>(CMDLMap[AssetID].version);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].version)) << "] version:" << CMDLMap[AssetID].version << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLMap[AssetID].version);

                    memcpy(&CMDLMap[AssetID].flags, &rawFile.data()[subGetLoc], 4);
                    CMDLMap[AssetID].flags = swap_endian<int32_t>(CMDLMap[AssetID].flags);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].flags)) << "] flags:" << CMDLMap[AssetID].flags << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLMap[AssetID].flags);

                    memcpy(CMDLMap[AssetID].ModelAxisAlignedBoundingBox, &rawFile.data()[subGetLoc], sizeof(float) * 6);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(float) * 6) << "] Model Axis-Aligned Bounding Box:";
                    for (int ijk = 0; ijk < 6; ijk++)
                    {
                        CMDLMap[AssetID].ModelAxisAlignedBoundingBox[ijk] = swap_endian<float>(CMDLMap[AssetID].ModelAxisAlignedBoundingBox[ijk]);
                        std::cout << CMDLMap[AssetID].ModelAxisAlignedBoundingBox[ijk];
                    }
                    std::cout << std::dec << std::endl;
                    subGetLoc += sizeof(float) * 6;

                    memcpy(&CMDLMap[AssetID].dataSectionCount, &rawFile.data()[subGetLoc], 4);
                    CMDLMap[AssetID].dataSectionCount = swap_endian<int32_t>(CMDLMap[AssetID].dataSectionCount);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].dataSectionCount)) << "] data Section Count:" << CMDLMap[AssetID].dataSectionCount << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLMap[AssetID].dataSectionCount);

                    memcpy(&CMDLMap[AssetID].MaterialSetCount, &rawFile.data()[subGetLoc], 4);
                    CMDLMap[AssetID].MaterialSetCount = swap_endian<int32_t>(CMDLMap[AssetID].MaterialSetCount);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].MaterialSetCount)) << "] Material Set Count:" << CMDLMap[AssetID].MaterialSetCount << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLMap[AssetID].MaterialSetCount);



                    CMDLMap[AssetID].materialSets.resize(CMDLMap[AssetID].MaterialSetCount);





                    CMDLMap[AssetID].dataSectionSizes.resize(CMDLMap[AssetID].dataSectionCount);

                    for (int ijk = 0; ijk < CMDLMap[AssetID].dataSectionCount; ijk++)
                    {
                        memcpy(&CMDLMap[AssetID].dataSectionSizes[ijk], &rawFile.data()[subGetLoc], sizeof(uint32_t));
                        CMDLMap[AssetID].dataSectionSizes[ijk] = swap_endian<uint32_t>(CMDLMap[AssetID].dataSectionSizes[ijk]);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc + sizeof(uint32_t) << "]" << "data section " << std::dec << ijk << " size: " << CMDLMap[AssetID].dataSectionSizes[ijk] << std::endl;
                        subGetLoc += sizeof(uint32_t);

                    }


                    //subGetLoc += sizeof(uint32_t)*CMDLMap[AssetID].dataSectionCount;



                    subGetLoc += 32 - subGetLoc % 32;

                    uint32_t upperGetLoc = subGetLoc;
                    std::cout << "reading material data from " << std::hex << subGetLoc << std::dec << std::endl;


                    if (true)
                        for (int imat = 0; imat < CMDLMap[AssetID].MaterialSetCount; imat++)
                        {

                            memcpy(&(CMDLMap[AssetID].materialSets[imat].textureCount), &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].materialSets[imat].textureCount));
                            CMDLMap[AssetID].materialSets[imat].textureCount = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].textureCount);
                            std::cout << "textures: " << CMDLMap[AssetID].materialSets[imat].textureCount << std::endl;
                            CMDLMap[AssetID].materialSets[imat].textureFileIDs.resize(CMDLMap[AssetID].materialSets[imat].textureCount);
                            memcpy(CMDLMap[AssetID].materialSets[imat].textureFileIDs.data(), &rawFile.data()[subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].textureCount)], sizeof(CMDLMap[AssetID].materialSets[imat].textureFileIDs.data()) * CMDLMap[AssetID].materialSets[imat].textureFileIDs.size());
                            for (int tx = 0; tx < CMDLMap[AssetID].materialSets[imat].textureCount; tx++) {
                                memcpy(&(CMDLMap[AssetID].materialSets[imat].textureFileIDs[tx]), &rawFile.data()[subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].textureCount) + tx * sizeof(uint32_t)], sizeof(uint32_t));
                                CMDLMap[AssetID].materialSets[imat].textureFileIDs[tx] = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].textureFileIDs[tx]);
                                std::cout << "texture used: " << std::hex << CMDLMap[AssetID].materialSets[imat].textureFileIDs[tx] << std::dec << std::endl;
                            }


                            memcpy(&(CMDLMap[AssetID].materialSets[imat].materialCount), &rawFile.data()[subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].textureCount) + CMDLMap[AssetID].materialSets[imat].textureCount * sizeof(uint32_t)], sizeof(CMDLMap[AssetID].materialSets[imat].materialCount));
                            CMDLMap[AssetID].materialSets[imat].materialCount = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materialCount);
                            std::cout << CMDLMap[AssetID].materialSets[imat].materialCount << std::endl;
                            CMDLMap[AssetID].materialSets[imat].materialEndOffsets.resize(CMDLMap[AssetID].materialSets[imat].materialCount);
                            for (int mc = 0; mc < CMDLMap[AssetID].materialSets[imat].materialCount; mc++) {
                                memcpy(&(CMDLMap[AssetID].materialSets[imat].materialEndOffsets[mc]), &rawFile.data()[subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].textureCount) + CMDLMap[AssetID].materialSets[imat].textureCount * sizeof(uint32_t) + sizeof(CMDLMap[AssetID].materialSets[imat].materialCount) + mc * sizeof(uint32_t)], sizeof(uint32_t));
                                CMDLMap[AssetID].materialSets[imat].materialEndOffsets[mc] = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materialEndOffsets[mc]);
                                std::cout << "material end offset: " << std::hex << CMDLMap[AssetID].materialSets[imat].materialEndOffsets[mc] << std::dec << std::endl;
                            }
                            subGetLoc = subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].textureCount) + CMDLMap[AssetID].materialSets[imat].textureCount * sizeof(uint32_t) + sizeof(CMDLMap[AssetID].materialSets[imat].materialCount) + CMDLMap[AssetID].materialSets[imat].materialCount * sizeof(uint32_t);

                            uint32_t materialStartingMarker=subGetLoc;

                            CMDLMap[AssetID].materialSets[imat].materials.resize(CMDLMap[AssetID].materialSets[imat].materialCount+5);
                            for (int ijk=0; ijk < CMDLMap[AssetID].materialSets[imat].materialCount;ijk++)
                            {
                                uint32_t flags;
                                memcpy(&flags, &rawFile.data()[subGetLoc], sizeof(flags));
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
                                memcpy(&TC, &rawFile.data()[subGetLoc], sizeof(TC));
                                TC = swap_endian<int32_t>(TC);
                                std::cout << "Texture Count: " << TC << std::endl;
                                subGetLoc += sizeof(TC);
                                while (TC > 100) {}
                                CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices.resize(TC);
                                std::cout << "textures:" << std::endl;
                                for (int tx = 0; tx < TC; tx += sizeof(uint32_t)) {
                                    memcpy(&(CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices[tx]), &rawFile.data()[subGetLoc + tx], sizeof(uint32_t));
                                    CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices[tx] = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices[tx]);
                                    //std::cout << CMDLMap[AssetID].materialSets[imat].textureFileIndices[tx] << std::endl;
                                    std::cout << "\ttexture: " << std::hex << CMDLMap[AssetID].materialSets[imat].textureFileIDs[CMDLMap[AssetID].materialSets[imat].materials[ijk].textureFileIndices[tx]] << std::dec << std::endl;
                                }

                                subGetLoc += TC * sizeof(uint32_t);

                                //uint32_t vertexAtributeFlags;
                                memcpy(&CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags, &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].materialSets[imat].materials[ijk].vertexAtributeFlags));
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
                                memcpy(&groupIndex, &rawFile.data()[subGetLoc], sizeof(groupIndex));
                                groupIndex = swap_endian<uint32_t>(groupIndex);
                                std::cout << "group index: " << groupIndex << std::endl;
                                subGetLoc += sizeof(groupIndex);
                                if ((flags & 0x08) > 0)
                                {
                                    uint32_t KonstCount;
                                    memcpy(&KonstCount, &rawFile.data()[subGetLoc], sizeof(KonstCount));
                                    KonstCount = swap_endian<uint32_t>(KonstCount);
                                    std::cout << KonstCount << std::endl;
                                    CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors.resize(KonstCount);
                                    for (int mc = 0; mc < KonstCount; mc++) {
                                        memcpy(&(CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors[mc]), &rawFile.data()[subGetLoc + sizeof(KonstCount) + mc * sizeof(uint32_t)], sizeof(uint32_t));
                                        CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors[mc] = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors[mc]);
                                        std::cout << "konst color " << mc << ": " << std::hex << CMDLMap[AssetID].materialSets[imat].materials[ijk].konstColors[mc] << std::dec << std::endl;
                                    }
                                    subGetLoc += sizeof(KonstCount) + KonstCount * sizeof(uint32_t);
                                }
                                std::cout << "offset: " << std::hex << subGetLoc << std::dec << std::endl;
                                short blendDestFactor;
                                memcpy(&blendDestFactor, &rawFile.data()[subGetLoc], sizeof(blendDestFactor));
                                blendDestFactor = swap_endian<short>(blendDestFactor);
                                std::cout << "blendDestFactor: " << blendDestFactor << std::endl;
                                subGetLoc += sizeof(blendDestFactor);

                                short blendSourceFactor;
                                memcpy(&blendSourceFactor, &rawFile.data()[subGetLoc], sizeof(blendSourceFactor));
                                blendSourceFactor = swap_endian<short>(blendSourceFactor);
                                std::cout << "blendSourceFactor: " << blendSourceFactor << std::endl;
                                subGetLoc += sizeof(blendSourceFactor);

                                if ((flags & 0x400) != 0)
                                {
                                    uint32_t reflectionIndirectTextureIndex;
                                    memcpy(&reflectionIndirectTextureIndex, &rawFile.data()[subGetLoc], sizeof(reflectionIndirectTextureIndex));
                                    reflectionIndirectTextureIndex = swap_endian<uint32_t>(reflectionIndirectTextureIndex);
                                    std::cout << "reflection Indirect Texture Index: " << reflectionIndirectTextureIndex << std::endl;
                                    subGetLoc += sizeof(reflectionIndirectTextureIndex);
                                }


                                //
                                memcpy(&(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount), &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount));
                                CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount);
                                std::cout << "color channel count: " << CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount << std::endl;
                                std::cout << "offset: " << std::hex << subGetLoc << std::dec << std::endl;
                                CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags.resize(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount);
                                for (int mc = 0; mc < CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount; mc++) {
                                    memcpy(&(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags[mc]), &rawFile.data()[subGetLoc + sizeof(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount) + mc * sizeof(uint32_t)], sizeof(uint32_t));
                                    CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags[mc] = swap_endian<uint32_t>(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags[mc]);
                                    std::cout << "color channel flags: " << CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelFlags[mc] << std::dec << std::endl;
                                }
                                subGetLoc += sizeof(CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount) + CMDLMap[AssetID].materialSets[imat].materials[ijk].ColorChannelCount * sizeof(uint32_t);


                                uint32_t TEVStageCount;
                                memcpy(&TEVStageCount, &rawFile.data()[subGetLoc], sizeof(TEVStageCount));
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


                    CMDLMap[AssetID].geometry.vertexCoords.resize(
                        (
                            CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount] -
                            (CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount]) % (sizeof(float) * 3)
                            )
                        / (sizeof(float))
                    );
                    std::cout << "number of vert coords: " << CMDLMap[AssetID].geometry.vertexCoords.size() << std::endl;
                    for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.vertexCoords.size(); ijk++)
                    {
                        memcpy(&CMDLMap[AssetID].geometry.vertexCoords[ijk], &rawFile.data()[subGetLoc], sizeof(uint32_t));
                        CMDLMap[AssetID].geometry.vertexCoords[ijk] = swap_endian<float>(CMDLMap[AssetID].geometry.vertexCoords[ijk]);

                        subGetLoc += sizeof(float);
                    }
                    

                    //CMDLMap[AssetID].geometry.vertexCoords = std::vector<float>(rawFile.data() + subGetLoc, rawFile.data()+ CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount] - (CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount]) % (sizeof(float) * 3));


                    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount];
                    subGetLoc = upperGetLoc;
                    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "reading normals" << std::endl;

                    CMDLMap[AssetID].geometry.normals.resize(
                        (
                            CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 1] -
                            (CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 1]) % (sizeof(float) * 3)
                            ) / sizeof(float)
                    );
                    std::cout << "number of normal coords: " << CMDLMap[AssetID].geometry.normals.size() << std::endl;


                    for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.normals.size(); ijk++)
                    {
                        memcpy(&CMDLMap[AssetID].geometry.normals[ijk], &rawFile.data()[subGetLoc], sizeof(float));
                        CMDLMap[AssetID].geometry.normals[ijk] = swap_endian<float>(CMDLMap[AssetID].geometry.normals[ijk]);
                        subGetLoc += sizeof(float);
                    }
                    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 1];
                    subGetLoc = upperGetLoc;

                    //std::cout << std::hex << subGetLoc << std::dec << std::endl;
                    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "skipping color data" << std::endl;

                    //no need to read color data, it's all empty

                    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 2];
                    subGetLoc = upperGetLoc;

                    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "reading float UV coords" << std::endl;
                    CMDLMap[AssetID].geometry.floatUVCoords.resize(
                        (
                            CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 3] -
                            (CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 3]) % (sizeof(float) * 2)
                            ) / sizeof(float)
                    );
                    std::cout << "number of float UV coords: " << CMDLMap[AssetID].geometry.floatUVCoords.size() << std::endl;

                    for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.floatUVCoords.size(); ijk++)
                    {
                        memcpy(&CMDLMap[AssetID].geometry.floatUVCoords[ijk], &rawFile.data()[subGetLoc], sizeof(float));
                        CMDLMap[AssetID].geometry.floatUVCoords[ijk] = swap_endian<float>(CMDLMap[AssetID].geometry.floatUVCoords[ijk]);
                        subGetLoc += sizeof(float);
                    }

                    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 3];
                    subGetLoc = upperGetLoc;


                    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "skipping short UV coords" << std::endl;
                    //short uv coords are COMPLETELY empty for this mesh, but I'll need to implement it for the future
                    upperGetLoc += CMDLMap[AssetID].dataSectionSizes[CMDLMap[AssetID].MaterialSetCount + 4];
                    subGetLoc = upperGetLoc;

                    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "reading header data" << std::endl;
                    //the moment of truth:

                    memcpy(&CMDLMap[AssetID].geometry.surfaceCount, &rawFile.data()[subGetLoc], 4);
                    CMDLMap[AssetID].geometry.surfaceCount = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaceCount);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaceCount)) << "] surface count:" << CMDLMap[AssetID].geometry.surfaceCount << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaceCount);

                    CMDLMap[AssetID].geometry.surfaceOffsets.resize(CMDLMap[AssetID].geometry.surfaceCount);

                    for (int ijk = 0; ijk < CMDLMap[AssetID].geometry.surfaceCount; ijk++)
                    {
                        memcpy(&CMDLMap[AssetID].geometry.surfaceOffsets[ijk], &rawFile.data()[subGetLoc], sizeof(uint32_t));
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
                            memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[ijk], &rawFile.data()[subGetLoc], sizeof(float));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[ijk] = swap_endian<float>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[ijk]);
                            subGetLoc += sizeof(float);
                        }
                        std::cout << "center point: " << CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[0] << ", " << CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[1] << ", " << CMDLMap[AssetID].geometry.surfaces[surfaceNum].centerPoint[2] << std::endl;

                        memcpy(
                            &CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex,
                            &rawFile.data()[subGetLoc],
                            sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex)
                        );
                        CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex)) << "] matIndex:" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex);

                        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa, &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa));
                        CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa = swap_endian<uint16_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa)) << "] mantissa:" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].mantissa);

                        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize, &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize));
                        CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize = swap_endian<uint16_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize)) << "] display list size:" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].displayListSize);

                        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer, &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer));
                        CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer)) << "] parentModelPointer (always 0):" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].parentModelPointer);

                        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer, &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer));
                        CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer)) << "] nextSurfacePointer (always 0):" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].nextSurfacePointer);

                        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize, &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize));
                        CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize = swap_endian<uint32_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize)) << "] extraDataSize (always 0):" << CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].extraDataSize);

                        CMDLMap[AssetID].geometry.surfaces.resize(CMDLMap[AssetID].geometry.surfaceCount);
                        for (int ijk = 0; ijk < 3; ijk++)
                        {
                            memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].surfaceNormal[ijk], &rawFile.data()[subGetLoc], sizeof(float));
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

                        memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags, &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags));
                        //std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(GXFlags)) << "] GXFlags:" << GXFlags << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags);

                        while (CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags > 0)
                        {


                            std::bitset<8> GXFlagBits(CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags);

                            std::cout << GXFlagBits << std::endl;

                            memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount, &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount));
                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount = swap_endian<uint16_t>(CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount);
                            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount)) << "] vertex count:" << std::dec << CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount << std::dec << std::endl;
                            subGetLoc += sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].vertexCount);

                            uint16_t pos_index1before = 0;
                            uint16_t pos_index2before = 0;
                            uint16_t pos_indexwaybefore = 0;

                            uint16_t nml_index1before = 0;
                            uint16_t nml_index2before = 0;
                            uint16_t nml_indexwaybefore = 0;

                            uint16_t uvc_index1before = 0;
                            uint16_t uvc_index2before = 0;
                            uint16_t uvc_indexwaybefore = 0;
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
                                    memcpy(&pos_vIndex, &rawFile.data()[subGetLoc], sizeof(pos_vIndex));
                                    pos_vIndex = swap_endian<uint16_t>(pos_vIndex);
                                    subGetLoc += sizeof(pos_vIndex);
                                }
                                else
                                {
                                    std::cout << "epic failure" << std::endl;
                                }
                                if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC) > 0) {
                                    memcpy(&nml_vIndex, &rawFile.data()[subGetLoc], sizeof(nml_vIndex));
                                    nml_vIndex = swap_endian<uint16_t>(nml_vIndex);
                                    subGetLoc += sizeof(nml_vIndex);
                                }
                                if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x300) > 0) {
                                    memcpy(&uvc1_vIndex, &rawFile.data()[subGetLoc], sizeof(uvc1_vIndex));
                                    uvc1_vIndex = swap_endian<uint16_t>(uvc1_vIndex);
                                    subGetLoc += sizeof(uvc1_vIndex);
                                }
                                if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC00) > 0)
                                {
                                    memcpy(&uvc2_vIndex, &rawFile.data()[subGetLoc], sizeof(uvc2_vIndex));
                                    uvc2_vIndex = swap_endian<uint16_t>(uvc2_vIndex);
                                    subGetLoc += sizeof(uvc2_vIndex);
                                }
                                if (ijk == 0) {
                                    pos_indexwaybefore = pos_vIndex;
                                    nml_indexwaybefore = nml_vIndex;
                                    uvc_indexwaybefore = uvc1_vIndex;
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
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_indexwaybefore));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_index1before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_vIndex));
                                        }
                                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC) > 0)
                                        {
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_indexwaybefore));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_index1before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_vIndex));
                                        }
                                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x300) > 0)
                                        {
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_indexwaybefore));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_index1before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc1_vIndex));
                                        }
                                    }
                                }
                                else if (((CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags & 0xF8) == 0x90))
                                {
                                    if (ijk > 1 && (ijk + 1) % 3 == 0) {
                                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x3) > 0)
                                        {
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_index1before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_index2before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_vIndex));
                                        }
                                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC) > 0)
                                        {
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_index1before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_index2before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_vIndex));
                                        }
                                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x300) > 0)
                                        {
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_index1before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_index2before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc1_vIndex));
                                        }
                                    }
                                }
                                else if (((CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags & 0xF8) == 0x98))
                                {
                                    if (ijk > 1) {
                                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x3) > 0)
                                        {
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_index2before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_index1before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_vIndex));
                                        }
                                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC) > 0)
                                        {
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_index2before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_index1before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_vIndex));
                                        }
                                        if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0x300) > 0)
                                        {
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_index2before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_index1before));
                                            CMDLMap[AssetID].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc1_vIndex));
                                        }

                                    }
                                }
                                else
                                {
                                    std::cout << "unsupported primitive" << std::endl;
                                }
                                pos_index2before = pos_index1before;
                                pos_index1before = pos_vIndex;

                                
                                //if ((CMDLMap[AssetID].materialSets[0].materials[CMDLMap[AssetID].geometry.surfaces[surfaceNum].matIndex].vertexAtributeFlags & 0xC) > 0)
                                //{
                                //    uint16_t vIndex;variable 'pos_vIndex' is being used
                                //    memcpy(&vIndex, &rawFile.data()[subGetLoc], sizeof(vIndex));
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
                                //    memcpy(&vIndex, &rawFile.data()[subGetLoc], sizeof(vIndex));
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
                                //    memcpy(&vIndex, &rawFile.data()[subGetLoc], sizeof(vIndex));
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

                            memcpy(&CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags, &rawFile.data()[subGetLoc], sizeof(CMDLMap[AssetID].geometry.surfaces[surfaceNum].GXFlags));
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
            }
            else if (compressionFlag == 0)
            {
                if (fourCC[0] == 'S' && fourCC[1] == 'T' && fourCC[2] == 'R' && fourCC[3] == 'G')
                {
                    int32_t magic;
                    f.read(reinterpret_cast<char*>(&magic), sizeof(magic));

                    magic = swap_endian<int32_t>(magic);
                    std::cout << "magic: " << std::hex << magic << std::dec << std::endl;


                    int32_t version;
                    int32_t langCount;
                    int32_t stringCount;

                    f.read(reinterpret_cast<char*>(&version), sizeof(version));
                    f.read(reinterpret_cast<char*>(&langCount), sizeof(langCount));
                    f.read(reinterpret_cast<char*>(&stringCount), sizeof(stringCount));

                    version = swap_endian<int32_t>(version);
                    langCount = swap_endian<int32_t>(langCount);
                    stringCount = swap_endian<int32_t>(stringCount);

                    std::cout << "version: " << std::hex << version << std::dec << std::endl;
                    std::cout << "langCount: " << std::hex << langCount << std::dec << std::endl;
                    std::cout << "string count: " << std::hex << stringCount << std::dec << std::endl;
                    for (int j = 0; j < langCount; j++) {
                        f.read(fourCC, 4);
                        std::cout << "Language ID: "; std::cout.write(fourCC, 4) << std::endl;
                        uint32_t posOffset;
                        f.read(reinterpret_cast<char*>(&posOffset), sizeof(posOffset));
                        posOffset = swap_endian<uint32_t>(posOffset);
                        std::cout << "language location offset: " << posOffset << std::endl;

                    }
                    for (int j = 0; j < langCount; j++)
                    {
                        uint32_t stringTableSize;
                        f.read(reinterpret_cast<char*>(&stringTableSize), sizeof(stringTableSize));
                        stringTableSize = swap_endian<uint32_t>(stringTableSize);
                        std::cout << "string table size: " << stringTableSize << std::endl;
                        std::vector<uint32_t> stringOffsets;
                        stringOffsets.resize(stringCount);
                        uint32_t disjointOffset = f.tellg();
                        for (int k = 0; k < stringCount; k++)
                        {
                            f.read(reinterpret_cast<char*>(&stringOffsets[k]), sizeof(uint32_t));
                            stringOffsets[k] = swap_endian<uint32_t>(stringOffsets[k]);
                        }
                        std::vector<std::string> strings;
                        strings.resize(stringCount);
                        for (int k = 0; k < stringCount; k++)
                        {
                            f.seekg(stringOffsets.at(k) + disjointOffset);
                            char temp;
                            std::string tempstr = "";
                            f.get();
                            while ((temp = f.get()) != '\0') {
                                tempstr += temp; f.get();
                            }
                            strings[k] = tempstr;
                            std::cout << tempstr << std::endl;
                        }
                    }

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