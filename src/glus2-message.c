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

#include <glus2/glus2.h>

gboolean
glus2_message_respond (LSMessage    *msg,
                       const gchar  *reply)
{
    LSError error;
    gboolean ret;

    LSErrorInit (&error);

    if ( !(ret = LSMessageRespond (msg, reply, &error)) )
        glus2_err_log_if_set (&error);

    return ret;
}

gboolean
glus2_message_respond_with_payload (LSMessage   *msg,
                                    LSPayload   *payload)
{
    LSError error;
    gboolean ret;

    LSErrorInit (&error);

    if ( !(ret = LSMessageRespondWithPayload (msg, payload, &error)) )
        glus2_err_log_if_set (&error);

    return ret;
}

gboolean
glus2_message_reply (Glus2Handle    *self,
                     LSMessage      *msg,
                     const gchar    *reply)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    if ( !(ret = LSMessageReply (priv->handler, msg, reply, priv->lserror)) )
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_message_reply_err_bad_json (Glus2Handle   *self,
                                  LSMessage     *msg)
{
    gboolean ret;

    const gchar *reply = " \
        {                                           \
            \"returnValue\": false,                 \
            \"errorText\"  : \"Malformed json.\"    \
        }";

    return glus2_message_reply (self, msg, reply);
}

gboolean
glus2_message_reply_err_invalid_params (Glus2Handle     *self,
                                        LSMessage       *msg)
{
    gboolean ret;

    const gchar *reply = " \
        {                                             \
            \"returnValue\": false,                   \
            \"errorText\"  : \"Invalid parameters.\"  \
        }";

    return glus2_message_reply (self, msg, reply);
}

gboolean
glus2_message_reply_success (Glus2Handle        *self,
                             LSMessage          *msg,
                             const gchar        *payload)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    if (payload == NULL) {
        ret = LSMessageReply (priv->handler,
                              msg,
                              "{\"returnValue\": true}",
                              priv->lserror);
    } else {
        ret = LSMessageReply (priv->handler,
                              msg,
                              payload,
                              priv->lserror);
    }

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}
