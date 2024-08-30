#include "rms-page-people.h"

#define GtkColumnViewColumnN(n) GtkColumnViewColumn* col##n;
struct _RmsPagePeople
{
    GtkBox parent_type;

    GtkButton* add_data;
    GtkButton* set_data;
    GtkButton* del_data;

    GtkColumnView* column_view;
    GtkColumnViewColumnN(1)
    GtkColumnViewColumnN(2)
    GtkColumnViewColumnN(3)
    GtkColumnViewColumnN(4)
};

G_DEFINE_TYPE (RmsPagePeople, rms_page_people, GTK_TYPE_BOX)

/* part: constructed */

static void
rms_page_people_constructed(GObject *gobject){
    RmsPagePeople *self = RMS_PAGE_PEOPLE(gobject);

    /* 调用父类<加载完成后初始化>函数 */
    G_OBJECT_CLASS(rms_page_people_parent_class)->constructed(gobject);
}

/* End */

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
    GObjectClass *oclass = G_OBJECT_CLASS (klass);
    GtkWidgetClass *wclass = GTK_WIDGET_CLASS (klass);
    GtkWindowClass *winclass = GTK_WINDOW_CLASS (klass);

    gtk_widget_class_set_template_from_resource (wclass,
                                               "/rikki/tools/rms/rms-page-people.ui");

    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, add_data);
    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, set_data);
    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, del_data);

    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, column_view);
    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, col1);
    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, col2);
    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, col3);
    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, col4);

    oclass->constructed = rms_page_people_constructed;
}


GtkWidget *
rms_page_people_new(){
    return g_object_new (RMS_TYPE_PAGE_PEOPLE,NULL);
}