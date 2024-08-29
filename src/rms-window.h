#pragma once

#include <adwaita.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define RMS_TYPE_WINDOW (rms_window_get_type())
G_DECLARE_FINAL_TYPE (RmsWindow, rms_window, RMS, WINDOW, AdwApplicationWindow)

/* public method */
GtkWindow *
rms_window_new (GtkApplication *app);

G_END_DECLS