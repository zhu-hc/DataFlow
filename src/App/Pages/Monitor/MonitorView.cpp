#include "MonitorView.h"

using namespace Page;

void MonitorView::Create(lv_obj_t* root)
{
	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
	
	ui.labelInfo = lv_label_create(root);
	lv_obj_set_align(ui.labelInfo, LV_ALIGN_TOP_LEFT);
	lv_obj_set_size(ui.labelInfo, LV_HOR_RES, LV_VER_RES);
	lv_label_set_text(ui.labelInfo, "");
}

void MonitorView::Delete()
{

}
