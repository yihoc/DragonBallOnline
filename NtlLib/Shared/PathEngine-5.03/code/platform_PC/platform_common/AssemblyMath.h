//**********************************************************************
//
// Copyright (c) 2000-2005
// PathEngine
// Lyon, France
//
// All Rights Reserved
//
//**********************************************************************

#ifndef ASSEMBLYMATH_INCLUDED
#define ASSEMBLYMATH_INCLUDED

namespace nAssemblyMath
{

inline void add(unsigned long source, unsigned long &dest, unsigned long &carry)
{
    unsigned long _dest=dest;
    unsigned long _carry;
    _asm
    {
        mov eax,_dest
        add eax,source
        mov _dest,eax
        mov _carry,0
        adc _carry,0
    }
    dest=_dest;
    carry=_carry;
}
//inline void add(unsigned long source, unsigned long &dest, unsigned long &carry)
//{
//    unsigned long _carry;
//    _asm
//    {
//        mov ebx,dest
//        mov eax,dword ptr [ebx]
//        add eax,source
//        mov dword ptr[ebx],eax
//        mov _carry,0
//        adc _carry,0
//    }
//    carry=_carry;
//}
inline void adc(unsigned long source, unsigned long &dest, unsigned long &carry)
{
    unsigned long _dest=dest;
    unsigned long _carry=carry;
    _asm
    {
        mov eax,_dest
        add eax,_carry
        mov _carry,0
        adc _carry,0
        add eax,source
        mov _dest,eax
        adc _carry,0
    }
    dest=_dest;
    carry=_carry;
}
inline void sub(unsigned long source, unsigned long &dest, unsigned long &borrow)
{
    unsigned long _dest=dest;
    unsigned long _borrow;
    _asm
    {
        mov eax,_dest
        sub eax,source
        mov _dest,eax
        mov _borrow,0
        sbb _borrow,0
        neg _borrow
    }
    dest=_dest;
    borrow=_borrow;
}
inline void sbb(unsigned long source, unsigned long &dest, unsigned long &borrow)
{
    unsigned long _dest=dest;
    unsigned long _borrow=borrow;
    _asm
    {
        mov eax,_dest
        sub eax,_borrow
        mov _borrow,0
        sbb _borrow,0
        sub eax,source
        mov _dest,eax
        sbb _borrow,0
        neg _borrow
    }
    dest=_dest;
    borrow=_borrow;
}
inline void mul(unsigned long source1, 
                unsigned long source2, 
                unsigned long &dest_high, 
                unsigned long &dest_low)
{
    unsigned long _dest_high,_dest_low;
    _asm
    {
        mov eax,source1
        mul source2
        mov _dest_high,edx
        mov _dest_low,eax
    }
    dest_high=_dest_high;
    dest_low=_dest_low;
}
inline void imul(long source1, 
                long source2, 
                unsigned long &dest_high, 
                unsigned long &dest_low)
{
    unsigned long _dest_high,_dest_low;
    _asm
    {
        mov eax,source1
        imul source2
        mov _dest_high,edx
        mov _dest_low,eax
    }
    dest_high=_dest_high;
    dest_low=_dest_low;
}
inline void div(unsigned long dividend_high, 
                unsigned long dividend_low, 
                unsigned long divisor, 
                unsigned long &quotient,
                unsigned long &remainder
                )
{
    unsigned long _quotient,_remainder;
    _asm
    {
        mov eax,dividend_low
        mov edx,dividend_high
        div divisor
        mov _quotient,eax
        mov _remainder,edx
    }
    quotient=_quotient;
    remainder=_remainder;
}

inline int bitCount(unsigned long input, unsigned long& output)
{
	int returnvalue;
	__asm
	{
		mov		eax, [input]
		mov		ebx, 0x0000ffff

		mov		esi, 0			// Bit counter
		cmp		ebx, eax

		sbb		edi, edi		// if upper bits set, edi = 0xffffffff
		mov		edx, 16

		mov		ecx, 0x00ff00ff
		and		edx, edi

		xor		ebx, edi
		add		esi, edx

		and		eax, ebx		// AND with input
		and		ecx, ebx		// AND with NEXT comaprison mask

		cmp		ecx, eax

		sbb		edi, edi
		mov		edx, 8

		and		edx, edi
		and		edi, ebx		// AND with previous mask

		mov		ebx, 0x0f0f0f0f
		xor		ecx, edi		// flip comparison mask if(val > comparison)

		and		eax, ecx		// AND with input
		and		ebx, ecx		// AND with next mask

		add		esi, edx
		cmp		ebx, eax

		sbb		edi, edi
		mov		edx, 4
		
		and		edx, edi
		and		edi, ecx		// AND with previous mask

		mov		ecx, 0x33333333
		xor		ebx, edi		// flip mask if val>compare

		and		eax, ebx		// AND with input
		and		ecx, ebx		// AND with next mask

		add		esi, edx
		cmp		ecx, eax

		sbb		edi, edi
		mov		edx, 2

		and		edx, edi
		and		edi, ebx

		mov		ebx, 0x55555555
		xor		ecx, edi

		and		eax, ecx
		and		ebx, ecx

		add		esi, edx
		cmp		ebx, eax

		sbb		edi, edi
		mov		edx, 1

		and		edx, edi
		and		edi, ecx

		xor		ebx, edi
		mov		ecx, [output]

		add		esi, edx
		and		eax, ebx

		mov		[returnvalue], esi
		mov		[ecx], eax
	}
	return returnvalue;
}

inline int indexForTopBit(unsigned long input)
{
	unsigned long dummy;
	return bitCount(input,dummy);
/*
	int returnvalue;
	__asm
	{
		mov		eax, [input]
		mov		ebx, 0x0000ffff

		mov		esi, 0			// Bit counter
		cmp		ebx, eax

		sbb		edi, edi		// if upper bits set, edi = 0xffffffff
		mov		edx, 16

		mov		ecx, 0x00ff00ff
		and		edx, edi

		xor		ebx, edi
		add		esi, edx

		and		eax, ebx		// AND with input
		and		ecx, ebx		// AND with NEXT comaprison mask

		cmp		ecx, eax

		sbb		edi, edi
		mov		edx, 8

		and		edx, edi
		and		edi, ebx		// AND with previous mask

		mov		ebx, 0x0f0f0f0f
		xor		ecx, edi		// flip comparison mask if(val > comparison)

		and		eax, ecx		// AND with input
		and		ebx, ecx		// AND with next mask

		add		esi, edx
		cmp		ebx, eax

		sbb		edi, edi
		mov		edx, 4
		
		and		edx, edi
		and		edi, ecx		// AND with previous mask

		mov		ecx, 0x33333333
		xor		ebx, edi		// flip mask if val>compare

		and		eax, ebx		// AND with input
		and		ecx, ebx		// AND with next mask

		add		esi, edx
		cmp		ecx, eax

		sbb		edi, edi
		mov		edx, 2

		and		edx, edi
		and		edi, ebx

		mov		ebx, 0x55555555
		xor		ecx, edi

		and		eax, ecx
		and		ebx, ecx

		add		esi, edx
//		cmp		ebx, eax

//		sbb		edi, edi
		mov		edx, 1

		and		edx, edi
//		and		edi, ecx

//		xor		ebx, edi
//		mov		ecx, [output]

		add		esi, edx
//		and		eax, ebx

		mov		[returnvalue], esi
//		mov		[ecx], eax
	}
	return returnvalue;
*/
}

}

#endif
