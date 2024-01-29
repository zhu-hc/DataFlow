#include "HomeView.h"

using namespace Page;

// lv_group_t *group = lv_group_create();
// lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), group);
// lv_group_add_obj(group, btn);

void HomeView::Create(lv_obj_t* root)
{
	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

	//Write codes ui.menu
	ui.menu = lv_img_create(root);
	lv_obj_add_flag(ui.menu, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_set_align(ui.menu, LV_ALIGN_CENTER);
	lv_obj_set_size(ui.menu, 128, 128);

	//Write style for ui.menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui.menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	ui.group = lv_group_create();
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER, "Main"), ui.group);

	lv_group_add_obj(ui.group, ui.menu);
	lv_group_focus_obj(ui.menu);
	lv_group_focus_freeze(ui.group, true);
	lv_group_set_editing(ui.group, true);

	// lv_obj_t* labe = lv_label_create(root);
	// lv_label_set_text(labe, "最是人间留不住 朱颜辞镜花辞树");
	// lv_label_set_long_mode(labe, LV_LABEL_LONG_WRAP);
	// lv_obj_set_pos(labe, 0, 30);
	// lv_obj_set_size(labe, 320, 20);
	// lv_obj_set_style_text_font(labe, Resource.GetFont("ali_20"), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void HomeView::Delete()
{

}
