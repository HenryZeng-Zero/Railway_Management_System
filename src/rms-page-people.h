#pragma once

#include <adwaita.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

extern GtkWindow *window_main;

#define RMS_TYPE_PAGE_PEOPLE (rms_page_people_get_type())
G_DECLARE_FINAL_TYPE (RmsPagePeople, rms_page_people, RMS, PAGE_PEOPLE, GtkBox)

/* public method */
GtkWidget *
rms_page_people_new();

void
rms_page_people_set_root_window(RmsPagePeople *self, GtkWindow *root_window);

GtkWindow*
rms_page_people_get_root_window(RmsPagePeople *self);

G_END_DECLS