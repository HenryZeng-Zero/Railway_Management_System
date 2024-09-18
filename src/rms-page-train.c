#include "rms-page-train.h"
#include "model-train.h"
#include "rms-col-view-helper.h"

#define GtkColumnViewColumnN(n) GtkColumnViewColumn* col##n;
struct _RmsPageTrain
{
    GtkBox parent_type;

    GtkWindow* root_window;

    GtkButton* add_data;
    GtkButton* set_data;
    GtkButton* del_data;

    GtkColumnView* column_view;
    GListModel *model;
    GtkSingleSelection *selection;
    define_bind_funcList(bind,8)
};

G_DEFINE_TYPE (RmsPageTrain, rms_page_train, GTK_TYPE_BOX)

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
    RmsPageTrain *self = RMS_PAGE_TRAIN(object);

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
    RmsPageTrain *self = RMS_PAGE_TRAIN(object);

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
rms_page_train_add_data_choose(GObject* dialog, GAsyncResult* result,gpointer user_data)
{
    RmsPageTrain* self = RMS_PAGE_TRAIN(user_data);
    GtkEntry *entry;
    const char* response;
    GtkEntryBuffer* buffer;
    char* str;
    ModelTrain* item;
    char* str_tmp;

    response = adw_alert_dialog_choose_finish(ADW_ALERT_DIALOG(dialog), result);
    entry = GTK_ENTRY(adw_alert_dialog_get_extra_child(ADW_ALERT_DIALOG(dialog)));
    buffer = gtk_entry_get_buffer(entry);
    str = g_strdup(gtk_entry_buffer_get_text(buffer));

    if(strcmp(response, "select") == 0){
        str_tmp = strtok(str, ",");
        item = model_train_new();
        int count = 0;

        do {
            model_train_set_ById(item, count, str_tmp);
            str_tmp = strtok(NULL, ",");
            count++;
        }while (str_tmp);

        if (count == 8) {
            g_list_store_append(G_LIST_STORE(self->model), item);
        }
    } 
}

static void
rms_page_train_add_data(GtkWidget *self)
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
                           rms_page_train_add_data_choose, self);
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

bind_type_cb(model_train_get_ById,MODEL_TRAIN,MODEL_TRAIN_NAME)
bind_type_cb(model_train_get_ById,MODEL_TRAIN,MODEL_TRAIN_FROM)
bind_type_cb(model_train_get_ById,MODEL_TRAIN,MODEL_TRAIN_TO)
bind_type_cb(model_train_get_ById,MODEL_TRAIN,MODEL_TRAIN_BEGIN_TIME)
bind_type_cb(model_train_get_ById,MODEL_TRAIN,MODEL_TRAIN_LASTING_TIME)
bind_type_cb(model_train_get_ById,MODEL_TRAIN,MODEL_TRAIN_TICKETS)
bind_type_cb(model_train_get_ById,MODEL_TRAIN,MODEL_TRAIN_LEFT_TICKETS)
bind_type_cb(model_train_get_ById,MODEL_TRAIN,MODEL_TRAIN_VALUE)

static void
rms_page_train_del_data(RmsPageTrain* self)
{
    gint id = gtk_single_selection_get_selected(self->selection);
    if(id > -1){
        // id = -1 -> No Selection
        g_list_store_remove(G_LIST_STORE(self->model), id);
    }
}

static void
rms_page_train_constructed(GObject *gobject){
    RmsPageTrain *self = RMS_PAGE_TRAIN(gobject);

    /* 调用父类<加载完成后初始化>函数 */
    G_OBJECT_CLASS(rms_page_train_parent_class)->constructed(gobject);

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

/* End */

static void
rms_page_train_init (RmsPageTrain *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));

    link_type_cb(self->bind, MODEL_TRAIN_NAME)
    link_type_cb(self->bind, MODEL_TRAIN_FROM)
    link_type_cb(self->bind, MODEL_TRAIN_TO)
    link_type_cb(self->bind, MODEL_TRAIN_BEGIN_TIME)
    link_type_cb(self->bind, MODEL_TRAIN_LASTING_TIME)
    link_type_cb(self->bind, MODEL_TRAIN_TICKETS)
    link_type_cb(self->bind, MODEL_TRAIN_LEFT_TICKETS)
    link_type_cb(self->bind, MODEL_TRAIN_VALUE)

    g_signal_connect_swapped(self->del_data, "clicked", G_CALLBACK(rms_page_train_del_data),self);
    g_signal_connect_swapped(self->add_data, "clicked", G_CALLBACK(rms_page_train_add_data),self);
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
    GParamFlags default_flags = G_PARAM_READWRITE | 
                                G_PARAM_STATIC_STRINGS;

    oclass->constructed = rms_page_train_constructed;
    oclass->dispose = rms_page_train_dispose;

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
                                               "/rikki/tools/rms/rms-page-train.ui");

    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, add_data);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, set_data);
    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, del_data);

    gtk_widget_class_bind_template_child (wclass, RmsPageTrain, column_view);
}

/* public method */

GtkWidget *
rms_page_train_new()
{
    return g_object_new (RMS_TYPE_PAGE_TRAIN,NULL);
}

void
rms_page_train_set_root_window(RmsPageTrain *self, GtkWindow *root_window)
{
    self->root_window = root_window;
}

GtkWindow*
rms_page_train_get_root_window(RmsPageTrain *self)
{
    return self->root_window;
}

void rms_page_train_save(RmsPageTrain *self)
{
    FILE *fp;
    fp = fopen("train.txt","w");
    if(fp==NULL){
        return;
    }

    for (int i = 0; i < g_list_model_get_n_items(self->model); i++) {
        ModelTrain *item = g_list_model_get_item(self->model, i);
        fprintf(fp,"%s,%s,%s,%s,%s,%s,%s,%s\n", model_train_get_ById(item, 0),
                                                model_train_get_ById(item, 1),
                                                model_train_get_ById(item, 2),
                                                model_train_get_ById(item, 3),
                                                model_train_get_ById(item, 4),
                                                model_train_get_ById(item, 5),
                                                model_train_get_ById(item, 6),
                                                model_train_get_ById(item, 7));
    }

    fclose(fp);
}
void rms_page_train_load(RmsPageTrain *self)
{
    FILE *fp;
    char buffer[500];
    char *str_tmp;
    char *status;
    ModelTrain* item;
    
    fp = fopen("train.txt","r");
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
        item = model_train_new();
        int count = 0;

        do {
            int last = strlen(str_tmp) - 1;
            if(str_tmp[last] == '\n') {
                str_tmp[last] = '\0';
            }

            model_train_set_ById(item, count, str_tmp);
            str_tmp = strtok(NULL, ",");
            
            count++;
        }while (str_tmp);

        if (count == 8) {
            g_list_store_append(G_LIST_STORE(self->model), item);
        }
    }

    fclose(fp);
}