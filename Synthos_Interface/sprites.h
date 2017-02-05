#ifndef SPRITES_H
#define SPRITES_H

#define LOADING_W 128
#define LOADING_H 64

#define MAX_W 128
#define MAX_H 64

static const unsigned char PROGMEM loading_bmp[] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x30,0xc4,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xf4,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x3d,0x3f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xe0,0xe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0xb,0xc0,0x7,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x98,0x63,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7,0x20,0x83,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x3,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x1,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x70,0xe0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x99,0x30,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x99,0x30,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x70,0xe0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x4,0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x4,0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x4,0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x4,0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x7,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x41,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x88,0x83,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x87,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x40,0x4,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x30,0x18,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x10,0x0,0x40,0x0,0x8,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xc0,0x6,0x0,0x28,0x0,0x40,0x40,0x8,0x0,0x38,0x0,0x0,
0x0,0x0,0x0,0x1,0x40,0x6,0x0,0x28,0x0,0x40,0xa0,0x8,0x3,0xc4,0x0,0x0,
0x0,0x0,0x0,0x6,0x20,0x6,0x0,0x24,0x0,0x40,0xa0,0x8,0xc,0x2,0x0,0x0,
0x0,0x0,0x0,0x8,0x20,0x5,0x0,0x22,0x0,0x40,0x90,0x8,0x10,0x1,0x0,0x0,
0x0,0x80,0x0,0x30,0x10,0x9,0x0,0x21,0x0,0x80,0x90,0x10,0x10,0x0,0x80,0x0,
0x0,0x80,0x0,0x20,0x10,0x9,0x0,0x21,0x0,0x80,0x88,0x10,0x10,0x0,0x40,0x0,
0x0,0x80,0x0,0x20,0x8,0x9,0x0,0x20,0x80,0x80,0x88,0x10,0x10,0x0,0x0,0x0,
0x0,0x40,0x0,0x20,0x8,0x8,0x80,0x20,0x40,0x80,0x84,0x10,0x10,0x0,0x0,0x0,
0x0,0x40,0x0,0x20,0x8,0x8,0x80,0x20,0x40,0x80,0x84,0x10,0x10,0x0,0x0,0x0,
0x0,0x40,0x0,0x20,0x8,0x8,0x80,0x20,0x40,0x80,0x82,0x10,0x10,0x8,0x0,0x0,
0x0,0x40,0x0,0x20,0x8,0x10,0x80,0x40,0x40,0x80,0x42,0x10,0x10,0x6,0x0,0x0,
0x0,0x40,0x0,0x20,0x8,0x10,0x80,0x40,0x40,0x80,0x41,0x10,0x10,0x1,0x0,0x0,
0x0,0x20,0x0,0x20,0x8,0x18,0x40,0x40,0x40,0x80,0x41,0x20,0x10,0x0,0x80,0x0,
0x0,0x20,0x0,0x20,0x8,0x16,0x40,0x40,0x41,0x0,0x40,0xa0,0x10,0x0,0x60,0x0,
0x0,0x20,0x0,0x20,0x8,0x11,0xc0,0x40,0x41,0x0,0x40,0xa0,0x10,0x0,0x10,0x0,
0x0,0x20,0x0,0x10,0x8,0x10,0x40,0x40,0xc1,0x0,0x40,0x60,0x8,0x0,0x20,0x0,
0x0,0x20,0x0,0x8,0x8,0x20,0x20,0x43,0x1,0x0,0x40,0x20,0x4,0x0,0xc0,0x0,
0x0,0x10,0x0,0x4,0x30,0x20,0x20,0x4c,0x1,0x0,0x40,0x0,0x3,0x1,0x0,0x0,
0x0,0x10,0x0,0x2,0xc0,0x20,0x20,0x70,0x0,0x0,0x0,0x0,0x0,0x82,0x0,0x0,
0x0,0x10,0x7c,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x4c,0x0,0x0,
0x0,0x1f,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x30,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

#define DRUMS_W 33
#define DRUMS_H 24
static const unsigned char PROGMEM drums_bmp[] =
{
0x0,0x0,0x30,0x0,0x0,
0x0,0x0,0x78,0x0,0x0,
0x0,0x18,0x7f,0xe0,0x0,
0x0,0x3c,0x30,0x1f,0x80,
0x0,0x7c,0x0,0x0,0x0,
0x1,0x98,0x0,0x0,0x0,
0x6,0x0,0x0,0x0,0x0,
0x18,0xf,0xf0,0x0,0x0,
0x60,0x30,0xc,0x0,0x0,
0x80,0x41,0x82,0x0,0x0,
0x0,0x83,0xc1,0x0,0x0,
0x0,0x81,0x81,0x0,0x0,
0x0,0xc0,0x3,0x0,0x0,
0x0,0xb0,0xd,0x0,0x0,
0x0,0x8f,0xf1,0x0,0x0,
0x0,0x80,0x1,0x0,0x0,
0x0,0x80,0x1,0x0,0x0,
0x0,0x80,0x1,0x0,0x0,
0x0,0x80,0x1,0x0,0x0,
0x0,0x80,0x1,0x0,0x0,
0x0,0x80,0x1,0x0,0x0,
0x0,0x40,0x2,0x0,0x0,
0x0,0x30,0xc,0x0,0x0,
0x0,0xf,0xf0,0x0,0x0
};

#define SYNTH_W 85
#define SYNTH_H 16
static const unsigned char PROGMEM synth_bmp[] =
{
0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0x0,0x0,0x0,0x4,0x0,0x0,0x0,0x0,0x0,0x0,0x8,
0x1,0x80,0x60,0x4,0x0,0x0,0x0,0x0,0x0,0x1,0x48,
0x2,0x40,0x90,0x4,0x0,0x0,0x0,0x0,0x0,0x1,0x48,
0x84,0x21,0x8,0x4,0x0,0x0,0x0,0x0,0x0,0x1,0x48,
0x84,0x21,0x8,0x4,0x0,0x0,0x0,0x0,0x0,0x0,0x8,
0x84,0x21,0x8,0x4,0x1f,0xff,0xff,0xff,0xff,0xc0,0x8,
0x84,0x21,0x8,0x4,0x26,0xc6,0xd8,0xd8,0xdb,0x20,0x8,
0x84,0x21,0x8,0x4,0x26,0xc6,0xd8,0xd8,0xdb,0x20,0x8,
0x84,0x21,0x8,0x4,0x26,0xc6,0xd8,0xd8,0xdb,0x20,0x8,
0x84,0x21,0x8,0x4,0x26,0xc6,0xd8,0xd8,0xdb,0x20,0x8,
0x84,0x21,0x8,0x4,0x26,0xc6,0xd8,0xd8,0xdb,0x20,0x8,
0x48,0x12,0x0,0x4,0x20,0x0,0x0,0x0,0x0,0x20,0x8,
0x30,0xc,0x0,0x7,0xe0,0x0,0x0,0x0,0x0,0x21,0xf8,
0x0,0x0,0x0,0x4,0x20,0x0,0x0,0x0,0x0,0x21,0x8,
0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xf0
};


#define DRUM_EACH_W 32
#define DRUM_EACH_H 32

static const unsigned char PROGMEM drum_car[] =
{
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x7f,0xfe,0x0,
0x0,0x80,0x1,0x0,
0x1,0x0,0x0,0x80,
0x2,0x0,0x0,0x40,
0x4,0x0,0x0,0x20,
0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,
0xc,0x0,0x0,0x30,
0xa,0x0,0x0,0x50,
0x9,0x0,0x0,0x90,
0x8,0x80,0x1,0x10,
0x8,0x7f,0xfe,0x10,
0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,
0x8,0x3,0xe0,0x10,
0x8,0x2,0x20,0x10,
0x8,0x2,0x20,0x10,
0x8,0x3f,0xf8,0x10,
0x8,0x3f,0xfc,0x10,
0x4,0x3f,0xfc,0x20,
0x2,0xc,0x30,0x40,
0x1,0x0,0x0,0x80,
0x0,0x80,0x1,0x0,
0x0,0x7f,0xfe,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0
};

static const unsigned char PROGMEM drum_skull[] =

{
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x7f,0xfe,0x0,
0x0,0x80,0x1,0x0,
0x1,0x0,0x0,0x80,
0x2,0x0,0x0,0x40,
0x4,0x0,0x0,0x20,
0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,
0xc,0x0,0x0,0x30,
0xa,0x0,0x0,0x50,
0x9,0x0,0x0,0x90,
0x8,0x80,0x1,0x10,
0x8,0x7f,0xfe,0x10,
0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,
0x8,0x1f,0xf8,0x10,
0x8,0x3f,0xfc,0x10,
0x8,0x27,0xe4,0x10,
0x8,0x26,0x64,0x10,
0x8,0x3e,0x7c,0x10,
0x4,0xf,0xf0,0x20,
0x2,0xd,0xb0,0x40,
0x1,0x0,0x0,0x80,
0x0,0x80,0x1,0x0,
0x0,0x7f,0xfe,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0
};

static const unsigned char PROGMEM drum_train[] =
{
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x7f,0xfe,0x0,
0x0,0x80,0x1,0x0,
0x1,0x0,0x0,0x80,
0x2,0x0,0x0,0x40,
0x4,0x0,0x0,0x20,
0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,
0xc,0x0,0x0,0x30,
0xa,0x0,0x0,0x50,
0x9,0x0,0x0,0x90,
0x8,0x80,0x1,0x10,
0x8,0x7f,0xfe,0x10,
0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,
0x8,0x3f,0x30,0x10,
0x8,0x21,0x30,0x10,
0x8,0x21,0xf0,0x10,
0x8,0x3f,0xf0,0x10,
0x8,0x3f,0xf8,0x10,
0x4,0x3f,0xfc,0x20,
0x2,0x1b,0x30,0x40,
0x1,0x0,0x0,0x80,
0x0,0x80,0x1,0x0,
0x0,0x7f,0xfe,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0
};
static const unsigned char PROGMEM drum_shark[] =
{
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x7f,0xfe,0x0,
0x0,0x80,0x1,0x0,
0x1,0x0,0x0,0x80,
0x2,0x0,0x0,0x40,
0x4,0x0,0x0,0x20,
0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,
0xc,0x0,0x0,0x30,
0xa,0x0,0x0,0x50,
0x9,0x0,0x0,0x90,
0x8,0x80,0x1,0x10,
0x8,0x7f,0xfe,0x10,
0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,
0x8,0x1,0x0,0x10,
0x8,0x3,0x4,0x10,
0x8,0x3f,0xfc,0x10,
0x8,0x17,0xf8,0x10,
0x8,0xf,0xfc,0x10,
0x4,0x1f,0x84,0x20,
0x2,0x1,0xc0,0x40,
0x1,0x0,0x0,0x80,
0x0,0x80,0x1,0x0,
0x0,0x7f,0xfe,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0
};

static const unsigned char PROGMEM drum_skull_hit[] =
{
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0xff,0xff,0x0,
0x1,0x0,0x0,0x80,
0x2,0x0,0x0,0x40,
0x4,0x0,0x0,0x20,
0x8,0x0,0x0,0x10,
0x10,0x0,0x0,0x8,
0x18,0x0,0x0,0x18,
0x14,0x0,0x0,0x28,
0x12,0x0,0x0,0x48,
0x11,0x0,0x0,0x88,
0x10,0xff,0xff,0x8,
0x10,0x0,0x0,0x8,
0x10,0x1f,0xf8,0x8,
0x10,0x3f,0xfc,0x8,
0x10,0x3f,0xfc,0x8,
0x10,0x27,0xe4,0x8,
0x8,0x26,0x64,0x10,
0x4,0x3f,0xfc,0x20,
0x2,0x1d,0xb8,0x40,
0x1,0x0,0x0,0x80,
0x0,0xff,0xff,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0
};

static const unsigned char PROGMEM drum_abused_hit[] =
{
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x3f,0xf8,0x0,
0x0,0x40,0x4,0x0,
0x0,0x80,0x2,0x0,
0x1,0x0,0x1,0x0,
0x2,0x0,0x0,0x80,
0x4,0x0,0x0,0x40,
0x8,0x7,0xe0,0x20,
0x10,0xf,0xf0,0x10,
0x18,0xf,0xf0,0x30,
0x14,0x7,0xe0,0x50,
0x12,0x0,0x0,0x88,
0x21,0x0,0x1,0x8,
0x20,0x80,0x2,0x8,
0x20,0x40,0x4,0x8,
0x24,0x20,0x8,0x8,
0x22,0x1f,0xf0,0x10,
0x10,0x0,0x0,0x10,
0x10,0x24,0x40,0x10,
0x8,0xff,0xf0,0x20,
0x4,0x24,0x40,0x40,
0x2,0x0,0x0,0x80,
0x1,0x0,0x1,0x0,
0x0,0xff,0xfe,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0
};




static const unsigned char PROGMEM drumset_proto[] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,
0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,
0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,
0x2,0x0,0x0,0x40,0x2,0x0,0x0,0x40,0x2,0x0,0x0,0x40,0x2,0x0,0x0,0x40,
0x4,0x0,0x0,0x20,0x4,0x0,0x0,0x20,0x4,0x0,0x0,0x20,0x4,0x0,0x0,0x20,
0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,
0xc,0x0,0x0,0x30,0xc,0x0,0x0,0x30,0xc,0x0,0x0,0x30,0xc,0x0,0x0,0x30,
0xa,0x0,0x0,0x50,0xa,0x0,0x0,0x50,0xa,0x0,0x0,0x50,0xa,0x0,0x0,0x50,
0x9,0x0,0x0,0x90,0x9,0x0,0x0,0x90,0x9,0x0,0x0,0x90,0x9,0x0,0x0,0x90,
0x8,0x80,0x1,0x10,0x8,0x80,0x1,0x10,0x8,0x80,0x1,0x10,0x8,0x80,0x1,0x10,
0x8,0x7f,0xfe,0x10,0x8,0x7f,0xfe,0x10,0x8,0x7f,0xfe,0x10,0x8,0x7f,0xfe,0x10,
0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,
0x8,0x3f,0x30,0x10,0x8,0x3f,0xc0,0x10,0x8,0x3f,0xfc,0x10,0x8,0x3,0xe0,0x10,
0x8,0x21,0x30,0x10,0x8,0x22,0x40,0x10,0x8,0x24,0x90,0x10,0x8,0x2,0x20,0x10,
0x8,0x21,0xf0,0x10,0x8,0x22,0x40,0x10,0x8,0x24,0x90,0x10,0x8,0x2,0x20,0x10,
0x8,0x3f,0xf0,0x10,0x8,0x3f,0xf0,0x10,0x8,0x3f,0xf0,0x10,0x8,0x3f,0xf8,0x10,
0x8,0x3f,0xf8,0x10,0x8,0x3f,0xfc,0x10,0x8,0x3f,0xfc,0x10,0x8,0x3f,0xfc,0x10,
0x4,0x3f,0xfc,0x20,0x4,0x3f,0xfc,0x20,0x4,0x3f,0xfc,0x20,0x4,0x3f,0xfc,0x20,
0x2,0x1b,0x30,0x40,0x2,0x18,0x30,0x40,0x2,0xc,0x30,0x40,0x2,0xc,0x30,0x40,
0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,
0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,
0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,
0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,
0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,
0x2,0x0,0x0,0x40,0x2,0x0,0x0,0x40,0x2,0x0,0x0,0x40,0x2,0x0,0x0,0x40,
0x4,0x0,0x0,0x20,0x4,0x0,0x0,0x20,0x4,0x0,0x0,0x20,0x4,0x0,0x0,0x20,
0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,
0xc,0x0,0x0,0x30,0xc,0x0,0x0,0x30,0xc,0x0,0x0,0x30,0xc,0x0,0x0,0x30,
0xa,0x0,0x0,0x50,0xa,0x0,0x0,0x50,0xa,0x0,0x0,0x50,0xa,0x0,0x0,0x50,
0x9,0x0,0x0,0x90,0x9,0x0,0x0,0x90,0x9,0x0,0x0,0x90,0x9,0x0,0x0,0x90,
0x8,0x80,0x1,0x10,0x8,0x80,0x1,0x10,0x8,0x80,0x1,0x10,0x8,0x80,0x1,0x10,
0x8,0x7f,0xfe,0x10,0x8,0x7f,0xfe,0x10,0x8,0x7f,0xfe,0x10,0x8,0x7f,0xfe,0x10,
0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,
0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,0x8,0x0,0x0,0x10,
0x8,0x1f,0xf8,0x10,0x8,0x1f,0xf8,0x10,0x8,0x1f,0xf8,0x10,0x8,0x1f,0xf8,0x10,
0x8,0x33,0xcc,0x10,0x8,0x3f,0xfc,0x10,0x8,0x23,0xc4,0x10,0x8,0x3f,0xfc,0x10,
0x8,0x33,0xcc,0x10,0x8,0x27,0xe4,0x10,0x8,0x23,0xc4,0x10,0x8,0x3f,0xfc,0x10,
0x8,0x3e,0x7c,0x10,0x8,0x26,0x64,0x10,0x8,0x3e,0x7c,0x10,0x8,0x27,0xe4,0x10,
0x8,0x1f,0xf8,0x10,0x8,0x3e,0x7c,0x10,0x8,0xe,0x70,0x10,0x8,0x26,0x64,0x10,
0x4,0x4,0xa0,0x20,0x4,0xf,0xf0,0x20,0x4,0x7,0xe0,0x20,0x4,0x3f,0xfc,0x20,
0x2,0xf,0xf0,0x40,0x2,0xd,0xb0,0x40,0x2,0x5,0xa0,0x40,0x2,0x1d,0xb8,0x40,
0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,
0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,0x0,0x80,0x1,0x0,
0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,0x0,0x7f,0xfe,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};




#endif
