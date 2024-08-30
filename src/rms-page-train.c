#include "rms-page-train.h"

struct _RmsPageTrain
{
    GtkBox parent_type;
};

G_DEFINE_TYPE (RmsPageTrain, rms_page_train, GTK_TYPE_BOX)

static void
rms_page_train_init (RmsPageTrain *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
}

static void
rms_page_train_dispose (GObject *gobject)
{
  gtk_widget_dispose_template (GTK_WIDGET (gobject), RMS_TYPE_PAGE_TRAIN);

  G_OBJECT_CLASS (rms_page_train_parent_class)->dispose (gobject);
}

static void
rms_page_train_class_init (RmsPageTrainClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class,
                                               "/rikki/tools/rms/rms-page-train.ui");
}


GtkWidget *
rms_page_train_new(){
    return g_object_new (RMS_TYPE_PAGE_TRAIN,NULL);
}