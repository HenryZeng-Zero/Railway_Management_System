#include "rms-page-people.h"

struct _RmsPagePeople
{
    GtkBox parent_type;
};

G_DEFINE_TYPE (RmsPagePeople, rms_page_people, GTK_TYPE_BOX)


static void
rms_page_people_init (RmsPagePeople *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
    //g_signal_connect(self->sidebar_show, "clicked", G_CALLBACK (rms_test), NULL);
}

static void
rms_page_people_dispose (GObject *gobject)
{
  gtk_widget_dispose_template (GTK_WIDGET (gobject), RMS_TYPE_PAGE_PEOPLE);

  G_OBJECT_CLASS (rms_page_people_parent_class)->dispose (gobject);
}

static void
rms_page_people_class_init (RmsPagePeopleClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class,
                                               "/rikki/tools/rms/rms-page-people.ui");
}


GtkWidget *
rms_page_people_new(){
    return g_object_new (RMS_TYPE_PAGE_PEOPLE,NULL);
}