#ifndef TT_GFX_VERTEX_H
#define TT_GFX_VERTEX_H

#pragma pack(1)
struct tt_vertex
{
	tt_vec3 pos;
	tt_vec2 tex;
	tt_vec3 normal;
} typedef tt_vertex;

#endif