#include <adwaita.h>
#include "gtk_node.h"

#define getObj(type,name) type(gtk_builder_get_object(builder,name))

static void activate_cb (GtkApplication *app)
{
  // 利用 GtkBuilder 读取界面文件并构建图形元素
  GtkBuilder* builder = gtk_builder_new();
  gtk_builder_add_from_file(builder,"design/main.ui", NULL);

  // 获取 id: window 的对象，这是默认的根窗口的对象
  GObject* window = gtk_builder_get_object(builder,"window");
  // 设置窗口对象依赖附的 Application 对象
  gtk_window_set_application(GTK_WINDOW(window), app);

  show_sidebar_button = getObj(GTK_TOGGLE_BUTTON,"show_sidebar_button");
    split_view = getObj(ADW_OVERLAY_SPLIT_VIEW, "split_view");

      train_mamage = getObj(GTK_BUTTON, "train_mamage");
      people_mamage = getObj(GTK_BUTTON, "people_mamage");
      search_info = getObj(GTK_BUTTON, "search_info");
      save_info = getObj(GTK_BUTTON, "save_info");
      load_info = getObj(GTK_BUTTON, "load_info");

      page_split = getObj(GTK_NOTEBOOK, "page_split");
        page_1_col_view = getObj(GTK_COLUMN_VIEW, "page_1_col_view");
          page_1_col_view_dataflow = getObj(G_LIST_STORE, "page_1_col_view_dataflow");
        page_2_col_view = getObj(GTK_COLUMN_VIEW, "page_2_col_view");
          page_2_col_view_dataflow = getObj(G_LIST_STORE, "page_1_col_view_dataflow");

  // show_sidebar_button.toggled -> split_view
  g_signal_connect(show_sidebar_button, "toggled", G_CALLBACK(show_sidebar_button_toggled), NULL);

  g_signal_connect(train_mamage, "clicked", G_CALLBACK(train_mamage_button_clicked), NULL);
  g_signal_connect(people_mamage, "clicked", G_CALLBACK(people_mamage_button_clicked), NULL);
  g_signal_connect(search_info, "clicked", G_CALLBACK(search_info_button_clicked), NULL);
  g_signal_connect(save_info, "clicked", G_CALLBACK(save_info_button_clicked), NULL);
  g_signal_connect(load_info, "clicked", G_CALLBACK(load_info_button_clicked), NULL);

  // 将窗口对象的显示属性设置为真，使得窗口被展示出来
  gtk_widget_set_visible(GTK_WIDGET(window),TRUE);
  // 此时 builder 已经没有用处了，减少对象的引用计数（计数为0的时候对象自动结束生命周期）
  // 在本程序下，此处的用处在于避免手动管理内存，通过 引用计数 和 自动生命周期 在此处销毁对象
  g_object_unref(builder);
}

int main (int argc,char *argv[])
{
  // 创建实例
  AdwApplication* app;
  app = adw_application_new ("rikki.tools.Railway_Management_System", G_APPLICATION_DEFAULT_FLAGS);
  
  // 将窗口激活信号和激活函数连接
  g_signal_connect (app, "activate", G_CALLBACK (activate_cb), NULL);
  
  // 进入GTK主循环
  return g_application_run (G_APPLICATION (app), argc, argv);
}
