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

#ifndef GLS2_SIGNAL_H
#define GLS2_SIGNAL_H

#if !defined (__GLS2_HEADER_INCLUDE__) && !defined (GLS2_COMPILATION)
#   error "Only <gls2/gls2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>

#include "gls2-handle.h"

G_BEGIN_DECLS

gboolean gls2_signal_send (Gls2Handle       *self,
                           const gchar      *uri,
                           const gchar      *payload);

gboolean gls2_signal_send_no_type_check (Gls2Handle         *self,
                                         const gchar        *uri,
                                         const gchar        *payload);

gboolean gls2_signal_call (Gls2Handle           *self,
                           const gchar          *category,
                           const gchar          *method,
                           LSFilterFunc         filter_func,
                           gpointer             user_data,
                           LSMessageToken       *ret_token);

gboolean gls2_signal_call_cancel (Gls2Handle        *self,
                                  LSMessageToken    token);

gboolean gls2_register_server_status_ex (Gls2Handle         *self,
                                         const gchar        *service_name,
                                         LSServerStatusFunc func,
                                         gpointer           user_data,
                                         gpointer           *cookie);

gboolean gls2_cancel_server_status (Gls2Handle      *self,
                                    gpointer        cookie);

G_END_DECLS

#endif
