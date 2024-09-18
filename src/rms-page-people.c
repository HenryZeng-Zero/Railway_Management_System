#include "rms-page-people.h"
#include "model-people.h"
#include "rms-col-view-helper.h"

struct _RmsPagePeople
{
    GtkBox parent_type;

    GtkWindow* root_window;

    GtkButton* add_data;
    GtkButton* set_data;
    GtkButton* del_data;

    GtkColumnView* column_view;
    GListModel *model;
    GtkSingleSelection *selection;
    define_bind_funcList(bind,4)

};

G_DEFINE_TYPE (RmsPagePeople, rms_page_people, GTK_TYPE_BOX)

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

static void
rms_page_people_add_data_choose(GObject* dialog, GAsyncResult* result,gpointer user_data)
{
    RmsPagePeople* self = RMS_PAGE_PEOPLE(user_data);
    GtkEntry *entry;
    const char* response;
    GtkEntryBuffer* buffer;
    char* str;
    ModelPeople* item;
    char* str_tmp;

    response = adw_alert_dialog_choose_finish(ADW_ALERT_DIALOG(dialog), result);
    entry = GTK_ENTRY(adw_alert_dialog_get_extra_child(ADW_ALERT_DIALOG(dialog)));
    buffer = gtk_entry_get_buffer(entry);
    str = g_strdup(gtk_entry_buffer_get_text(buffer));

    if(strcmp(response, "select") == 0){
        str_tmp = strtok(str, ",");
        item = model_people_new();
        int count = 0;

        do {
            model_people_set_ById(item, count, str_tmp);
            str_tmp = strtok(NULL, ",");
            count++;
        }while (str_tmp);

        if (count == 4) {
            g_list_store_append(G_LIST_STORE(self->model), item);
        }
    } 
}

static void
rms_page_people_add_data(GtkWidget *self)
{
    AdwDialog *dialog;
    GtkEntry *entry;
    
    dialog = adw_alert_dialog_new("增加记录", "在如下位置填写记录，使用逗号隔开。");
    entry = GTK_ENTRY(gtk_entry_new());

    adw_alert_dialog_set_extra_child(ADW_ALERT_DIALOG(dialog), GTK_WIDGET(entry));

    adw_alert_dialog_add_response(ADW_ALERT_DIALOG(dialog), "cancel", "取消");
    adw_alert_dialog_add_response(ADW_ALERT_DIALOG(dialog), "select", "确认");

    adw_alert_dialog_set_close_response (ADW_ALERT_DIALOG (dialog), "cancel");
    adw_alert_dialog_set_response_appearance( ADW_ALERT_DIALOG(dialog), 
                                            "select",ADW_RESPONSE_SUGGESTED);

    adw_alert_dialog_choose(ADW_ALERT_DIALOG(dialog), 
                            GTK_WIDGET(window_main), 
                            NULL, 
                           rms_page_people_add_data_choose, self);
}

static GListModel*
rms_create_model(void)
{
    GListStore *store = g_list_store_new(G_TYPE_OBJECT);

    return G_LIST_MODEL(store);
}

static void 
setup_cb(GtkSignalListItemFactory *factory,GObject *listitem)
{
    GtkWidget *label =gtk_label_new(NULL);
    gtk_list_item_set_child(GTK_LIST_ITEM(listitem),label);
}

bind_type_cb(model_people_get_ById,MODEL_PEOPLE,MODEL_PEOPLE_NAME)
bind_type_cb(model_people_get_ById,MODEL_PEOPLE,MODEL_PEOPLE_TRAIN)
bind_type_cb(model_people_get_ById,MODEL_PEOPLE,MODEL_PEOPLE_TO)
bind_type_cb(model_people_get_ById,MODEL_PEOPLE,MODEL_PEOPLE_SIGN)


static void
rms_page_people_del_data(RmsPagePeople* self)
{
    gint id = gtk_single_selection_get_selected(self->selection);
    if(id > -1){
        // id = -1 -> No Selection
        g_list_store_remove(G_LIST_STORE(self->model), id);
    }
}

static void
rms_page_people_init (RmsPagePeople *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
    link_type_cb(self->bind, MODEL_PEOPLE_NAME)
    link_type_cb(self->bind, MODEL_PEOPLE_TRAIN)
    link_type_cb(self->bind, MODEL_PEOPLE_TO)
    link_type_cb(self->bind, MODEL_PEOPLE_SIGN)

    g_signal_connect_swapped(self->del_data, "clicked", G_CALLBACK(rms_page_people_del_data),self);
    g_signal_connect_swapped(self->add_data, "clicked", G_CALLBACK(rms_page_people_add_data),self);
    
}

static void
rms_page_people_constructed(GObject *gobject){
    RmsPagePeople *self = RMS_PAGE_PEOPLE(gobject);

    /* 调用父类<加载完成后初始化>函数 */
    G_OBJECT_CLASS(rms_page_people_parent_class)->constructed(gobject);

    self->model = rms_create_model();
    self->selection = gtk_single_selection_new(G_LIST_MODEL(self->model));
    gtk_single_selection_set_autoselect(self->selection,TRUE);

    gtk_column_view_set_model(self->column_view, GTK_SELECTION_MODEL(self->selection));

    GListModel *cols = gtk_column_view_get_columns(self->column_view);

    for (guint i = 0; i < g_list_model_get_n_items (cols); i++)
    {
        g_autoptr (GtkColumnViewColumn) col = NULL;
        GtkListItemFactory *factory;

        col = g_list_model_get_item (cols, i);
        factory = gtk_column_view_column_get_factory (col);
        g_signal_connect(factory, "setup", G_CALLBACK(setup_cb),NULL);
        g_signal_connect_swapped(factory, "bind", G_CALLBACK(get_bind(self->bind, i)),self->root_window);
    }

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
                                G_PARAM_STATIC_STRINGS;

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

    gtk_widget_class_bind_template_child (wclass, RmsPagePeople, column_view);
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

void rms_page_people_save(RmsPagePeople *self)
{
    FILE *fp;
    fp = fopen("people.txt","w");
    if(fp==NULL){
        return;
    }

    for (int i = 0; i < g_list_model_get_n_items(self->model); i++) {
        ModelPeople *item = g_list_model_get_item(self->model, i);
        fprintf(fp,"%s,%s,%s,%s\n", model_people_get_ById(item, 0),
                                                model_people_get_ById(item, 1),
                                                model_people_get_ById(item, 2),
                                                model_people_get_ById(item, 3));
    }

    fclose(fp);
}
void rms_page_people_load(RmsPagePeople *self)
{
    FILE *fp;
    char buffer[500];
    char *str_tmp;
    char *status;
    ModelPeople* item;
    
    fp = fopen("people.txt","r");
    if(fp==NULL){
        return;
    }

    g_list_store_remove_all(G_LIST_STORE(self->model));

    while (!feof(fp)) {
        status = fgets(buffer, 500, fp);

        if (status == NULL) {
            return;
        }

        str_tmp = strtok(buffer, ",");
        item = model_people_new();
        int count = 0;

        do {
            int last = strlen(str_tmp) - 1;
            if(str_tmp[last] == '\n') {
                str_tmp[last] = '\0';
            }

            model_people_set_ById(item, count, str_tmp);
            str_tmp = strtok(NULL, ",");
            
            count++;
        }while (str_tmp);

        if (count == 4) {
            g_list_store_append(G_LIST_STORE(self->model), item);
        }
    }

    fclose(fp);
}