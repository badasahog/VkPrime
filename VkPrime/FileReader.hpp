#include <vector>
#include <cstdint>
extern "C" {
	void _cpy8(uint8_t *dest, uint8_t *src);
	void _cpy16(uint16_t *dest, uint8_t *src);
	void _cpy32(uint32_t *dest, uint8_t *src);
	void _cpy64(uint64_t *dest, uint8_t *src);
	void _cpyFloat(float *dest, uint8_t *src);

}
struct FileReader
{
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
		sectionIndex++;
		getloc = sectionAncor;
		for (  int i = 0 ; i < sectionIndex; i++)
		{
			getloc += sectionSizes[i];
		}
	}
	uint32_t getSectionSize()
	{
		return sectionSizes[sectionIndex];
	}
	void seekBoundary32()
	{

		getloc += 32 - getloc % 32;
		
	}
	void readInt8(uint8_t* loc)
	{
		//_cpy8(loc, &src[getloc]);
		memcpy(loc, &src[getloc], 1);
		getloc += 1;
	}
	void readInt16(int16_t* loc)
	{
		readInt16((uint16_t*)loc);
	}
	void readInt16(uint16_t* loc)
	{
		_cpy16(loc, &src[getloc]);
		getloc += 2;
	}
	
	void readInt32(uint32_t* loc)
	{

		_cpy32(loc, &src[getloc]);
		getloc += 4;
	}
	void readInt64(uint64_t* loc)
	{
		_cpy64(loc, &src[getloc]);
		getloc += 8;
	}
	void readFloat(float* loc)
	{
		_cpyFloat(loc, &src[getloc]);
		getloc += 4;
	}

};