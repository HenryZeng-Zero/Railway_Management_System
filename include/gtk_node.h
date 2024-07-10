#ifndef GTK_NODE_H
#define GTK_NODE_H

#include <adwaita.h>

extern GtkToggleButton*                   show_sidebar_button;
extern   AdwOverlaySplitView*             split_view;

           //sidebar
extern     GtkButton*                     train_mamage;
extern     GtkButton*                     people_mamage;
extern     GtkButton*                     search_info;
extern     GtkButton*                     save_info;
extern     GtkButton*                     load_info;

           //content
extern     GtkNotebook*                   page_split;
extern       GtkColumnView*               page_1_col_view;
extern         GListStore*                page_1_col_view_dataflow;
extern       GtkColumnView*               page_2_col_view;
extern         GListStore*                page_2_col_view_dataflow;

/* -> to respond to all activities */
extern void show_sidebar_button_toggled(GtkToggleButton* source);

extern void train_mamage_button_clicked(GtkButton* source);
extern void people_mamage_button_clicked(GtkButton* source);
extern void search_info_button_clicked(GtkButton* source);
extern void save_info_button_clicked(GtkButton* source);
extern void load_info_button_clicked(GtkButton* source);

/* -> to finish some work of init */
// extern void rms_column_view_init(GtkColumnView* source);
#endif