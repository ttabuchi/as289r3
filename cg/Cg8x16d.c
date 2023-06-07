/*******************************************
	ANK 8x16D CARACTER GENERATOR
	32byte * 160char. = 5120byte
	type is int
*******************************************/
const unsigned short cg8x16d[] = 
{
//	0x0123,0x4567,0x89ab,0xcdef,0x0123,0x4567,0x89ab,0xcdef,		/* SP	*/
//	0x0123,0x4567,0x89ab,0xcdef,0x0123,0x4567,0x89ab,0xcdef,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,		/* SP	*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,		/* !	*/
	0x1800,0x1800,0x1800,0x1800,0x0000,0x0000,0x1800,0x1800,
	0xd800,0xd800,0x4800,0x9000,0x0000,0x0000,0x0000,0x0000,		/* "	*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x6600,0x6600,0x6700,0x6f00,0xfe00,0xf600,0x6600,0x6600,		/* #	*/
	0x6600,0x6700,0x6f00,0xfe00,0xf600,0x6600,0x6600,0x6600,
	0x1800,0x7e00,0xff00,0xdb00,0xd800,0xd800,0xf800,0x7c00,		/* $	*/
	0x3e00,0x1f00,0x1b00,0x1b00,0xdb00,0xff00,0x7e00,0x1800,
	0x7300,0xfb00,0xdb00,0xfe00,0x7600,0x0c00,0x0c00,0x1800,		/* %	*/
	0x1800,0x3000,0x3000,0x6e00,0x7f00,0xdb00,0xdf00,0xce00,
	0x3800,0x7c00,0x6c00,0x6c00,0x7c00,0x3800,0x3800,0x7b00,		/* &	*/
	0x6f00,0xef00,0xcf00,0xc600,0xc600,0xef00,0x7f00,0x3b00,
	0x3000,0x7800,0x7800,0x3800,0x1800,0x3000,0x0000,0x0000,		/* '	*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0c00,0x1c00,0x1800,0x3800,0x3000,0x3000,0x3000,0x3000,		/* (	*/
	0x3000,0x3000,0x3000,0x3000,0x3800,0x1800,0x1c00,0x0c00,
	0x3000,0x3800,0x1800,0x1c00,0x0c00,0x0c00,0x0c00,0x0c00,		/* )	*/
	0x0c00,0x0c00,0x0c00,0x0c00,0x1c00,0x1800,0x3800,0x3000,
	0x0000,0x0000,0x0000,0x1800,0xdb00,0xff00,0x7e00,0x3c00,		/* *	*/
	0x3c00,0x7e00,0xff00,0xdb00,0x1800,0x0000,0x0000,0x0000,
	0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0xff00,		/* +	*/
	0xff00,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,		/* ,	*/
	0x0000,0x0000,0x1800,0x3c00,0x3c00,0x1c00,0x0c00,0x1800,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x7e00,		/* -	*/
	0x7e00,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,		/* .	*/
	0x0000,0x0000,0x0000,0x1800,0x3c00,0x3c00,0x1800,0x0000,
	0x0300,0x0300,0x0300,0x0600,0x0600,0x0c00,0x0c00,0x1800,		/* /	*/
	0x1800,0x3000,0x3000,0x6000,0x6000,0xc000,0xc000,0xc000,
	0x3c00,0x7e00,0xe700,0xc300,0xc300,0xc300,0xc300,0xc300,		/* 0	*/
	0xc300,0xc300,0xc300,0xc300,0xc300,0xe700,0x7e00,0x3c00,
	0x0c00,0x1c00,0x3c00,0x7c00,0x6c00,0x0c00,0x0c00,0x0c00,		/* 1	*/
	0x0c00,0x0c00,0x0c00,0x0c00,0x0c00,0x0c00,0x0c00,0x0c00,
	0x3c00,0x7e00,0xe700,0xc300,0x0300,0x0700,0x0600,0x0e00,		/* 2	*/
	0x1c00,0x3800,0x7000,0x6000,0xe000,0xc000,0xff00,0xff00,
	0x3c00,0x7e00,0xe700,0xc300,0x0300,0x0300,0x0700,0x3e00,		/* 3	*/
	0x3e00,0x0700,0x0300,0x0300,0xc300,0xe700,0x7e00,0x3c00,
	0x0e00,0x0e00,0x1e00,0x1e00,0x3e00,0x3600,0x7600,0x6600,		/* 4	*/
	0xe600,0xc600,0xc600,0xff00,0xff00,0x0600,0x0600,0x0600,
	0x3f00,0x3f00,0x7000,0x6000,0x6000,0xc000,0xfc00,0xfe00,		/* 5	*/
	0xc700,0x0300,0x0300,0x0300,0xc300,0xe700,0x7e00,0x3c00,
	0x0c00,0x1c00,0x1800,0x3800,0x3000,0x7000,0x6000,0xfc00,		/* 6	*/
	0xfe00,0xe700,0xc300,0xc300,0xc300,0xe700,0x7e00,0x3c00,
	0xff00,0xff00,0x0300,0x0700,0x0600,0x0e00,0x0c00,0x0c00,		/* 7	*/
	0x1c00,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,
	0x3c00,0x7e00,0xe700,0xc300,0xc300,0xe700,0x7e00,0x3c00,		/* 8	*/
	0x7e00,0xe700,0xc300,0xc300,0xc300,0xe700,0x7e00,0x3c00,
	0x3c00,0x7e00,0xe700,0xc300,0xc300,0xc300,0xe700,0x7f00,		/* 9	*/
	0x3f00,0x0600,0x0e00,0x0c00,0x1c00,0x1800,0x3800,0x3000,
	0x0000,0x0000,0x1800,0x3c00,0x3c00,0x1800,0x0000,0x0000,		/* :	*/
	0x0000,0x1800,0x3c00,0x3c00,0x1800,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x1800,0x3c00,0x3c00,0x1800,0x0000,0x0000,		/* ;	*/
	0x0000,0x1800,0x3c00,0x1c00,0x0c00,0x1800,0x0000,0x0000,
	0x0000,0x0300,0x0700,0x0e00,0x1c00,0x3800,0x7000,0xe000,		/* <	*/
	0xe000,0x7000,0x3800,0x1c00,0x0e00,0x0700,0x0300,0x0000,
	0x0000,0x0000,0x0000,0x0000,0xff00,0xff00,0x0000,0x0000,		/* =	*/
	0x0000,0xff00,0xff00,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0xc000,0xe000,0x7000,0x3800,0x1c00,0x0e00,0x0700,		/* >	*/
	0x0700,0x0e00,0x1c00,0x3800,0x7000,0xe000,0xc000,0x0000,
	0x3c00,0x7e00,0xe700,0xc300,0xc300,0x0700,0x0e00,0x1c00,		/* ?	*/
	0x1800,0x1800,0x1800,0x1800,0x0000,0x0000,0x1800,0x1800,
	0x3c00,0x7e00,0xe700,0xc300,0xc300,0x0300,0x3b00,0x7b00,		/* @	*/
	0xfb00,0xdb00,0xdb00,0xdb00,0xdf00,0xff00,0xf700,0x6600,
	0x1800,0x1800,0x1800,0x3c00,0x3c00,0x3c00,0x7e00,0x6600,		/* A	*/
	0x6600,0xe700,0xc300,0xff00,0xff00,0xc300,0xc300,0xc300,
	0xfc00,0xfe00,0xc700,0xc300,0xc300,0xc700,0xce00,0xfc00,		/* B	*/
	0xfe00,0xc700,0xc300,0xc300,0xc300,0xc700,0xfe00,0xfc00,
	0x3c00,0x7e00,0xe700,0xc300,0xc000,0xc000,0xc000,0xc000,		/* C	*/
	0xc000,0xc000,0xc000,0xc000,0xc300,0xe700,0x7e00,0x3c00,
	0xfc00,0xfe00,0xc700,0xc300,0xc300,0xc300,0xc300,0xc300,		/* D	*/
	0xc300,0xc300,0xc300,0xc300,0xc300,0xc700,0xfe00,0xfc00,
	0xff00,0xff00,0xc000,0xc000,0xc000,0xc000,0xc000,0xfc00,		/* E	*/
	0xfc00,0xc000,0xc000,0xc000,0xc000,0xc000,0xff00,0xff00,
	0xff00,0xff00,0xc000,0xc000,0xc000,0xc000,0xc000,0xfc00,		/* F	*/
	0xfc00,0xc000,0xc000,0xc000,0xc000,0xc000,0xc000,0xc000,
	0x3c00,0x7e00,0xe700,0xc300,0xc000,0xc000,0xc000,0xcf00,		/* G	*/
	0xcf00,0xc300,0xc300,0xc300,0xc700,0xef00,0x7f00,0x3b00,
	0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,0xff00,		/* H 	*/
	0xff00,0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,
	0x3c00,0x3c00,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,		/* I	*/
	0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x3c00,0x3c00,
	0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,		/* J	*/
	0x0300,0x0300,0x0300,0x0300,0xc300,0xe700,0x7e00,0x3c00,
	0xc300,0xc700,0xc600,0xce00,0xcc00,0xdc00,0xd800,0xf800,		/* K	*/
	0xf800,0xec00,0xcc00,0xce00,0xc600,0xc700,0xc300,0xc300,
	0xc000,0xc000,0xc000,0xc000,0xc000,0xc000,0xc000,0xc000,		/* L	*/
	0xc000,0xc000,0xc000,0xc000,0xc000,0xc000,0xff00,0xff00,
	0xc300,0xc300,0xc300,0xe700,0xe700,0xe700,0xe700,0xff00,		/* M	*/
	0xff00,0xff00,0xdb00,0xdb00,0xdb00,0xdb00,0xc300,0xc300,
	0xc300,0xc300,0xe300,0xe300,0xf300,0xf300,0xf300,0xdb00,		/* N	*/
	0xdb00,0xcf00,0xcf00,0xcf00,0xc700,0xc700,0xc300,0xc300,
	0x3c00,0x7e00,0x6600,0x6600,0xe700,0xc300,0xc300,0xc300,		/* O	*/
	0xc300,0xc300,0xc300,0xe700,0x6600,0x6600,0x7e00,0x3c00,
	0xfc00,0xfe00,0xc700,0xc300,0xc300,0xc300,0xc700,0xfe00,		/* P	*/
	0xfc00,0xc000,0xc000,0xc000,0xc000,0xc000,0xc000,0xc000,
	0x3c00,0x7e00,0xe700,0xc300,0xc300,0xc300,0xc300,0xc300,		/* Q	*/
	0xc300,0xdb00,0xff00,0xe700,0xc600,0xef00,0x7f00,0x3b00,
	0xfc00,0xfe00,0xc700,0xc300,0xc300,0xc300,0xc700,0xfe00,		/* R	*/
	0xfc00,0xdc00,0xcc00,0xce00,0xc600,0xc700,0xc300,0xc300,
	0x3c00,0x7e00,0xe700,0xc300,0xc000,0xe000,0x7000,0x3800,		/* S	*/
	0x1c00,0x0e00,0x0700,0x0300,0xc300,0xe700,0x7e00,0x3c00,
	0xff00,0xff00,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,		/* T	*/
	0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,
	0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,		/* U	*/
	0xc300,0xc300,0xc300,0xc300,0xc300,0xe700,0x7e00,0x3c00,
	0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,0xe700,		/* V	*/
	0x6600,0x6600,0x6600,0x7e00,0x3c00,0x3c00,0x1800,0x1800,
	0xc300,0xc300,0xc300,0xdb00,0xdb00,0xdb00,0xdb00,0xdb00,		/* W	*/
	0xdb00,0xff00,0xff00,0x7e00,0x6600,0x6600,0x6600,0x4200,
	0xc300,0xc300,0xe700,0x6600,0x7e00,0x3c00,0x3c00,0x1800,		/* X	*/
	0x1800,0x3c00,0x3c00,0x7e00,0x6600,0xe700,0xc300,0xc300,
	0xc300,0xc300,0xc300,0xe700,0x6600,0x6600,0x7e00,0x3c00,		/* Y	*/
	0x3c00,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,
	0xff00,0xff00,0x0700,0x0600,0x0e00,0x0c00,0x1c00,0x1800,		/* Z	*/
	0x1800,0x3800,0x3000,0x7000,0x6000,0xe000,0xff00,0xff00,
	0x3c00,0x3c00,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,		/* [	*/
	0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3c00,0x3c00,
	0xc300,0xc300,0xe700,0x6600,0x7e00,0x3c00,0xff00,0xff00,		/* \	*/
	0x1800,0x1800,0xff00,0xff00,0x1800,0x1800,0x1800,0x1800,
	0x3c00,0x3c00,0x0c00,0x0c00,0x0c00,0x0c00,0x0c00,0x0c00,		/* ]	*/
	0x0c00,0x0c00,0x0c00,0x0c00,0x0c00,0x0c00,0x3c00,0x3c00,
	0x1800,0x1800,0x3c00,0x3c00,0x6600,0x6600,0xc300,0xc300,		/* ^	*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,		/* _	*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xff00,0xff00,
	0x0c00,0x1800,0x1c00,0x1e00,0x0c00,0x0000,0x0000,0x0000,		/* '	*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x3800,0x7c00,0x6e00,0x0600,0x0e00,		/* a	*/
	0x3e00,0x7600,0xe600,0xc600,0xce00,0xfe00,0xf700,0x6300,
	0xc000,0xc000,0xc000,0xc000,0xc000,0xdc00,0xfe00,0xf700,		/* b	*/
	0xe300,0xc300,0xc300,0xc300,0xe300,0xf700,0xfe00,0xdc00,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x3c00,0x7e00,0xe700,		/* c	*/
	0xc300,0xc000,0xc000,0xc000,0xc300,0xe700,0x7e00,0x3c00,
	0x0300,0x0300,0x0300,0x0300,0x0300,0x3b00,0x7f00,0xef00,		/* d	*/
	0xc700,0xc300,0xc300,0xc300,0xc700,0xef00,0x7f00,0x3b00,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x3c00,0x7e00,0xe700,		/* e	*/
	0xc300,0xff00,0xff00,0xc000,0xc000,0xe300,0x7f00,0x3e00,
	0x0e00,0x1f00,0x3b00,0x3000,0x3000,0x3000,0xfe00,0xfe00,		/* f	*/
	0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,
	0x0000,0x0000,0x0000,0x0000,0x3b00,0x7f00,0xe700,0xc300,		/* g	*/
	0xc300,0xe700,0x7f00,0x3b00,0x0300,0xc700,0xfe00,0x7c00,
	0xc000,0xc000,0xc000,0xc000,0xc000,0xc000,0xdc00,0xfe00,		/* h	*/
	0xe700,0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,
	0x0000,0x0000,0x0000,0x1800,0x1800,0x0000,0x0000,0x1800,		/* i	*/
	0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,
	0x0000,0x0000,0x0000,0x0300,0x0300,0x0000,0x0000,0x0300,		/* j	*/
	0x0300,0x0300,0x0300,0x0300,0xc300,0xe700,0x7e00,0x3c00,
	0xc000,0xc000,0xc000,0xc000,0xc000,0xc300,0xc700,0xce00,		/* k	*/
	0xdc00,0xfc00,0xfc00,0xee00,0xc600,0xc700,0xc300,0xc300,
	0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,		/* l	*/
	0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,
	0x0000,0x0000,0x0000,0x0000,0x0000,0xd400,0xfe00,0xff00,		/* m	*/
	0xdb00,0xdb00,0xdb00,0xdb00,0xdb00,0xdb00,0xdb00,0xdb00,
	0x0000,0x0000,0x0000,0x0000,0x0000,0xdc00,0xfe00,0xe700,		/* n	*/
	0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,0xc300,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x3c00,0x7e00,0x6600,		/* o	*/
	0xe700,0xc300,0xc300,0xc300,0xe700,0x6600,0x7e00,0x3c00,
	0x0000,0x0000,0x0000,0x0000,0x0000,0xdc00,0xfe00,0xe700,		/* p	*/
	0xc300,0xc300,0xc300,0xe700,0xfe00,0xdc00,0xc000,0xc000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x3b00,0x7f00,0xe700,		/* q	*/
	0xc300,0xc300,0xc300,0xe700,0x7f00,0x3b00,0x0300,0x0300,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x6700,0x6f00,0x7c00,		/* r	*/
	0x7800,0x7000,0x6000,0x6000,0x6000,0x6000,0x6000,0x6000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x3e00,0x7f00,0xe300,		/* s	*/
	0xc000,0xf000,0x7e00,0x0f00,0x0300,0xc700,0xfe00,0x7c00,
	0x3000,0x3000,0x3000,0x3000,0x3000,0xfe00,0xfe00,0x3000,		/* t	*/
	0x3000,0x3000,0x3000,0x3000,0x3000,0x3800,0x1e00,0x0e00,
	0x0000,0x0000,0x0000,0x0000,0x0000,0xc300,0xc300,0xc300,		/* u	*/
	0xc300,0xc300,0xc300,0xc300,0xc300,0xe700,0x7f00,0x3b00,
	0x0000,0x0000,0x0000,0x0000,0x0000,0xc300,0xc300,0xc300,		/* v	*/
	0xc300,0xc300,0xe700,0x6600,0x7e00,0x3c00,0x3c00,0x1800,
	0x0000,0x0000,0x0000,0x0000,0x0000,0xc300,0xc300,0xdb00,		/* w	*/
	0xdb00,0xdb00,0xff00,0xff00,0xe700,0x6600,0x6600,0x4200,
	0x0000,0x0000,0x0000,0x0000,0x0000,0xc300,0xc300,0xe700,		/* x	*/
	0x7e00,0x3c00,0x1800,0x3c00,0x7e00,0xe700,0xc300,0xc300,
	0x0000,0x0000,0x0000,0x0000,0x0000,0xc300,0xc300,0xe300,		/* y	*/
	0x6700,0x7600,0x3e00,0x1c00,0x1c00,0x3800,0xf000,0xe000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0xff00,0xff00,0x0700,		/* z	*/
	0x0e00,0x1c00,0x1800,0x3800,0x7000,0xe000,0xff00,0xff00,
	0x0e00,0x1e00,0x1800,0x3000,0x3000,0x3000,0x3000,0x6000,		/* {	*/
	0x6000,0x3000,0x3000,0x3000,0x3000,0x1800,0x1e00,0x0e00,
	0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,		/* |	*/
	0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,
	0x7000,0x7800,0x1800,0x0c00,0x0c00,0x0c00,0x0c00,0x0600,		/* }	*/
	0x0600,0x0c00,0x0c00,0x0c00,0x0c00,0x1800,0x7800,0x7000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x7000,0xf800,		/* �о�	*/
	0xdb00,0x1f00,0x0e00,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,		/*		*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,		/* SP	*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,		/* �	*/
	0x0000,0x0000,0x7800,0xfc00,0xcc00,0xcc00,0xfc00,0x7800,
	0x7c00,0x7c00,0x6000,0x6000,0x6000,0x6000,0x6000,0x6000,		/* �	*/
	0x6000,0x6000,0x6000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0600,0x0600,0x0600,		/* �	*/
	0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x3e00,0x3e00,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,		/* �	*/
	0x0000,0x0000,0x0000,0x8000,0x4000,0x6000,0x3000,0x3000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x1800,0x3c00,		/* �	*/
	0x3c00,0x1800,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0xff00,0xff00,0x0300,0x0300,0x0700,0xfe00,0xfe00,		/* �	*/
	0x0e00,0x0c00,0x0c00,0x1c00,0x1800,0x3800,0xf000,0xe000,
	0x0000,0x0000,0x0000,0xff00,0xff00,0x0700,0x3600,0x3e00,		/* �	*/
	0x3c00,0x3000,0x3000,0x3000,0x7000,0x6000,0xe000,0xc000,
	0x0000,0x0000,0x0000,0x0300,0x0700,0x0e00,0x1c00,0x3800,		/* �	*/
	0x7800,0xf800,0xd800,0x1800,0x1800,0x1800,0x1800,0x1800,
	0x0000,0x0000,0x1800,0x1800,0xff00,0xff00,0xc300,0xc300,		/* �	*/
	0xc700,0xc600,0x0600,0x0e00,0x0c00,0x1c00,0x3800,0x3000,
	0x0000,0x0000,0x0000,0x0000,0x7e00,0x7e00,0x1800,0x1800,		/* �	*/
	0x1800,0x1800,0x1800,0x1800,0x1800,0xff00,0xff00,0x0000,
	0x0000,0x0000,0x0c00,0x0c00,0x0c00,0xff00,0xff00,0x1c00,		/* �	*/
	0x3c00,0x7c00,0x6c00,0xec00,0xcc00,0xcc00,0x0c00,0x0c00,
	0x0000,0x0000,0x6000,0x6000,0x6700,0x7f00,0xfb00,0xf300,		/* �	*/
	0x3600,0x3600,0x3000,0x3000,0x1800,0x1800,0x1800,0x1800,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x7c00,0x7c00,0x0c00,		/* �	*/
	0x0c00,0x0c00,0x0c00,0x0c00,0x0c00,0xff00,0xff00,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x7e00,0x7e00,0x0600,		/* �	*/
	0x0600,0x7e00,0x7e00,0x0600,0x0600,0x0600,0x7e00,0x7e00,
	0x0000,0x0000,0x0000,0x0000,0x0000,0xdb00,0xdb00,0xdb00,		/* �	*/
	0xdb00,0x0300,0x0700,0x0600,0x0e00,0x0c00,0x1800,0x3000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xc000,0x7e00,		/* �	*/
	0x3f00,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0xff00,0xff00,0x0300,0x3700,0x3600,0x3e00,0x3c00,		/* �	*/
	0x3000,0x3000,0x3000,0x7000,0x6000,0x6000,0xe000,0xc000,
	0x0300,0x0300,0x0700,0x0600,0x0e00,0x1c00,0x3800,0x7800,		/* �	*/
	0xf800,0xd800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,
	0x1800,0x1800,0x1800,0xff00,0xff00,0xc300,0xc300,0xc300,		/* �	*/
	0xc700,0x0600,0x0600,0x0e00,0x0c00,0x1c00,0x3800,0x3000,
	0x0000,0x0000,0x7e00,0x7e00,0x1800,0x1800,0x1800,0x1800,		/* �	*/
	0x1800,0x1800,0x1800,0x1800,0x1800,0xff00,0xff00,0x0000,
	0x0c00,0x0c00,0x0c00,0xff00,0xff00,0x1c00,0x3c00,0x3c00,		/* �	*/
	0x7c00,0x6c00,0x6c00,0xec00,0xcc00,0xcc00,0x0c00,0x0c00,
	0x1800,0x1800,0x1800,0xff00,0xff00,0x1b00,0x1b00,0x3b00,		/* �	*/
	0x3300,0x3300,0x3300,0x7300,0x6300,0xe700,0xce00,0x0c00,
	0x3000,0x3000,0x3600,0x3e00,0xf800,0xd800,0x1800,0x1b00,		/* �	*/
	0x3f00,0xfc00,0xd800,0x1c00,0x0c00,0x0c00,0x0c00,0x0c00,
	0x1800,0x1800,0x3f00,0x3f00,0x7300,0x6300,0xe300,0xc300,		/* �	*/
	0x0300,0x0700,0x0600,0x0e00,0x0c00,0x1c00,0x3800,0x3000,
	0x3000,0x3000,0x3000,0x3f00,0x7f00,0x6c00,0xec00,0xcc00,		/* �	*/
	0x0c00,0x0c00,0x1c00,0x1800,0x1800,0x3800,0x7000,0x6000,
	0x0000,0x0000,0xfe00,0xfe00,0x0600,0x0600,0x0600,0x0600,		/* �	*/
	0x0600,0x0600,0x0600,0x0600,0x0600,0xfe00,0xfe00,0x0000,
	0x6600,0x6600,0x6600,0x6600,0xff00,0xff00,0x6600,0x6600,		/* �	*/
	0x6600,0x6600,0x0e00,0x0c00,0x0c00,0x1c00,0x3800,0x3000,
	0x0000,0x6000,0x7000,0x3000,0x0000,0xc300,0xe300,0x6300,		/* �	*/
	0x0300,0x0300,0x0700,0x0600,0x0e00,0x1c00,0xf800,0xe000,
	0x0000,0xff00,0xff00,0x0300,0x0300,0x0600,0x0600,0x0c00,		/* �	*/
	0x0c00,0x1c00,0x1e00,0x3600,0x3600,0x6300,0x6300,0xc300,
	0x6000,0x6000,0x6000,0x6300,0x6f00,0xff00,0xf300,0x6300,		/* �	*/
	0x6600,0x6000,0x6000,0x6000,0x6000,0x6000,0x7e00,0x3e00,
	0x0000,0x0300,0xc300,0xc300,0xc300,0xe300,0x6300,0x0300,		/* �	*/
	0x0700,0x0600,0x0600,0x0e00,0x0c00,0x1c00,0x3800,0x3000,
	0x1800,0x1800,0x3f00,0x3f00,0x7300,0x6300,0xe300,0xdb00,		/* �	*/
	0x1e00,0x0e00,0x0e00,0x0c00,0x1c00,0x3800,0x7000,0x6000,
	0x0600,0x0e00,0x7c00,0x7800,0x0c00,0x0c00,0xff00,0xff00,		/* �	*/
	0x0c00,0x0c00,0x0c00,0x1c00,0x1800,0x3800,0x7000,0x6000,
	0x0000,0x1b00,0xdb00,0xdb00,0xdb00,0xdb00,0xc300,0x0700,		/* �	*/
	0x0600,0x0600,0x0600,0x0e00,0x0c00,0x1c00,0x3800,0x3000,
	0x0000,0x7e00,0x7e00,0x0000,0x0000,0xff00,0xff00,0x1800,		/* �	*/
	0x1800,0x1800,0x1800,0x3800,0x3000,0x7000,0xe000,0xc000,
	0x6000,0x6000,0x6000,0x6000,0x6000,0x7000,0x7800,0x7c00,		/* �	*/
	0x6e00,0x6600,0x6600,0x6000,0x6000,0x6000,0x6000,0x6000,
	0x0c00,0x0c00,0x0c00,0x0c00,0xff00,0xff00,0x0c00,0x0c00,		/* �	*/
	0x0c00,0x1c00,0x1800,0x1800,0x3800,0x7000,0xe000,0xc000,
	0x0000,0x0000,0x7e00,0x7e00,0x0000,0x0000,0x0000,0x0000,		/* �	*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0xff00,0xff00,0x0000,
	0x0000,0xff00,0xff00,0x0300,0x0300,0x6300,0x7600,0x3600,		/* �	*/
	0x3e00,0x1c00,0x1c00,0x1e00,0x3f00,0x7300,0xe000,0xc000,
	0x1800,0x1800,0xff00,0xff00,0x0300,0x0700,0x0e00,0x1c00,		/* �	*/
	0x3e00,0x7e00,0xfb00,0xdb00,0x1800,0x1800,0x1800,0x1800,
	0x0000,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,		/* �	*/
	0x0600,0x0e00,0x0c00,0x1c00,0x3800,0x7000,0x6000,0x0000,
	0x0000,0x0c00,0x0e00,0x0600,0x0600,0x6600,0x6700,0x6300,		/* �	*/
	0x6300,0x6300,0x6300,0x6300,0x6300,0xc300,0xc300,0x0300,
	0x0000,0xc000,0xc000,0xc600,0xce00,0xdc00,0xf800,0xf000,		/* �	*/
	0xc000,0xc000,0xc000,0xc000,0xc000,0xe000,0x7f00,0x3f00,
	0x0000,0x0000,0xff00,0xff00,0x0300,0x0300,0x0300,0x0700,		/* �	*/
	0x0600,0x0600,0x0e00,0x0c00,0x1c00,0x3800,0x7000,0x6000,
	0x0000,0x0000,0x3800,0x3800,0x7c00,0x6c00,0xe600,0xc600,		/* �	*/
	0xc600,0xc700,0x0300,0x0300,0x0300,0x0300,0x0300,0x0000,
	0x1800,0x1800,0x1800,0xff00,0xff00,0x1800,0x1800,0x1800,		/* �	*/
	0xdb00,0xdb00,0xdb00,0xdb00,0xdb00,0xdb00,0x1800,0x1800,
	0x0000,0x0000,0xff00,0xff00,0x0300,0x0300,0x0700,0x0600,		/* �	*/
	0x6e00,0x7c00,0x7800,0x3800,0x1c00,0x0e00,0x0600,0x0000,
	0x0000,0x6000,0x7000,0x3800,0x1c00,0x0c00,0x6000,0x7000,		/* �	*/
	0x3800,0x1c00,0xcc00,0xe000,0x7000,0x3800,0x1e00,0x0600,
	0x1800,0x1800,0x1800,0x3800,0x3000,0x3000,0x3000,0x3000,		/* �	*/
	0x7000,0x6600,0x6700,0x6300,0xef00,0xff00,0xf300,0x0300,
	0x0300,0x0300,0x0300,0x0700,0x6600,0x7600,0x3e00,0x1c00,		/* �	*/
	0x0c00,0x1e00,0x1f00,0x3b00,0x3000,0x7000,0xe000,0xc000,
	0x0000,0x7e00,0x7e00,0x3000,0x3000,0x3000,0xff00,0xff00,		/* �	*/
	0x3000,0x3000,0x3000,0x3000,0x3000,0x3800,0x1e00,0x0e00,
	0x6000,0x6000,0x6300,0x6f00,0x7f00,0xfb00,0xf300,0x3700,		/* �	*/
	0x3600,0x3000,0x3000,0x3800,0x1800,0x1800,0x1800,0x1800,
	0x0000,0x0000,0x7e00,0x7e00,0x0600,0x0600,0x0600,0x0e00,		/* �	*/
	0x0c00,0x0c00,0x0c00,0x0c00,0x0c00,0xff00,0xff00,0x0000,
	0x0000,0x7f00,0x7f00,0x0300,0x0300,0x0300,0x0300,0x7f00,		/* �	*/
	0x7f00,0x0300,0x0300,0x0300,0x0300,0x7f00,0x7f00,0x0000,
	0x7e00,0x7e00,0x0000,0x0000,0x0000,0xff00,0xff00,0x0300,		/* �	*/
	0x0300,0x0700,0x0600,0x0e00,0x0c00,0x1c00,0x3800,0x3000,
	0x0000,0xc600,0xc600,0xc600,0xc600,0xc600,0xc600,0xc600,		/* �	*/
	0xc600,0x0600,0x0e00,0x0c00,0x0c00,0x1c00,0x3800,0x3000,
	0x1800,0x1800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,		/* �	*/
	0xd800,0xdb00,0xdb00,0xdb00,0xde00,0x1e00,0x1c00,0x1c00,
	0x6000,0x6000,0x6000,0x6000,0x6000,0x6000,0x6000,0x6300,		/* �	*/
	0x6300,0x6600,0x6600,0x6c00,0x6c00,0x7800,0x7800,0x7000,
	0x0000,0xff00,0xff00,0xc300,0xc300,0xc300,0xc300,0xc300,		/* �	*/
	0xc300,0xc300,0xc300,0xc300,0xc300,0xff00,0xff00,0x0000,
	0x0000,0xff00,0xff00,0xc300,0xc300,0xc300,0xc300,0x0300,		/* �	*/
	0x0700,0x0600,0x0600,0x0e00,0x0c00,0x1c00,0x3800,0x3000,
	0x0000,0x0000,0xc000,0xe000,0x6000,0x0300,0x0300,0x0300,		/* �	*/
	0x0300,0x0300,0x0700,0x0600,0x0e00,0x1c00,0xf800,0xe000,
	0x1800,0x1c00,0xcc00,0xec00,0x6000,0x6000,0x0000,0x0000,		/* �	*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x7800,0xfc00,0xcc00,0xcc00,0xfc00,0x7800,0x0000,0x0000,		/* �	*/
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};

/*	end of file		*/
