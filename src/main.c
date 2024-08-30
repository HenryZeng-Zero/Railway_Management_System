#include <adwaita.h>
#include "rms-application.h"

gchar* APPLICATION_ID = "rikki.tools.rms";
gchar* APPLICATION_NAME = "地铁管理系统";

int
main(int argc, char *argv[])
{
  gint status;
  g_autoptr (AdwApplication) app = NULL;

  app = rms_application_new(APPLICATION_ID,G_APPLICATION_DEFAULT_FLAGS);
  status = g_application_run(G_APPLICATION(app), argc, argv);

  return status;
}