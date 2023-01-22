#include<iostream>
#include <vector>
#include <fstream>

namespace Core
{
	namespace Util
	{
        void save(const char* file,std::vector<int8_t> buffer)
        {
            std::ofstream out;
            out.open(file);
            
            for(unsigned i = 0; i < buffer.size(); ++i)
            {
                out << buffer[i];
            }
        }
       // void retriveNsave(
	}
	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator,T value)
	{
		for (unsigned i = 1; i <= sizeof(T); ++i)
		{
			(*buffer)[(*iterator)++] = value >> 8 * (sizeof (T) - i);
		}
	}
}

