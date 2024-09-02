#include "rms-application.h"
#include "gResource.h"
#include "rms-window.h"

struct _RmsApplication {
    AdwApplication parent_instance;
};

G_DEFINE_TYPE (RmsApplication, rms_application, ADW_TYPE_APPLICATION)

/* private methods */

static void
rms_application_activate (GApplication *app)
{
    GtkWindow *window = rms_window_new(GTK_APPLICATION (app));
    
    gtk_window_set_title(window, APPLICATION_NAME);
    gtk_window_set_default_size(window, 1200, 600);
    gtk_window_present (window);
}

static void
rms_application_class_init (RmsApplicationClass *klass)
{
    G_APPLICATION_CLASS (klass)->activate = rms_application_activate;
}

static void
rms_application_init (RmsApplication *self)
{
    /* gResource module loaded */
    g_resources_register (gResource_get_resource());
}

/* public methods */

AdwApplication *
rms_application_new (gchar* application_id,
                    GApplicationFlags  flags)
{
    return g_object_new (rms_application_get_type (),
                        "application-id", application_id,
                        "flags", flags,
                        NULL);
}