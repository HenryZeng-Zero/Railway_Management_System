#pragma once

#include <adwaita.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

extern gchar* APPLICATION_NAME;

#define RMS_TYPE_APPLICATION (rms_application_get_type())
G_DECLARE_FINAL_TYPE (RmsApplication, rms_application, RMS, APPLICATION, AdwApplication)

/* public method */

AdwApplication *
rms_application_new (gchar* application_id,
                    GApplicationFlags  flags);

G_END_DECLS