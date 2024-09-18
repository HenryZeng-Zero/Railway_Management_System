#include "model-train.h"

struct _ModelTrain
{
    GObject parent_instance;
    char *name;
    char *from;
    char *to;
    char *begin_time;
    char *lasting_time;
    char *tickets;
    char *left_tickets;
    char *value;
};

struct _ModelTrainClass
{
    GObjectClass parent_class;
};

G_DEFINE_TYPE (ModelTrain, model_train, G_TYPE_OBJECT)

static void
model_train_init(ModelTrain *item)
{
}

static void
model_train_class_init(ModelTrainClass *class)
{
}

/* public */

ModelTrain * model_train_new()
{
    return g_object_new(MODEL_TYPE_TRAIN, NULL);
}

ModelTrain * model_train_new_with_values(const char *name,
                const char *from,
                const char *to,
                const char *begin_time,
                const char *lasting_time,
                const char *tickets,
                const char *left_tickets,
                const char *value)
{
    ModelTrain *item = g_object_new(MODEL_TYPE_TRAIN, NULL);
    item->name = g_strdup(name);
    item->from = g_strdup(from);
    item->to = g_strdup(to);
    item->begin_time = g_strdup(begin_time);
    item->lasting_time = g_strdup(lasting_time);
    item->tickets = g_strdup(tickets);
    item->left_tickets = g_strdup(left_tickets);
    item->value = g_strdup(value);
    return item;
}

const char* 
model_train_get_ById(ModelTrain* self,int id)
{
    switch (id) {
        case MODEL_TRAIN_NAME:
            return self->name;
        break;
        case MODEL_TRAIN_FROM:
            return self->from;
        break;
        case MODEL_TRAIN_TO:
            return self->to;
        break;
        case MODEL_TRAIN_BEGIN_TIME:
            return self->begin_time;
        break;
        case MODEL_TRAIN_LASTING_TIME:
            return self->lasting_time;
        break;
        case MODEL_TRAIN_TICKETS:
            return self->tickets;
        break;
        case MODEL_TRAIN_LEFT_TICKETS:
            return self->left_tickets;
        break;
        case MODEL_TRAIN_VALUE:
            return self->value;
        break;
    }
    return NULL;
}

void
model_train_set_ById(ModelTrain* self,int id,const char* value)
{
    switch (id) {
        case MODEL_TRAIN_NAME:
            self->name = g_strdup(value);
        break;
        case MODEL_TRAIN_FROM:
            self->from = g_strdup(value);
        break;
        case MODEL_TRAIN_TO:
            self->to = g_strdup(value);
        break;
        case MODEL_TRAIN_BEGIN_TIME:
            self->begin_time = g_strdup(value);
        break;
        case MODEL_TRAIN_LASTING_TIME:
            self->lasting_time = g_strdup(value);
        break;
        case MODEL_TRAIN_TICKETS:
            self->tickets = g_strdup(value);
        break;
        case MODEL_TRAIN_LEFT_TICKETS:
            self->left_tickets = g_strdup(value);
        break;
        case MODEL_TRAIN_VALUE:
            self->value = g_strdup(value);
        break;
    }
}