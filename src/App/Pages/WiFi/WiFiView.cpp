#include "WiFiView.h"

using namespace Page;

void WiFiView::Create(lv_obj_t* root)
{
	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
	
	ui.labelInfo = lv_label_create(root);
	lv_obj_set_align(ui.labelInfo, LV_ALIGN_TOP_LEFT);
	lv_obj_set_size(ui.labelInfo, LV_HOR_RES, LV_VER_RES);
	lv_label_set_text(ui.labelInfo, "");
	lv_obj_set_style_text_font(ui.labelInfo, Resource.GetFont("ali_20"), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void WiFiView::Delete()
{

}
