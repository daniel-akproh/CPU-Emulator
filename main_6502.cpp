#include <iostream>

using Word = unsigned short;
using Byte = unsigned char;

using u32 = unsigned int;

struct Mem
{
   static constexpr u32 MAX_MEM = 1024 * 64;
   Byte Data[MAX_MEM];

   void Initialize() 
   {
       for (u32 i = 0; i < MAX_MEM; i++)
       {
           Data[i] = 0;
       }
   }

   // read 1 byte
   Byte operator[](u32 Address) const
   {
       // assert here that Address < MAX_MEM
       return Data[Address];
   }
};

struct CPU
{
    Word PC; // program counter
    Word SP; // stack pointer

    Byte A, X, Y; // registers

    Byte C : 1;  // status flag
    Byte Z : 1;  // status flag
    Byte I : 1;  // status flag
    Byte D : 1;  // status flag
    Byte B : 1;  // status flag
    Byte V : 1;  // status flag
    Byte N : 1;  // status flag

    void Reset(Mem& memory) // reset process. See: https://www.c64-wiki.com/wiki/Reset_(Process)
    {
        // initialization
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = I = D = B = V = N = 0;
    }

    Byte FetchByte(u32 Cycles, Mem& memory) {
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;
    }

    void Execute(u32 Cycles, Mem& memory) {
        while(Cycles > 0) {
            Byte Ins = FetchByte(Cycles, memory);
        }
    }

};

int main()
{
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    cpu.Execute(2, mem);
    std::cout << "Hello World\n";
}