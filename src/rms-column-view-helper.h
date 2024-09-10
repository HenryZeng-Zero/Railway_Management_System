#pragma once

#define 

#define rms_column_view_ui_new(root_name,bind_name,bind_quantity) \
#define RMS_COLUMN_VIEW##root_name root_name \
GtkColumnView* root_name; \
struct \
{ \
    GtkColumnViewColumn* col[bind_quantity]; \
    void (*col_bind[bind_quantity])(GtkSignalListItemFactory *factory, GtkListItem *listitem); \
} bind_name;

#define rms_column_view_get_col(self_object,bind_name,id) \
self_object->bind_name.col[id]

#define rms_column_view_get_func(self_object,bind_name,id) \
self_object->bind_name.col_bind[id]

#define rms_column_view_bind_func_new(func_name,id,ByIdFunc,item_type) \
static void \
func_name(GtkSignalListItemFactory *factory, GtkListItem *listitem) \
{ \
    GtkWidget *label = gtk_list_item_get_child(listitem); \
    GObject *item = gtk_list_item_get_item(GTK_LIST_ITEM(listitem)); \
    const char *string = ByIdFunc(item_type(item),id); \
    gtk_label_set_text(GTK_LABEL (label), string); \
}

#define rms_column_view_bind_func_connect(columns,id,func_name) \
columns.col_bind[id] = func_name;

#define rms_column_view_bind_template_child(widget_class, TypeName,             \
                                            member_name, bind_name, id)         \
gtk_widget_class_bind_template_child_full(                                      \
    widget_class, member_name, FALSE,                                           \
    G_STRUCT_OFFSET(TypeName, bind_name.col[id]))
