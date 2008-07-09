#ifndef __DO_ARC_H__
#define __DO_ARC_H__

#ifdef __cplusplus
	extern "C"
	{
#endif
	
void do_arc(void * bmp, short x, short y,short start,short end, int r, void * d, void (*proc)(void* bmp,int x,int y,void * data));

#ifdef __cplusplus
	}
#endif


#endif /*__DO_ARC_H__*/