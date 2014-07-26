/*
 * File:   common.h
 * Author: Kreyl
 *
 * Created on June 9, 2011, 11:11 PM
 */

#ifndef COMMON_H
#define	COMMON_H
/*
typedef struct {
    uint8_t *Buf;
    uint8_t Length;
    uint8_t CurrentItem;
} Buf8_t;
typedef Buf8_t* Buf8_p;
*/
// Functional types
typedef void (*ftVoid_uint32)(uint32_t iData);

//
// Params:
//     T  - is type of x0, x1, y0 and y1 halves
//     T2 - is type of x, y and half of res
//

typedef struct {
	uint64_t l;
	uint64_t h;

} uint128_t;

typedef struct {
	int64_t l;
	int64_t h;

} int128_t;

__INLINE void mult64_32_x_32(const uint32_t*  x1,const uint32_t*  x2,uint64_t* res) /// !!!!!!!!!!!!!!!!!!! может добавить ограничители на регистры !!!!!!!!!
{
	uint32_t* resL;
	uint32_t* resH;
	resL=(uint32_t*)res;
	resH=resL+1;
	__asm
	(
		"umull	%[resL], %[resH], %[X1], %[X2]"		"\n\t"
		: [resL] "=&r" (*resL), [resH] "=&r" (*resH)
		: [X1] "r"(*x1), [X2] "r" (*x2)
	);
}

__INLINE void smult64_32_x_32(const int32_t* x1,const int32_t* x2,int64_t* res) /// !!!!!!!!!!!!!!!!!!! может добавить ограничители на регистры !!!!!!!!!
{
	int32_t* resL;
	int32_t* resH;
	resL=(int32_t*)res;
	resH=resL+1;
	__asm
	(
		"smull	%[resL], %[resH], %[X1], %[X2]"		"\n\t"
		: [resL] "=&r" (*resL), [resH] "=&r" (*resH)
		: [X1] "r"(*x1), [X2] "r" (*x2)
	);
}

// http://habrahabr.ru/post/121950/
inline void mult128_64_x_64(uint32_t* const x, uint32_t* const y, uint64_t* res)
{
    // Define vars (depending from byte order)

    #define ptrRes ((uint32_t*)res)
	uint64_t &  lowWord = (uint64_t&)(ptrRes[0]);
	uint64_t &  midWord = (uint64_t&)(ptrRes[1]);
	uint64_t & highWord = (uint64_t&)(ptrRes[2]);
	uint32_t  & highByte = (uint32_t &)(ptrRes[3]);
    #undef ptrRes

    const uint32_t & x0 = x[0];
    const uint32_t & x1 = x[1];
    const uint32_t & y0 = y[0];
    const uint32_t & y1 = y[1];

    // Multiply action
    mult64_32_x_32(&x0,&y0,&lowWord);
    mult64_32_x_32(&x1,&y1,&highWord);
    uint64_t m1;
    uint64_t m2;
    mult64_32_x_32(&x0,&y1,&m1);
    mult64_32_x_32(&x1,&y0,&m2);
    midWord += m1;
    if (midWord < m1) highByte++;
    midWord += m2;
    if (midWord < m2) highByte++;
}
inline void sign_mult128_64_x_64(int32_t* const x, int32_t* const y, int64_t* res)
{
    // Define vars (depending from byte order)

    #define ptrRes ((int32_t*)res)
	int64_t &  lowWord = (int64_t&)(ptrRes[0]);
	int64_t &  midWord = (int64_t&)(ptrRes[1]);
	int64_t & highWord = (int64_t&)(ptrRes[2]);
	int32_t  & highByte = (int32_t &)(ptrRes[3]);
    #undef ptrRes

    const int32_t & x0 = x[0];
    const int32_t & x1 = x[1];
    const int32_t & y0 = y[0];
    const int32_t & y1 = y[1];

    // Multiply action
    smult64_32_x_32(&x0,&y0,&lowWord);
    smult64_32_x_32(&x1,&y1,&highWord);
    int64_t m1;
    int64_t m2;
    smult64_32_x_32(&x0,&y1,&m1);
    smult64_32_x_32(&x1,&y0,&m2);
    midWord += m1;
    if (midWord < m1) highByte++;
    midWord += m2;
    if (midWord < m2) highByte++;
}

__INLINE void Shift_128bits_right(uint128_t*  data, uint32_t namber) /// !!!!!!!!!!!!!!!!!!! может добавить ограничители на регистры !!!!!!!!!
{
	uint64_t temp;
	temp=1<<namber;
	temp--;
	temp=temp & (data->h);
	temp=temp<<(64-namber);
	data->h=(data->h)>>namber;
	data->l=(data->l)>>namber;
	data->l+=temp;
}
__INLINE void sign_Shift_128bits_right(int128_t*  data, uint32_t namber) /// !!!!!!!!!!!!!!!!!!! может добавить ограничители на регистры !!!!!!!!!
{
	int64_t temp;
	temp=1<<namber;
	temp--;
	temp=temp & (data->h);
	temp=temp<<(64-namber);
	data->h=(data->h)>>namber;
	data->l=((uint64_t)(data->l))>>namber;
	//data->l=(data->l) & (0xFFFFFFFFFFFFFFFF>>namber)
	data->l=(data->l) | temp;
}

#endif	/* COMMON_H */

