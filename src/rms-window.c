#include "rms-window.h"
#include "rms-page-train.h"
#include "rms-page-people.h"

#include "sqlite3.h"

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
    GtkWidget* page_data[2];

    sqlite3* db;
};

G_DEFINE_TYPE (RmsWindow, rms_window, ADW_TYPE_APPLICATION_WINDOW)

/* part: constructed */

static void
rms_window_sidebar_split_view_collapse(RmsWindow *self)
{
    gboolean status = adw_overlay_split_view_get_show_sidebar(self->split_view);
    adw_overlay_split_view_set_show_sidebar(self->split_view, !status);
}

#define rms_window_page_split_switch_gen(num) \
static void \
rms_window_page_split_switch_page_##num(RmsWindow *self) \
{ \
    gtk_notebook_set_current_page(self->page_split, num); \
} 

rms_window_page_split_switch_gen(0)
rms_window_page_split_switch_gen(1)

static void
rms_window_constructed(GObject *gobject){
    RmsWindow *self = RMS_WINDOW(gobject);

    /* 调用父类<加载完成后初始化>函数 */
    G_OBJECT_CLASS(rms_window_parent_class)->constructed(gobject);

    /* sidebar collapse */
    g_signal_connect_swapped(self->sidebar_show, "toggled",
                            G_CALLBACK(rms_window_sidebar_split_view_collapse),
                            self);

    /* sidebar button */
    g_signal_connect_swapped(self->train_mamage, "clicked",
                            G_CALLBACK(rms_window_page_split_switch_page_0),
                            self);

    g_signal_connect_swapped(self->people_mamage, "clicked",
                            G_CALLBACK(rms_window_page_split_switch_page_1),
                            self);

    g_signal_connect_swapped(self->search_info, "clicked",
                            G_CALLBACK(rms_window_page_split_switch_page_1),
                            self);

    g_signal_connect_swapped(self->save_info, "clicked",
                            G_CALLBACK(rms_window_page_split_switch_page_1),
                            self);

    g_signal_connect_swapped(self->load_info, "clicked",
                            G_CALLBACK(rms_window_page_split_switch_page_1),
                            self);
}

/* End */

typedef struct {
    GtkWidget* (*page_new)();
    gchar* label;
} page_bind;

static void
rms_window_init (RmsWindow *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));

    page_bind pages[2] = {
        {
            .page_new = rms_page_train_new,
            .label = "班次管理"
        },
        {
            .page_new = rms_page_people_new,
            .label = "乘客管理"
        }
    };

    GtkApplication* app = gtk_window_get_application(GTK_WINDOW(self));
    
    for(int i = 0; i < 2; i++){
        GtkWidget* page = pages[i].page_new();
        GtkWidget* label = gtk_label_new(pages[i].label);
        
        g_object_set(page, "root-window", app, NULL);
        self->page_data[i] = page;
        
        gtk_notebook_append_page(self->page_split, page, label);
    }
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
    GObjectClass *oclass = G_OBJECT_CLASS (klass);
    GtkWidgetClass *wclass = GTK_WIDGET_CLASS (klass);
    GtkWindowClass *winclass = GTK_WINDOW_CLASS (klass);

    gtk_widget_class_set_template_from_resource (wclass,
                                               "/rikki/tools/rms/rms-window.ui");

    gtk_widget_class_bind_template_child (wclass, RmsWindow, sidebar_show);
    gtk_widget_class_bind_template_child (wclass, RmsWindow, split_view);
    gtk_widget_class_bind_template_child (wclass, RmsWindow, train_mamage);
    gtk_widget_class_bind_template_child (wclass, RmsWindow, people_mamage);
    gtk_widget_class_bind_template_child (wclass, RmsWindow, search_info);
    gtk_widget_class_bind_template_child (wclass, RmsWindow, save_info);
    gtk_widget_class_bind_template_child (wclass, RmsWindow, load_info);
    gtk_widget_class_bind_template_child (wclass, RmsWindow, page_split);

    oclass->constructed = rms_window_constructed;
}


GtkWindow *
rms_window_new (GtkApplication *app){
    return g_object_new (RMS_TYPE_WINDOW, 
                        "application",app,
                        NULL);
}