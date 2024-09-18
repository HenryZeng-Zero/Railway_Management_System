#pragma once

#include<gtk/gtk.h>

G_BEGIN_DECLS

#define MODEL_TYPE_TRAIN (model_train_get_type())
G_DECLARE_FINAL_TYPE (ModelTrain, model_train, MODEL, TRAIN, GObject)

enum ModelTrainId
{
    MODEL_TRAIN_NAME,
    MODEL_TRAIN_FROM,
    MODEL_TRAIN_TO,
    MODEL_TRAIN_BEGIN_TIME,
    MODEL_TRAIN_LASTING_TIME,
    MODEL_TRAIN_TICKETS,
    MODEL_TRAIN_LEFT_TICKETS,
    MODEL_TRAIN_VALUE,
};

/* public */

ModelTrain * 
model_train_new();

ModelTrain * model_train_new_with_values(const char *name,
                const char *from,
                const char *to,
                const char *begin_time,
                const char *lasting_time,
                const char *tickets,
                const char *left_tickets,
                const char *value);

const char* 
model_train_get_ById(ModelTrain* self,int id);

void
model_train_set_ById(ModelTrain* self,int id,const char* value);

G_END_DECLS