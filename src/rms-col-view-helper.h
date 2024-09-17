#pragma once

#include <gtk/gtk.h>

#define CV_bind_second_type GtkListItem

#define bind_type_cb(ByIDfunc,DataType,type) \
static void bind_##type##_cb(GtkSignalListItemFactory *factory, CV_bind_second_type *listitem) \
{ \
    GtkWidget *label = gtk_list_item_get_child(listitem); \
    GObject *item = gtk_list_item_get_item(GTK_LIST_ITEM(listitem)); \
    const char *string = ByIDfunc(DataType(item),type); \
    gtk_label_set_text(GTK_LABEL (label), string); \
}

#define link_type_cb(v, type) v[type] = bind_##type##_cb;

#define define_bind_funcList(name,nums) \
void (*name[nums])(GtkSignalListItemFactory *factory, CV_bind_second_type *listitem);

#define get_bind(v, type) v[type]