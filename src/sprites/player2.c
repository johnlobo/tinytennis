#include "player2.h"
// Data created with Img2CPC - (c) Retroworks - 2007-2015
// Tile sp_player2_00: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_00[5 * 20] = {
	0x00, 0x31, 0x20, 0x11, 0x00,
	0x11, 0x32, 0x30, 0x22, 0x22,
	0x10, 0x32, 0x30, 0x11, 0x11,
	0x10, 0x32, 0x30, 0x22, 0x22,
	0x10, 0x30, 0x30, 0x11, 0x11,
	0x00, 0x30, 0x20, 0x33, 0x22,
	0x01, 0x53, 0xf3, 0x22, 0x00,
	0x53, 0xf3, 0xf3, 0xa2, 0x00,
	0x59, 0xf3, 0xf3, 0x08, 0x00,
	0x59, 0xa3, 0xf3, 0x08, 0x00,
	0x51, 0xf3, 0xf3, 0x00, 0x00,
	0x51, 0xf3, 0xf3, 0x00, 0x00,
	0x41, 0xd3, 0xc3, 0x00, 0x00,
	0x01, 0x43, 0x03, 0x00, 0x00,
	0x01, 0x02, 0x0c, 0x00, 0x00,
	0x04, 0x08, 0x0c, 0x00, 0x00,
	0xae, 0x08, 0x0c, 0xaa, 0x00,
	0xae, 0x08, 0xff, 0xaa, 0x00,
	0xff, 0xaa, 0xff, 0xaa, 0x00,
	0x55, 0xaa, 0xff, 0x00, 0x00
};

// Tile sp_player2_01: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_01[5 * 20] = {
	0x11, 0x30, 0x00, 0x00, 0x00,
	0x32, 0x30, 0x20, 0x00, 0x00,
	0x30, 0x30, 0x08, 0x11, 0x00,
	0x30, 0x24, 0x08, 0x22, 0x22,
	0x30, 0x24, 0x08, 0x11, 0x11,
	0x04, 0x0c, 0x00, 0x22, 0x22,
	0x01, 0x49, 0x00, 0x11, 0x11,
	0x53, 0xf3, 0xa2, 0x33, 0x22,
	0xf3, 0x59, 0xa2, 0x22, 0x00,
	0xf3, 0x0c, 0xb3, 0x00, 0x00,
	0xf3, 0xf3, 0xa6, 0x00, 0x00,
	0xf3, 0xf3, 0xa2, 0x00, 0x00,
	0xc3, 0xe3, 0x82, 0x00, 0x00,
	0x03, 0x83, 0x02, 0x00, 0x00,
	0x40, 0x81, 0x02, 0x00, 0x00,
	0x11, 0x04, 0x08, 0x00, 0x00,
	0x33, 0x04, 0x08, 0x00, 0x00,
	0x22, 0x00, 0x5d, 0xaa, 0x00,
	0xc3, 0x00, 0xff, 0xaa, 0x00,
	0xc3, 0x82, 0x55, 0x00, 0x00
};

// Tile sp_player2_02: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_02[5 * 20] = {
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x11, 0x30, 0x00, 0x00, 0x00,
	0x32, 0x30, 0x20, 0x00, 0x00,
	0x30, 0x30, 0x08, 0x00, 0x00,
	0x30, 0x24, 0x08, 0x11, 0x00,
	0x30, 0x24, 0x08, 0x22, 0x22,
	0x04, 0x0c, 0x00, 0x11, 0x11,
	0x01, 0x49, 0x00, 0x22, 0x22,
	0x53, 0xf3, 0xa2, 0x11, 0x11,
	0xf3, 0x59, 0xa2, 0x33, 0x22,
	0xf3, 0xa6, 0xb3, 0x00, 0x00,
	0xf3, 0xf3, 0x0c, 0x00, 0x00,
	0xc3, 0xe3, 0x86, 0x00, 0x00,
	0x03, 0x83, 0x02, 0x00, 0x00,
	0x01, 0x03, 0x00, 0x00, 0x00,
	0x04, 0x08, 0x00, 0x00, 0x00,
	0x04, 0x08, 0x00, 0x00, 0x00,
	0x11, 0x08, 0x00, 0x00, 0x00,
	0x41, 0xff, 0x00, 0x00, 0x00,
	0x41, 0xff, 0xaa, 0x00, 0x00
};

// Tile sp_player2_03: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_03[5 * 20] = {
	0x00, 0x32, 0x20, 0x00, 0x00,
	0x11, 0x30, 0x30, 0x00, 0x00,
	0x10, 0x30, 0x24, 0x00, 0x22,
	0x10, 0x30, 0x0c, 0x11, 0x11,
	0x10, 0x30, 0x0c, 0x00, 0x22,
	0x00, 0x0c, 0x08, 0x11, 0x11,
	0x00, 0x06, 0x82, 0x00, 0x22,
	0x01, 0xf3, 0xf3, 0x11, 0x33,
	0x51, 0xa6, 0xf3, 0x11, 0x00,
	0x51, 0xa6, 0x59, 0x22, 0x00,
	0x51, 0xf3, 0xf3, 0x08, 0x00,
	0x51, 0xf3, 0xf3, 0x00, 0x00,
	0x41, 0xd3, 0xc3, 0x00, 0x00,
	0x01, 0x43, 0x03, 0x00, 0x00,
	0x01, 0x42, 0xc0, 0x00, 0x00,
	0x04, 0x08, 0x33, 0x00, 0x00,
	0x04, 0x08, 0x33, 0x00, 0x00,
	0x0c, 0x00, 0x11, 0x82, 0x00,
	0xff, 0x00, 0x41, 0xc3, 0x00,
	0xff, 0xaa, 0x41, 0xc3, 0x00
};

// Tile sp_player2_04: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_04[5 * 20] = {
	0x00, 0x00, 0x10, 0x31, 0x00,
	0x00, 0x00, 0x30, 0x30, 0x22,
	0x11, 0x00, 0x18, 0x30, 0x20,
	0x22, 0x22, 0x0c, 0x30, 0x20,
	0x11, 0x00, 0x0c, 0x30, 0x20,
	0x22, 0x22, 0x04, 0x0c, 0x00,
	0x11, 0x00, 0x41, 0x09, 0x00,
	0x33, 0x22, 0xf3, 0xf3, 0x02,
	0x00, 0x22, 0xf3, 0x59, 0xa2,
	0x00, 0x11, 0xa6, 0x59, 0xa2,
	0x00, 0x04, 0xf3, 0xf3, 0xa2,
	0x00, 0x00, 0xf3, 0xf3, 0xa2,
	0x00, 0x00, 0xc3, 0xe3, 0x82,
	0x00, 0x00, 0x03, 0x83, 0x02,
	0x00, 0x00, 0xc0, 0x81, 0x02,
	0x00, 0x00, 0x33, 0x04, 0x08,
	0x00, 0x00, 0x33, 0x04, 0x08,
	0x00, 0x41, 0x22, 0x00, 0x0c,
	0x00, 0xc3, 0x82, 0x00, 0xff,
	0x00, 0xc3, 0x82, 0x55, 0xff
};

// Tile sp_player2_05: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_05[5 * 20] = {
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x30, 0x22,
	0x00, 0x00, 0x10, 0x30, 0x31,
	0x00, 0x00, 0x04, 0x30, 0x30,
	0x00, 0x22, 0x04, 0x18, 0x30,
	0x11, 0x11, 0x04, 0x18, 0x30,
	0x22, 0x22, 0x00, 0x0c, 0x08,
	0x11, 0x11, 0x00, 0x86, 0x02,
	0x22, 0x22, 0x51, 0xf3, 0xa3,
	0x11, 0x33, 0x51, 0xa6, 0xf3,
	0x00, 0x00, 0x73, 0x59, 0xf3,
	0x00, 0x00, 0x0c, 0xf3, 0xf3,
	0x00, 0x00, 0x49, 0xd3, 0xc3,
	0x00, 0x00, 0x01, 0x43, 0x03,
	0x00, 0x00, 0x00, 0x03, 0x02,
	0x00, 0x00, 0x00, 0x04, 0x08,
	0x00, 0x00, 0x00, 0x04, 0x08,
	0x00, 0x00, 0x00, 0x04, 0x22,
	0x00, 0x00, 0x00, 0xff, 0x82,
	0x00, 0x00, 0x55, 0xff, 0x82
};

// Tile sp_player2_06: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_06[5 * 20] = {
	0x00, 0x00, 0x00, 0x30, 0x22,
	0x00, 0x00, 0x10, 0x30, 0x31,
	0x00, 0x22, 0x04, 0x30, 0x30,
	0x11, 0x11, 0x04, 0x18, 0x30,
	0x22, 0x22, 0x04, 0x18, 0x30,
	0x11, 0x11, 0x00, 0x0c, 0x08,
	0x22, 0x22, 0x00, 0x86, 0x02,
	0x11, 0x33, 0x51, 0xf3, 0xa3,
	0x00, 0x11, 0x51, 0xa6, 0xf3,
	0x00, 0x00, 0x73, 0x0c, 0xf3,
	0x00, 0x00, 0x59, 0xf3, 0xf3,
	0x00, 0x00, 0x51, 0xf3, 0xf3,
	0x00, 0x00, 0x41, 0xd3, 0xc3,
	0x00, 0x00, 0x01, 0x43, 0x03,
	0x00, 0x00, 0x01, 0x42, 0x80,
	0x00, 0x00, 0x04, 0x08, 0x33,
	0x00, 0x00, 0x04, 0x08, 0x33,
	0x00, 0x55, 0xae, 0x00, 0x11,
	0x00, 0x55, 0xff, 0x00, 0xc3,
	0x00, 0x00, 0xaa, 0x41, 0xc3
};

// Tile sp_player2_07: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_07[5 * 20] = {
	0x00, 0x32, 0x20, 0x00, 0x00,
	0x11, 0x30, 0x30, 0x00, 0x00,
	0x10, 0x30, 0x30, 0x00, 0x00,
	0x10, 0x30, 0x24, 0x00, 0x22,
	0x10, 0x30, 0x24, 0x11, 0x11,
	0x00, 0x30, 0x20, 0x00, 0x22,
	0x01, 0x53, 0xf3, 0x11, 0x11,
	0x53, 0xf3, 0xf3, 0x00, 0x22,
	0x0c, 0xf3, 0xf3, 0x11, 0x33,
	0x59, 0xf3, 0xa6, 0x11, 0x00,
	0x59, 0xf3, 0xf3, 0x08, 0x00,
	0x59, 0xf3, 0xf3, 0x08, 0x00,
	0x41, 0xd3, 0xc3, 0x00, 0x00,
	0x01, 0x43, 0x03, 0x00, 0x00,
	0x01, 0x02, 0x0c, 0x00, 0x00,
	0x04, 0x08, 0x0c, 0x00, 0x00,
	0xae, 0x08, 0x0c, 0xaa, 0x00,
	0xae, 0x08, 0xff, 0xaa, 0x00,
	0xff, 0xaa, 0xff, 0xaa, 0x00,
	0x55, 0xaa, 0xff, 0x00, 0x00
};

// Tile sp_player2_08: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_08[5 * 20] = {
	0x00, 0x00, 0x32, 0x20, 0x00,
	0x00, 0x11, 0x32, 0x30, 0x00,
	0x00, 0x10, 0x32, 0x30, 0x00,
	0x00, 0x10, 0x30, 0x30, 0x00,
	0x00, 0x10, 0x30, 0x30, 0x00,
	0x00, 0x00, 0x30, 0x20, 0x22,
	0x00, 0x01, 0x53, 0xa2, 0x00,
	0x00, 0x53, 0xf3, 0xa2, 0x22,
	0x00, 0x0c, 0xf3, 0xa6, 0x00,
	0x00, 0x59, 0xf3, 0xa6, 0x00,
	0x04, 0x51, 0xf3, 0xf3, 0x00,
	0x00, 0x51, 0xf3, 0xf3, 0x00,
	0x00, 0x41, 0xd3, 0xc3, 0x00,
	0x00, 0x01, 0x43, 0x03, 0x00,
	0x00, 0x01, 0x02, 0x0c, 0x00,
	0x00, 0x04, 0x08, 0x0c, 0x00,
	0x00, 0xae, 0x08, 0x0c, 0xaa,
	0x00, 0xae, 0x08, 0xff, 0xaa,
	0x00, 0xff, 0xaa, 0xff, 0xaa,
	0x00, 0x55, 0xaa, 0xff, 0x00
};

// Tile sp_player2_09: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_09[5 * 20] = {
	0x00, 0x00, 0x11, 0x30, 0x00,
	0x00, 0x00, 0x32, 0x32, 0x20,
	0x00, 0x11, 0x30, 0x32, 0x20,
	0x00, 0x22, 0x18, 0x30, 0x20,
	0x11, 0x11, 0x18, 0x30, 0x20,
	0x00, 0x22, 0x10, 0x30, 0x00,
	0x11, 0x11, 0x03, 0xf3, 0x00,
	0x00, 0x23, 0xf3, 0xf3, 0x00,
	0x00, 0x00, 0x59, 0xf3, 0x00,
	0x00, 0x04, 0xf3, 0xf3, 0x00,
	0x00, 0x04, 0xf3, 0xf3, 0x00,
	0x00, 0x08, 0xf3, 0xf3, 0xa2,
	0x00, 0x00, 0xc3, 0xe3, 0x82,
	0x00, 0x00, 0x03, 0x03, 0x02,
	0x00, 0x00, 0x03, 0x04, 0x08,
	0x00, 0x00, 0x0c, 0x04, 0x08,
	0x00, 0x55, 0x0c, 0x04, 0x5d,
	0x00, 0x55, 0x0c, 0x55, 0xff,
	0x00, 0x55, 0xff, 0x55, 0xff,
	0x00, 0x00, 0xff, 0x55, 0xaa
};

// Tile sp_player2_10: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_10[5 * 20] = {
	0x00, 0x31, 0x20, 0x00, 0x00,
	0x11, 0x32, 0x30, 0x00, 0x00,
	0x10, 0x32, 0x30, 0x11, 0x00,
	0x10, 0x32, 0x30, 0x22, 0x22,
	0x10, 0x30, 0x30, 0x11, 0x11,
	0x00, 0x30, 0x20, 0x22, 0x22,
	0x03, 0x53, 0xf3, 0x11, 0x11,
	0x59, 0xf3, 0xf3, 0x33, 0x22,
	0x59, 0xf3, 0xf3, 0x22, 0x00,
	0x51, 0xa3, 0xf3, 0xa2, 0x00,
	0x51, 0x53, 0xf3, 0x08, 0x00,
	0x51, 0xf3, 0xf3, 0x08, 0x00,
	0x41, 0xd3, 0xc3, 0x00, 0x00,
	0x01, 0x03, 0x0c, 0xaa, 0x00,
	0x01, 0x02, 0xff, 0xaa, 0x00,
	0x04, 0x08, 0xff, 0xaa, 0x00,
	0xae, 0x08, 0xff, 0x00, 0x00,
	0xae, 0x08, 0x00, 0x00, 0x00,
	0xff, 0xaa, 0x00, 0x00, 0x00,
	0x55, 0xaa, 0x00, 0x00, 0x00
};

// Tile sp_player2_11: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_11[5 * 20] = {
	0x00, 0x31, 0x20, 0x22, 0x22,
	0x11, 0x32, 0x30, 0x11, 0x11,
	0x10, 0x32, 0x30, 0x22, 0x22,
	0x10, 0x32, 0x30, 0x11, 0x11,
	0x10, 0x30, 0x30, 0x33, 0x22,
	0x00, 0x30, 0x20, 0x22, 0x00,
	0x01, 0x53, 0xf3, 0xa2, 0x00,
	0x51, 0xf3, 0xf3, 0x08, 0x00,
	0x51, 0xf3, 0xf3, 0x08, 0x00,
	0x53, 0xa3, 0xf3, 0x00, 0x00,
	0x59, 0x53, 0xf3, 0x00, 0x00,
	0x59, 0xf3, 0xf3, 0x00, 0x00,
	0x41, 0xd3, 0xc3, 0x00, 0x00,
	0xae, 0x09, 0x03, 0x00, 0x00,
	0xae, 0x08, 0x0c, 0x00, 0x00,
	0xff, 0xaa, 0x0c, 0x00, 0x00,
	0x55, 0xaa, 0x0c, 0xaa, 0x00,
	0x00, 0x00, 0xff, 0xaa, 0x00,
	0x00, 0x00, 0xff, 0xaa, 0x00,
	0x00, 0x00, 0xff, 0x00, 0x00
};

// Tile sp_player2_12: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_12[5 * 20] = {
	0x00, 0x22, 0x31, 0x20, 0x00,
	0x11, 0x11, 0x04, 0x10, 0x00,
	0x22, 0x22, 0x0c, 0x18, 0x00,
	0x11, 0x11, 0x0c, 0x18, 0x00,
	0x22, 0x22, 0x08, 0x18, 0x00,
	0x11, 0x33, 0x0c, 0x08, 0x00,
	0x00, 0x11, 0x53, 0xf3, 0x00,
	0x00, 0x13, 0x73, 0xf3, 0xa2,
	0x00, 0x19, 0x73, 0xf3, 0x08,
	0x00, 0x59, 0x23, 0xf3, 0x08,
	0x00, 0x0c, 0x59, 0xf3, 0x08,
	0x00, 0x51, 0x73, 0xa6, 0x00,
	0x00, 0x41, 0xd3, 0xc3, 0x00,
	0x00, 0x01, 0x03, 0x03, 0x00,
	0x00, 0x01, 0x02, 0x0c, 0x00,
	0x00, 0x04, 0x08, 0x0c, 0x00,
	0x00, 0x04, 0x08, 0x0c, 0x00,
	0x00, 0x55, 0xaa, 0xff, 0x00,
	0x00, 0xff, 0xaa, 0xff, 0xaa,
	0x00, 0xff, 0xaa, 0xff, 0xaa
};

// Tile sp_player2_13: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_13[5 * 20] = {
	0x00, 0x00, 0x10, 0x32, 0x00,
	0x00, 0x11, 0x00, 0x08, 0x20,
	0x00, 0x22, 0x26, 0x0c, 0x20,
	0x11, 0x11, 0x04, 0x0c, 0x20,
	0x00, 0x22, 0x26, 0x04, 0x20,
	0x11, 0x11, 0x04, 0x0c, 0x00,
	0x00, 0x33, 0x23, 0xf3, 0xf3,
	0x00, 0x00, 0x73, 0xf3, 0xa6,
	0x00, 0x04, 0x33, 0xf3, 0xa6,
	0x00, 0x04, 0xb3, 0x53, 0xa6,
	0x00, 0x04, 0x0c, 0xf3, 0x08,
	0x00, 0x00, 0xb3, 0xf3, 0xa2,
	0x00, 0x00, 0xc3, 0xe3, 0x82,
	0x00, 0x00, 0x0c, 0x03, 0x02,
	0x00, 0x00, 0x0c, 0x04, 0x08,
	0x00, 0x55, 0xff, 0x04, 0x08,
	0x00, 0x55, 0xff, 0x04, 0x08,
	0x00, 0x00, 0x00, 0x55, 0xaa,
	0x00, 0x00, 0x00, 0x55, 0xff,
	0x00, 0x00, 0x00, 0x55, 0xff
};

// Tile sp_player2_14: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_14[5 * 20] = {
	0x11, 0x11, 0x00, 0x00, 0x00,
	0x22, 0x22, 0x31, 0x20, 0x00,
	0x11, 0x11, 0x04, 0x10, 0x00,
	0x22, 0x22, 0x0c, 0x18, 0x00,
	0x11, 0x33, 0x0c, 0x18, 0x00,
	0x00, 0x11, 0x08, 0x18, 0x00,
	0x00, 0x13, 0x26, 0x08, 0x00,
	0x00, 0x59, 0x73, 0xf3, 0x00,
	0x00, 0x59, 0x73, 0xf3, 0x00,
	0x00, 0x0c, 0x59, 0xf3, 0xa2,
	0x00, 0x51, 0x23, 0xf3, 0x08,
	0x00, 0x51, 0xf3, 0xf3, 0x08,
	0x00, 0x51, 0xf3, 0xa6, 0x00,
	0x00, 0x01, 0x03, 0x0c, 0x00,
	0x00, 0x01, 0x03, 0x0c, 0x00,
	0x00, 0x04, 0x08, 0xff, 0xaa,
	0x00, 0x04, 0x08, 0xff, 0xaa,
	0x00, 0x04, 0x08, 0x00, 0x00,
	0x00, 0xff, 0xaa, 0x00, 0x00,
	0x00, 0xff, 0xaa, 0x00, 0x00
};

// Tile sp_player2_15: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_15[5 * 20] = {
	0x11, 0x11, 0x10, 0x32, 0x00,
	0x22, 0x22, 0x20, 0x08, 0x20,
	0x11, 0x11, 0x24, 0x0c, 0x20,
	0x22, 0x33, 0x24, 0x0c, 0x20,
	0x11, 0x22, 0x24, 0x04, 0x20,
	0x00, 0x22, 0x04, 0x0c, 0x00,
	0x00, 0x22, 0x51, 0xf3, 0xa2,
	0x00, 0x08, 0xf3, 0xf3, 0xf3,
	0x00, 0x26, 0xf3, 0xf3, 0xa6,
	0x00, 0x04, 0xf3, 0xf3, 0xa6,
	0x00, 0x00, 0xf3, 0xf3, 0xa6,
	0x00, 0x00, 0xf3, 0xf3, 0x0c,
	0x00, 0x00, 0xc3, 0xe3, 0x82,
	0x00, 0x00, 0x03, 0x03, 0x02,
	0x00, 0x00, 0x03, 0x04, 0x08,
	0x00, 0x00, 0x0c, 0x04, 0x08,
	0x00, 0x00, 0x0c, 0x04, 0x08,
	0x00, 0x00, 0xff, 0x55, 0xaa,
	0x00, 0x55, 0xff, 0x55, 0xff,
	0x00, 0x55, 0xff, 0x55, 0xff
};

// Tile sp_player2_16: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_16[5 * 20] = {
	0x00, 0x10, 0x32, 0x00, 0x00,
	0x00, 0x20, 0x08, 0x20, 0x00,
	0x00, 0x24, 0x0c, 0x20, 0x00,
	0x00, 0x24, 0x0c, 0x20, 0x00,
	0x00, 0x24, 0x04, 0x20, 0x00,
	0x00, 0x00, 0x26, 0x00, 0x00,
	0x00, 0x11, 0x51, 0xa2, 0x00,
	0x00, 0xa2, 0x73, 0xf3, 0x00,
	0x00, 0xb3, 0x51, 0xa6, 0x00,
	0x00, 0x08, 0x73, 0xa6, 0x00,
	0x00, 0x19, 0x59, 0xa6, 0x00,
	0x00, 0xa6, 0x73, 0xa2, 0x08,
	0x00, 0xc3, 0xe3, 0x82, 0x00,
	0x00, 0x03, 0x03, 0x02, 0x00,
	0x00, 0x03, 0x04, 0x08, 0x00,
	0x00, 0x0c, 0x04, 0x08, 0x00,
	0x00, 0x0c, 0x04, 0x08, 0x00,
	0x00, 0xff, 0x55, 0xaa, 0x00,
	0x55, 0xff, 0x55, 0xff, 0x00,
	0x55, 0xff, 0x55, 0xff, 0x00
};

// Tile sp_player2_17: 10x20 pixels, 5x20 bytes.
const u8 sp_player2_17[5 * 20] = {
	0x00, 0x31, 0x20, 0x00, 0x00,
	0x10, 0x04, 0x10, 0x00, 0x00,
	0x10, 0x0c, 0x18, 0x00, 0x00,
	0x10, 0x0c, 0x18, 0x11, 0x00,
	0x10, 0x08, 0x18, 0x22, 0x22,
	0x00, 0x0c, 0x08, 0x11, 0x11,
	0x00, 0xf3, 0xf3, 0x22, 0x22,
	0x51, 0xf3, 0xb3, 0x33, 0x00,
	0x04, 0xf3, 0x19, 0x08, 0x00,
	0x04, 0x0c, 0x59, 0x08, 0x00,
	0x51, 0xb3, 0xf3, 0x04, 0x08,
	0x51, 0xf3, 0xf3, 0x00, 0x00,
	0x41, 0xd3, 0xc3, 0x00, 0x00,
	0x01, 0x03, 0x03, 0x00, 0x00,
	0x01, 0x02, 0x0c, 0x00, 0x00,
	0x04, 0x08, 0x0c, 0x00, 0x00,
	0x04, 0x08, 0x0c, 0x00, 0x00,
	0x55, 0xaa, 0xff, 0x00, 0x00,
	0xff, 0xaa, 0xff, 0xaa, 0x00,
	0xff, 0xaa, 0xff, 0xaa, 0x00
};

