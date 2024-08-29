#include "rms-window.h"

struct _RmsWindow
{
    AdwApplicationWindow parent_type;

    GtkToggleButton* sidebar_show;
    AdwOverlaySplitView* split_view;
    GtkButton* train_mamage;
    GtkButton* people_mamage;
    GtkButton* search_info;
    GtkButton* save_info;
    GtkButton* load_info;

    GtkNotebook* page_split;
};

G_DEFINE_TYPE (RmsWindow, rms_window, ADW_TYPE_APPLICATION_WINDOW)


static void
rms_test(GObject *gobject){
    g_print("test");
}

static void
rms_window_init (RmsWindow *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
    //g_signal_connect(self->sidebar_show, "clicked", G_CALLBACK (rms_test), NULL);
}

static void
rms_window_dispose (GObject *gobject)
{
  gtk_widget_dispose_template (GTK_WIDGET (gobject), RMS_TYPE_WINDOW);

  G_OBJECT_CLASS (rms_window_parent_class)->dispose (gobject);
}

static void
rms_window_class_init (RmsWindowClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class,
                                               "/rikki/tools/rms/rms-window.ui");

    gtk_widget_class_bind_template_child (widget_class, RmsWindow, sidebar_show);
    gtk_widget_class_bind_template_child (widget_class, RmsWindow, split_view);
    gtk_widget_class_bind_template_child (widget_class, RmsWindow, train_mamage);
    gtk_widget_class_bind_template_child (widget_class, RmsWindow, people_mamage);
    gtk_widget_class_bind_template_child (widget_class, RmsWindow, search_info);
    gtk_widget_class_bind_template_child (widget_class, RmsWindow, save_info);
    gtk_widget_class_bind_template_child (widget_class, RmsWindow, load_info);
    gtk_widget_class_bind_template_child (widget_class, RmsWindow, page_split);
}


GtkWindow *
rms_window_new (GtkApplication *app){
    return g_object_new (RMS_TYPE_WINDOW, 
                        "application",app,
                        NULL);
}