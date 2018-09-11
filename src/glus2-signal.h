/*
 * Copyright 2018 Yi-Soo An <yisooan@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GLUS2_SIGNAL_H
#define GLUS2_SIGNAL_H

#if !defined (__GLUS2_HEADER_INCLUDE__) && !defined (GLUS2_COMPILATION)
#   error "Only <glus2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>

#include "glus2-handle.h"

G_BEGIN_DECLS

gboolean glus2_signal_send (Glus2Handle      *self,
                            const gchar      *uri,
                            const gchar      *payload);

gboolean glus2_signal_send_no_type_check (Glus2Handle        *self,
                                          const gchar        *uri,
                                          const gchar        *payload);

gboolean glus2_signal_call (Glus2Handle          *self,
                            const gchar          *category,
                            const gchar          *method,
                            LSFilterFunc         filter_func,
                            gpointer             user_data,
                            LSMessageToken       *ret_token);

gboolean glus2_signal_call_cancel (Glus2Handle       *self,
                                   LSMessageToken    token);

gboolean glus2_register_server_status_ex (Glus2Handle        *self,
                                          const gchar        *service_name,
                                          LSServerStatusFunc func,
                                          gpointer           user_data,
                                          gpointer           *cookie);

gboolean glus2_cancel_server_status (Glus2Handle     *self,
                                     gpointer        cookie);

G_END_DECLS

#endif
