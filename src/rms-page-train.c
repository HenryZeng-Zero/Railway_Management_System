#include "rms-page-train.h"

#define GtkColumnViewColumnN(n) GtkColumnViewColumn* col##n;
struct _RmsPageTrain
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
    GtkColumnViewColumnN(5)
    GtkColumnViewColumnN(6)
    GtkColumnViewColumnN(7)
    GtkColumnViewColumnN(8)
};

G_DEFINE_TYPE (RmsPageTrain, rms_page_train, GTK_TYPE_BOX)

/* part: constructed */

static void
rms_page_train_constructed(GObject *gobject){
    RmsPageTrain *self = RMS_PAGE_TRAIN(gobject);

    /* 调用父类<加载完成后初始化>函数 */
    G_OBJECT_CLASS(rms_page_train_parent_class)->constructed(gobject);
}

/* End */

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
    GObjectClass *oclass = G_OBJECT_CLASS (klass);
    GtkWidgetClass *wclass = GTK_WIDGET_CLASS (klass);
    GtkWindowClass *winclass = GTK_WINDOW_CLASS (klass);

    gtk_widget_class_set_template_from_resource (wclass,
                                               "/rikki/tools/rms/rms-page-train.ui");

    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, add_data);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, set_data);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, del_data);

    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, column_view);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, col1);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, col2);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, col3);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, col4);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, col5);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, col6);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, col7);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, col8);

    oclass->constructed = rms_page_train_constructed;
}


GtkWidget *
rms_page_train_new(){
    return g_object_new (RMS_TYPE_PAGE_TRAIN,NULL);
}