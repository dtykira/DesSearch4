#include "Types.h"
#include "DesFunc.h"
#include "LookUpTables.h"

u8 ETableLookUp[4][256][8] = { 0 };
u32 PTableLookUp[4][256] = { 0 };

void set(u8* y,const u8* x){
	for(int i=0;i<8;i++){
		y[i]=x[i];
	}
}

void GenETableLookUp(){
	u32 x=0;
	u8 y[8]={0};
	for(int i=0;i<4;i++){
		for(u32 j=0;j<256;j++){
			x=j<<(8*i);
			Expansion(y,x);
			set(ETableLookUp[i][j],y);
		}
	}
}

void ExpansionTL(u8* output, u32 input){
	u32 x=input;
	u8 y[4][8]={0};
	for(int i=0;i<4;i++){
		set(y[i],ETableLookUp[i][(x>>(8*i))&0xff]);
	}
	for(int i=0;i<8;i++){
		output[i]=y[1][i]|y[2][i]|y[3][i]|y[4][i];
	}
}

void GenPTableLookUp(){
	u32 x=0,y=0;
	for(int i=0;i<4;i++){
		for(u32 j=0;j<256;j++){
			x=j<<(8*i);
			Permutation(&y,x);
			PTableLookUp[i][j]=y;
		}
	}
}

void PermutationTL(u32* output, u32 input){
	u32 x=input,y[4]={0};
	for(int i=0;i<4;i++){
		y[i]=PTableLookUp[i][(x>>(8*i))&0xff];
	}
	*output=y[1]|y[2]|y[3]|y[4];
}