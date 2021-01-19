#include <vector>
#include <cstdint>
#include <iostream>
#include <sal.h>
extern "C" {
	void _cpy8(uint8_t *dest, uint8_t *src);
	void _cpy16(uint16_t *dest, uint8_t *src);
	void _cpy32(uint32_t *dest, uint8_t *src);
	void _cpy64(uint64_t *dest, uint8_t *src);
	void _cpyFloat(float *dest, uint8_t *src);

}
class FileReader
{
public:
	uint8_t* src;
	uint64_t getloc;
	uint32_t sectionIndex = 0;
	uint32_t sectionCount = 0;
	uint32_t sectionAncor = 0;
	std::vector<uint32_t> sectionSizes;
	uint32_t dataRemaining()
	{
		int counter = sectionAncor;
		for (int i = 0; i < sectionIndex; i++)
		{
			counter += sectionSizes[i];
		}
		return counter - (getloc - sectionAncor);
	}
	void init(uint8_t* input)
	{
		src = input;
		getloc = 0;
	}
	void addSectionSize(uint32_t sectionSize)
	{
		sectionCount++;
		sectionSizes.push_back(sectionSize);
	}
	void toNextSection()
	{
		getloc = sectionAncor;
		for (  int i = 0 ; i < sectionIndex+1; i++)
		{
		getloc += sectionSizes[i];
		}
		sectionIndex++;
		std::cout << "MOVING TO SECTION " << sectionIndex << std::endl;
		std::cout << "SECTION " << sectionIndex << " SIZE: " << getSectionSize() << std::endl;
	}
	uint32_t getSectionSize()
	{
		return sectionSizes[sectionIndex];
	}
	void showDiag()
	{
		uint64_t temp_getloc = getloc;
		uint32_t temp_sectionAncor = sectionAncor;
		uint32_t temp_sectionIndex = sectionIndex;
		getloc = 0;
		sectionAncor = 0;
		sectionIndex = 0;
		std::cout << "FILE READER DIAGNOSTICS: " << std::endl;

		for (int i = 0; i < sectionSizes.size(); i++)
		{
			std::cout << "SECTION " << i << ": " << std::endl;
			std::cout << "\tsize: " << getSectionSize() << std::endl;
			std::cout << "\toffset: " << getloc << std::endl;
			if (i + 1 != sectionSizes.size())
				toNextSection();
		}
		getloc = temp_getloc;
		sectionAncor = temp_sectionAncor;
		sectionIndex = temp_sectionIndex;
	}
	void seekBoundary32()
	{

		getloc += 32 - getloc % 32;
		
	}
	void readInt8(uint8_t* _Out_ loc)
	{
		//_cpy8(loc, &src[getloc]);
		memcpy(loc, &src[getloc], 1);
		getloc += 1;
	}
	void readInt16(int16_t* _Out_ loc)
	{
		readInt16((uint16_t*)loc);
	}
	void readInt16(uint16_t* _Out_ loc)
	{
		_cpy16(loc, &src[getloc]);
		getloc += 2;
	}
	
	void readInt32(uint32_t* _Out_ loc)
	{

		_cpy32(loc, &src[getloc]);
		getloc += 4;
	}
	void readInt64(uint64_t* _Out_ loc)
	{
		_cpy64(loc, &src[getloc]);
		getloc += 8;
	}
	void readFloat(float* _Out_ loc)
	{
		_cpyFloat(loc, &src[getloc]);
		getloc += 4;
	}

};