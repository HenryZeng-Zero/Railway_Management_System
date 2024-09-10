#include "rms-page-people.h"
#include "model-people.h"
#include "rms-column-view-helper.h"

struct _RmsPagePeople
{
    GtkBox parent_type;

    GtkWindow* root_window;

    GtkButton* add_data;
    GtkButton* set_data;
    GtkButton* del_data;

    
};

/* part: rms_column_view bind func */

rms_column_view_bind_func_new(rms_col_get_name, MODEL_PEOPLE_NAME, model_people_get_ById, MODEL_PEOPLE)
rms_column_view_bind_func_new(rms_col_get_train, MODEL_PEOPLE_TRAIN, model_people_get_ById, MODEL_PEOPLE)
rms_column_view_bind_func_new(rms_col_get_to, MODEL_PEOPLE_TO, model_people_get_ById, MODEL_PEOPLE)
rms_column_view_bind_func_new(rms_col_get_sign, MODEL_PEOPLE_SIGN, model_people_get_ById, MODEL_PEOPLE)


G_DEFINE_TYPE (RmsPagePeople, rms_page_people, GTK_TYPE_BOX)

/* part: properities */

enum properity_type
{
    PROP_ROOT_WINDOW = 1,
    N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES];

static void
rms_page_train_set_property(GObject *object, 
                            guint property_id, 
                            const GValue *value, 
                            GParamSpec *pspec)
{
    RmsPagePeople *self = RMS_PAGE_PEOPLE(object);

    switch (property_id)
    {
        case PROP_ROOT_WINDOW:
            self->root_window = g_value_get_pointer(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void
rms_page_train_get_property(GObject *object, 
                            guint property_id, 
                            GValue *value,
                            GParamSpec *pspec)
{
    RmsPagePeople *self = RMS_PAGE_PEOPLE(object);

    switch (property_id)
    {
        case PROP_ROOT_WINDOW:
            g_value_set_pointer(value,self->root_window);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

/* test */
static void
rms_page_people_messgb(GtkWindow *parent)
{
    GtkWidget *dialog;

    dialog = adw_message_dialog_new (parent, "Replace File?", NULL);

    gtk_window_set_transient_for(GTK_WINDOW(dialog), parent);

    adw_message_dialog_format_body (ADW_MESSAGE_DIALOG (dialog),
                                    "A file named “%s” already exists. Do you want to replace it?",
                                    "ssssss");

    adw_message_dialog_add_responses (ADW_MESSAGE_DIALOG (dialog),
                                    "cancel",  "_Cancel",
                                    "replace", "_Replace",
                                    NULL);

    adw_message_dialog_set_response_appearance (ADW_MESSAGE_DIALOG (dialog), "replace", ADW_RESPONSE_DESTRUCTIVE);

    adw_message_dialog_set_default_response (ADW_MESSAGE_DIALOG (dialog), "cancel");
    adw_message_dialog_set_close_response (ADW_MESSAGE_DIALOG (dialog), "cancel");

    gtk_window_present (GTK_WINDOW (dialog));
}


/* part: constructed */


GListModel * create_capital_model(void)
{
    GListStore *store = g_list_store_new(G_TYPE_OBJECT);
    g_list_store_append(store, model_people_new("Washington,D.C.","USA","1790","712,816"));
    g_list_store_append(store, model_people_new("London","Britain","43","8,799,800"));
    g_list_store_append(store, model_people_new("Paris","France","3rd c. BC","2,161,000"));
    g_list_store_append(store, model_people_new("Berlin","Germany","13th century","3,850,809"));
    g_list_store_append(store, model_people_new("Rome","Italy","753 BC","2,860,009"));
    return G_LIST_MODEL(store);
}

static void 
setup_cb(GtkSignalListItemFactory *factory,GObject *listitem)
{
    GtkWidget *label =gtk_label_new(NULL);
    gtk_list_item_set_child(GTK_LIST_ITEM(listitem),label);
}

static void
rms_page_people_constructed(GObject *gobject){
    RmsPagePeople *self = RMS_PAGE_PEOPLE(gobject);

    /* 调用父类<加载完成后初始化>函数 */
    G_OBJECT_CLASS(rms_page_people_parent_class)->constructed(gobject);

    GListModel *model;
    GtkSingleSelection *selection;

    model = create_capital_model();
    selection = gtk_single_selection_new(G_LIST_MODEL(model));
    gtk_single_selection_set_autoselect(selection,TRUE);

    gtk_column_view_set_model(self->column_view, GTK_SELECTION_MODEL(selection));

    

    for (int i = 0; i<4; i++) {
        g_print("pointer: %p\n",self->columns.col[i]);
        GtkColumnViewColumn* col_item = rms_column_view_get_col(self,columns,i);
        GtkListItemFactory* factory = gtk_column_view_column_get_factory(col_item);

        g_signal_connect(factory, "setup", G_CALLBACK(setup_cb),NULL);
        g_signal_connect(factory, "bind", G_CALLBACK(rms_column_view_get_func(self, columns, i)),NULL);
    }

}

/* End */

static void
rms_page_people_init (RmsPagePeople *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));

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
    GParamFlags default_flags = G_PARAM_READWRITE | 
                                G_PARAM_STATIC_STRINGS |
                                G_PARAM_EXPLICIT_NOTIFY;

    oclass->constructed = rms_page_people_constructed;
    oclass->dispose = rms_page_people_dispose;

    oclass->set_property = rms_page_train_set_property;
    oclass->get_property = rms_page_train_get_property;

    /* 注册属性 */

    properties[PROP_ROOT_WINDOW] = g_param_spec_string(
        "root-window",
        "root window object",
        "The root window of application",
        NULL,
        default_flags
    );

    g_object_class_install_properties(oclass, N_PROPERTIES, properties);

    /* end */

    gtk_widget_class_set_template_from_resource (wclass,
                                               "/rikki/tools/rms/rms-page-people.ui");

    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, add_data);
    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, set_data);
    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, del_data);

}

/* public method */

GtkWidget *
rms_page_people_new()
{
    return g_object_new (RMS_TYPE_PAGE_PEOPLE,NULL);
}

void
rms_page_people_set_root_window(RmsPagePeople *self, GtkWindow *root_window)
{
    self->root_window = root_window;
}

GtkWindow*
rms_page_people_get_root_window(RmsPagePeople *self)
{
    return self->root_window;
}