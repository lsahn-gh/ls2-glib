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
#include <gls2/gls2-handle-priv.h>

gboolean
gls2_signal_send (Gls2Handle       *self,
                  const gchar      *uri,
                  const gchar      *payload)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSSignalSend (priv->handler, uri, payload, priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_signal_send_no_type_check (Gls2Handle         *self,
                                const gchar        *uri,
                                const gchar        *payload)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSSignalSendNoTypecheck (priv->handler, uri, payload, priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_signal_call (Gls2Handle           *self,
                  const gchar          *category,
                  const gchar          *method,
                  LSFilterFunc         filter_func,
                  gpointer             user_data,
                  LSMessageToken       *ret_token)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSSignalCall (priv->handler,
                        category,
                        method, filter_func,
                        user_data,
                        ret_token,
                        priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_signal_call_cancel (Gls2Handle        *self,
                         LSMessageToken    token)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSSignalCallCancel (priv->handler, token, priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_register_server_status_ex (Gls2Handle         *self,
                                const gchar        *service_name,
                                LSServerStatusFunc func,
                                gpointer           user_data,
                                gpointer           *cookie)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSRegisterServerStatusEx (priv->handler,
                                    service_name,
                                    func,
                                    user_data,
                                    cookie,
                                    priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_cancel_server_status (Gls2Handle      *self,
                           gpointer        cookie)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSCancelServerStatus (priv->handler, cookie, priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}
