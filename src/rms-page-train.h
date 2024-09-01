#pragma once

#include <adwaita.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define RMS_TYPE_PAGE_TRAIN (rms_page_train_get_type())
G_DECLARE_FINAL_TYPE (RmsPageTrain, rms_page_train, RMS, PAGE_TRAIN, GtkBox)

/* public method */
GtkWidget *
rms_page_train_new();

void
rms_page_train_set_root_window(RmsPageTrain *self, GtkWindow *root_window);

GtkWindow*
rms_page_train_get_root_window(RmsPageTrain *self);

G_END_DECLS