#include "SerialView.h"

using namespace Page;

void SerialView::Create(lv_obj_t* root)
{
	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
	
	lv_obj_t* label = lv_label_create(root);
	lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
	lv_label_set_text(label, "");
	ui.labelBaud = label;

	ui.group_minor = lv_group_create();
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER, "Minor"), ui.group_minor);

	lv_group_add_obj(ui.group_minor, ui.labelBaud);
	lv_group_focus_obj(ui.labelBaud);
	lv_group_focus_freeze(ui.group_minor, true);
	lv_group_set_editing(ui.group_minor, true);
}

void SerialView::Delete()
{

}
