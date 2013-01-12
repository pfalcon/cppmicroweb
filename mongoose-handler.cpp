#include <stdio.h>
#include <string.h>
#include "mongoose.h"
#include "microweb.hpp"
//using namespace std;

static void *callback(enum mg_event event,
                      struct mg_connection *conn) {
  const struct mg_request_info *request_info = mg_get_request_info(conn);

  if (event == MG_NEW_REQUEST) {
    string path(request_info->uri);
    cout << path << endl;
    ostringstream buf;
    route(buf, path);
#if 0
//    printf("%s\n", request_info->uri);
//    char content[1024];
    int content_length = snprintf(content, sizeof(content),
                                  "Hello from mongoose! Remote port: %d",
                                  request_info->remote_port);
#endif
    mg_printf(conn,
              "HTTP/1.1 200 OK\r\n"
              "Content-Type: text/plain\r\n"
              "Content-Length: %d\r\n"        // Always set Content-Length
              "\r\n"
              "%s",
              buf.str().size(), buf.str().c_str());
    // Mark as processed
    return (void*)"";
  } else {
    return NULL;
  }
}

int main(void) {
  struct mg_context *ctx;
  const char *options[] = {"listening_ports", "8080", NULL};

  ctx = mg_start(&callback, NULL, options);
  getchar();  // Wait until user hits "enter"
  mg_stop(ctx);

  return 0;
}
