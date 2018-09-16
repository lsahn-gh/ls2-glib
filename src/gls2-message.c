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

#include <gls2/gls2.h>

gboolean
gls2_message_respond (LSMessage    *msg,
                      const gchar  *reply)
{
    LSError error;
    gboolean ret;

    LSErrorInit (&error);

    if ( !(ret = LSMessageRespond (msg, reply, &error)) )
        gls2_err_log_if_set (&error);

    return ret;
}

gboolean
gls2_message_respond_with_payload (LSMessage   *msg,
                                   LSPayload   *payload)
{
    LSError error;
    gboolean ret;

    LSErrorInit (&error);

    if ( !(ret = LSMessageRespondWithPayload (msg, payload, &error)) )
        gls2_err_log_if_set (&error);

    return ret;
}

gboolean
gls2_message_reply (Gls2Handle     *self,
                    LSMessage      *msg,
                    const gchar    *reply)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    if ( !(ret = LSMessageReply (priv->handler, msg, reply, priv->lserror)) )
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_message_reply_err_bad_json (Gls2Handle    *self,
                                 LSMessage     *msg)
{
    gboolean ret;

    const gchar *reply = " \
        {                                           \
            \"returnValue\": false,                 \
            \"errorText\"  : \"Malformed json.\"    \
        }";

    return gls2_message_reply (self, msg, reply);
}

gboolean
gls2_message_reply_err_invalid_params (Gls2Handle      *self,
                                       LSMessage       *msg)
{
    gboolean ret;

    const gchar *reply = " \
        {                                             \
            \"returnValue\": false,                   \
            \"errorText\"  : \"Invalid parameters.\"  \
        }";

    return gls2_message_reply (self, msg, reply);
}

gboolean
gls2_message_reply_success (Gls2Handle         *self,
                            LSMessage          *msg,
                            const gchar        *payload)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

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
        gls2_err_log_if_set (priv->lserror);

    return ret;
}
