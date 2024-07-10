#include "gtk_node.h"

void show_sidebar_button_toggled(GtkToggleButton* source){
    if (gtk_toggle_button_get_active(source)) {
        adw_overlay_split_view_set_show_sidebar(split_view, TRUE);
    }else {
        adw_overlay_split_view_set_show_sidebar(split_view, FALSE);
    }
}

void train_mamage_button_clicked(GtkButton* source){
    gtk_notebook_set_current_page(page_split, 0);
    // g_list_store_append(page_1_col_view_dataflow,)
}

void people_mamage_button_clicked(GtkButton* source){
    gtk_notebook_set_current_page(page_split, 1);
}

void search_info_button_clicked(GtkButton* source){
    gtk_notebook_set_current_page(page_split, 2);
}

void save_info_button_clicked(GtkButton* source){

}

void load_info_button_clicked(GtkButton* source){

}