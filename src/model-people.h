#pragma once

#include<gtk/gtk.h>

G_BEGIN_DECLS

#define MODEL_TYPE_PEOPLE (model_people_get_type())
G_DECLARE_FINAL_TYPE (ModelPeople, model_people, MODEL, PEOPLE, GObject)

enum ModelPeopleId
{
    MODEL_PEOPLE_NAME,
    MODEL_PEOPLE_TRAIN,
    MODEL_PEOPLE_TO,
    MODEL_PEOPLE_SIGN
};

/* public */

ModelPeople * 
model_people_new(const char *name,
                const char *train,
                const char *to,
                const char *sign);

const char* 
model_people_get_ById(ModelPeople* self,enum ModelPeopleId id);

G_END_DECLS