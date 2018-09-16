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

#ifndef GLS2_MESSAGE_H
#define GLS2_MESSAGE_H

#if !defined (__GLS2_HEADER_INCLUDE__) && !defined (GLS2_COMPILATION)
#   error "Only <gls2/gls2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>

#include "gls2-handle.h"

G_BEGIN_DECLS

gboolean gls2_message_respond (LSMessage    *msg,
                               const gchar  *reply);

gboolean gls2_message_respond_with_payload (LSMessage   *msg,
                                            LSPayload   *payload);

gboolean gls2_message_reply (Gls2Handle     *self,
                             LSMessage      *msg,
                             const gchar    *reply);

gboolean gls2_message_reply_err_bad_json (Gls2Handle     *self,
                                          LSMessage      *msg);

gboolean gls2_message_reply_err_invalid_params (Gls2Handle      *self,
                                                LSMessage       *msg);

gboolean gls2_message_reply_success (Gls2Handle         *self,
                                     LSMessage          *msg,
                                     const gchar        *payload);

/*
 * Part of inline functions.
 *
 * See https://stackoverflow.com/a/5229417
 */
static inline LSHandle *
gls2_message_get_connection (LSMessage *msg)
{
    return LSMessageGetConnection (msg);
}

static inline void
gls2_message_ref (LSMessage *msg)
{
    LSMessageRef (msg);
}

static inline void
gls2_message_unref (LSMessage *msg)
{
    LSMessageUnref (msg);
}

static inline gboolean
gls2_message_print_file (LSMessage *msg, FILE *out)
{
    return LSMessagePrint (msg, out);
}

static inline gboolean
gls2_message_print (LSMessage *msg)
{
    return LSMessagePrint (msg, stdout);
}

static inline gboolean
gls2_message_print_err (LSMessage *msg)
{
    return LSMessagePrint (msg, stderr);
}

static inline gboolean
gls2_message_is_err_from_hub (LSMessage *msg)
{
    return LSMessageIsHubErrorMessage (msg);
}

static inline const gchar *
gls2_message_get_unique_token (LSMessage *msg)
{
    return LSMessageGetUniqueToken (msg);
}

static inline const gchar *
gls2_message_get_kind (LSMessage *msg)
{
    return LSMessageGetKind (msg);
}

static inline const gchar *
gls2_message_get_application_id (LSMessage *msg)
{
    return LSMessageGetApplicationID (msg);
}

static inline const gchar *
gls2_message_get_sender (LSMessage *msg)
{
    return LSMessageGetSender (msg);
}

static inline const gchar *
gls2_message_get_sender_service_name (LSMessage *msg)
{
    return LSMessageGetSenderServiceName (msg);
}

static inline const gchar *
gls2_message_get_category (LSMessage *msg)
{
    return LSMessageGetCategory (msg);
}

static inline const gchar *
gls2_message_get_method (LSMessage *msg)
{
    return LSMessageGetMethod (msg);
}

static inline const gchar *
gls2_message_get_payload (LSMessage *msg)
{
    return LSMessageGetPayload (msg);
}

static inline LSPayload *
gls2_message_access_payload (LSMessage *msg)
{
    return LSMessageAccessPayload (msg);
}

static inline gboolean
gls2_message_is_subscription (LSMessage *msg)
{
    return LSMessageIsHubErrorMessage (msg);
}

static inline LSMessageToken
gls2_message_get_token (LSMessage *msg)
{
    return LSMessageGetToken (msg);
}

static inline LSMessageToken
gls2_message_get_response_token (LSMessage *msg)
{
    return LSMessageGetResponseToken (msg);
}

G_END_DECLS

#endif
