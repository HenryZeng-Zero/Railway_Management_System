#include "model-people.h"

struct _ModelPeople
{
    GObject parent_instance;
    char *name;
    char *train;
    char *to;
    char *sign;
};

struct _ModelPeopleClass
{
    GObjectClass parent_class;
};

G_DEFINE_TYPE (ModelPeople, model_people, G_TYPE_OBJECT)

static void
model_people_init(ModelPeople *item)
{
}

static void
model_people_class_init(ModelPeopleClass *class)
{
}

/* public */

ModelPeople * model_people_new(const char *name,
                const char *train,
                const char *to,
                const char *sign)
{
    ModelPeople  *item = g_object_new(MODEL_TYPE_PEOPLE, NULL);
    item->name = g_strdup(name);
    item->train = g_strdup(train);
    item->to = g_strdup(to);
    item->sign = g_strdup(sign);
    return item;
}

const char* 
model_people_get_ById(ModelPeople* self,enum ModelPeopleId id)
{
    switch (id) {
        case MODEL_PEOPLE_NAME:
            return self->name;
        break;
        case MODEL_PEOPLE_TRAIN:
            return self->train;
        break;
        case MODEL_PEOPLE_TO:
            return self->to;
        break;
        case MODEL_PEOPLE_SIGN:
            return self->sign;
        break;
    }
}