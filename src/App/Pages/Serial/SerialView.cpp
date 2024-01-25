#include "SerialView.h"

using namespace Page;

void SerialView::Create(lv_obj_t* root)
{
	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
	
	lv_obj_t* label = lv_label_create(root);
	lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
	lv_label_set_text(label, "");
	ui.labelTitle = label;

	label = lv_label_create(root);
	lv_label_set_text(label, "");
	lv_obj_center(label);
	ui.labelTick = label;
}

void SerialView::Delete()
{

}
