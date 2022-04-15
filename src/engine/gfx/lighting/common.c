#include <tt.h>

extern bool tt_gfx_gouraud_shading_active; //toggle if gouraud shading is active
extern bool tt_gfx_phong_shading_active; //toggle if phong shading is active
extern bool tt_gfx_tone_mapping_toggle; //toggle if tone mapping is enabled
extern float tt_gfx_exposure; //full scene exposure
extern float tt_gfx_saturation; //full scene saturation
extern float tt_gfx_contrast; //full scene contrast


//Gouraud Shading
void tt_gfx_gouraud_shading(bool active)
{
	tt_gfx_gouraud_shading_active=active;
}

//Phong Shading
void tt_gfx_phong_shading(bool active)
{
	tt_gfx_phong_shading_active=active;
}

//Tone Mapping
void tt_gfx_tone_mapping(bool active)
{
	tt_gfx_tone_mapping_toggle=active;
}

//Full scene exposure
void tt_gfx_set_exposure(float exposure)
{
	tt_gfx_exposure = exposure;
}

//Full scene saturation
void tt_gfx_set_saturation(float saturation)
{
	tt_gfx_saturation = saturation;
}

//Full scene contrast
void tt_gfx_set_contrast(float contrast) {
	tt_gfx_contrast = contrast;
}
