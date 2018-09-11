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
glus2_call_add_cancel_notification (Glus2Handle                 *self,
                                    LSCancelNotificationFunc    fptr,
                                    gpointer                    user_data)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    ret = LSCallCancelNotificationAdd (priv->handler,
                                       fptr,
                                       user_data,
                                       priv->lserror);

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_call_remove_cancel_notification (Glus2Handle              *self,
                                       LSCancelNotificationFunc fptr,
                                       gpointer                 user_data)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    ret = LSCallCancelNotificationRemove (priv->handler,
                                          fptr,
                                          user_data,
                                          priv->lserror);

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_call (Glus2Handle     *self,
            const gchar     *uri,
            const gchar     *payload,
            LSFilterFunc    callback,
            gpointer        user_data,
            LSMessageToken  *ret_token,
            gboolean        one_reply)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    if (one_reply) {
        ret = LSCallOneReply (priv->handler,
                              uri,
                              payload,
                              callback,
                              user_data,
                              ret_token,
                              priv->lserror);
    } else {
        ret = LSCall (priv->handler,
                      uri,
                      payload,
                      callback,
                      user_data,
                      ret_token,
                      priv->lserror);
    }
    
    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_call_from_application (Glus2Handle        *self,
                             const gchar        *uri,
                             const gchar        *payload,
                             const gchar        *app_id,
                             LSFilterFunc       callback,
                             gpointer           user_data,
                             LSMessageToken     *ret_token,
                             gboolean           one_reply)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    if (one_reply) {
        ret = LSCallFromApplicationOneReply (priv->handler,
                                             uri,
                                             payload,
                                             app_id,
                                             callback,
                                             user_data,
                                             ret_token,
                                             priv->lserror);
    } else {
        ret = LSCallFromApplication (priv->handler,
                                     uri,
                                     payload,
                                     app_id,
                                     callback,
                                     user_data,
                                     ret_token,
                                     priv->lserror);
    }

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_call_cancel (Glus2Handle      *self,
                   LSMessageToken   token)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    if ( !(ret = LSCallCancel (priv->handler, token, priv->lserror)) )
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_call_set_timeout (Glus2Handle     *self,
                        LSMessageToken  token,
                        gint            timeout_ms)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    ret = LSCallSetTimeout (priv->handler,
                            token,
                            timeout_ms,
                            priv->lserror);

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_call_set_timeout_seconds (Glus2Handle       *self,
                                LSMessageToken    token,
                                gint              timeout_sec)
{
    return glus2_call_set_timeout (self, token, timeout_sec * 1000);
}

gboolean
glus2_call_set_timeout_minutes (Glus2Handle       *self,
                                LSMessageToken    token,
                                gint              timeout_min)
{
    return glus2_call_set_timeout (self, token, timeout_min * 1000 * 60);
}
