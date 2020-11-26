
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
	void init(uint8_t* input)
	{
		src = input;
		getloc = 0;
	}
	void seekBoundary32()
	{

		getloc += 32 - getloc % 32;
	}
	void readInt8(uint8_t* loc)
	{
		_cpy8(loc, &src[getloc]);
		getloc += 1;
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