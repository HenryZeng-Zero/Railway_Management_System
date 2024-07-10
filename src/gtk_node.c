#include "gtk_node.h"

GtkToggleButton*                   show_sidebar_button;
  AdwOverlaySplitView*             split_view;

    //sidebar
    GtkButton*                     train_mamage;
    GtkButton*                     people_mamage;
    GtkButton*                     search_info;
    GtkButton*                     save_info;
    GtkButton*                     load_info;

    //content
    GtkNotebook*                   page_split;
      GtkColumnView*               page_1_col_view;
        GListStore*                page_1_col_view_dataflow;
      GtkColumnView*               page_2_col_view;
        GListStore*                page_2_col_view_dataflow;