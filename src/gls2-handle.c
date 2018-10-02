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

G_DEFINE_TYPE_WITH_PRIVATE (Gls2Handle, gls2_handle, G_TYPE_OBJECT)

enum
{
    PROP_0,
    PROP_SERVICE_NAME,
    PROP_APP_ID,
    LAST_PROP
};


/* --- GObject --- */
static void
gls2_handle_dispose (GObject *parent)
{
    /* Drop all the references of inheriting GObject 
     * 
     * should call g_object_unref and be careful calling it.
     * dispose could be called several times.
     * must check the instances for g_object_unref 
     * what if it is already called.
     * 
     * See https://developer.gnome.org/gobject/stable/howto-gobject-destruction.html
     */

    G_OBJECT_CLASS (gls2_handle_parent_class)->dispose (parent);
}

static void
gls2_handle_finalize (GObject *parent)
{
    Gls2HandlePrivate *priv = GLS2_HANDLE (parent)->priv;
    bool ret;

    /* Free if lserror was set somewhere */
    if (LSErrorIsSet (priv->lserror))
        LSErrorFree (priv->lserror);

    /* Unregister LSHandle */
    if ( !(ret = LSUnregister (priv->handler, priv->lserror)) ) {
        gls2_err_log_if_set (priv->lserror);
    }

    g_free (priv->lserror);
    priv->lserror = NULL;

    g_free (priv->service_name);
    g_free (priv->app_id);

    G_OBJECT_CLASS (gls2_handle_parent_class)->finalize (parent);
}

static void
gls2_handle_get_property (GObject      *object,
                          guint        prop_id,
                          GValue       *value,
                          GParamSpec   *pspec)
{
    Gls2HandlePrivate *priv = GLS2_HANDLE (object)->priv;

    switch (prop_id)
    {
        case PROP_SERVICE_NAME:
            g_value_set_string (value, priv->service_name);
            break;

        case PROP_APP_ID:
            g_value_set_string (value, priv->app_id);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
gls2_handle_set_property (GObject      *object,
                          guint        prop_id,
                          const GValue *value,
                          GParamSpec   *pspec)
{
    Gls2HandlePrivate *priv = GLS2_HANDLE (object)->priv;

    switch (prop_id)
    {
        case PROP_SERVICE_NAME:
            g_free (priv->service_name);
            priv->service_name = g_value_dup_string (value);
            break;

        case PROP_APP_ID:
            g_free (priv->app_id);
            priv->app_id = g_value_dup_string (value);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
gls2_handle_constructed (GObject *parent)
{
    Gls2HandlePrivate *priv = GLS2_HANDLE (parent)->priv;
    LSError *error;

    G_OBJECT_CLASS (gls2_handle_parent_class)->constructed (parent);

    /* Initialize LSError */
    if ( (error = g_try_new (LSError, 1)) != NULL ) {
        LSErrorInit (error);
        priv->lserror = error;
    }

    /* Register LSHandle */
    if ( !LSRegister(priv->service_name, &priv->handler, error) ) {
        gls2_err_log_if_set (error);
    }
}

static void
gls2_handle_class_init (Gls2HandleClass *klass)
{
    GObjectClass *object_klass = G_OBJECT_CLASS (klass);

    object_klass->dispose = gls2_handle_dispose;
    object_klass->finalize = gls2_handle_finalize;
    object_klass->get_property = gls2_handle_get_property;
    object_klass->set_property = gls2_handle_set_property;
    object_klass->constructed = gls2_handle_constructed;

    /* Install gobject properties */
    g_object_class_install_property (
        object_klass,
        PROP_SERVICE_NAME,
        g_param_spec_string ("service-name",
                             "Service name being registered",
                             "The service name that will be registered",
                             NULL,
                             G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE));

    g_object_class_install_property (
        object_klass,
        PROP_APP_ID,
        g_param_spec_string ("app-id",
                             "App name being registered",
                             "The app name that will be registered",
                             NULL,
                             G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE));

    /* Install gobject signals */
}

static void
gls2_handle_init (Gls2Handle *self)
{
    Gls2HandlePrivate *priv = gls2_handle_get_instance_private (self);

    self->priv = priv;
}

Gls2Handle *
gls2_handle_new (const gchar *service_name)
{
    return GLS2_HANDLE (g_object_new (GLS2_TYPE_HANDLE,
                                      "service-name", service_name,
                                      "app-id", NULL,
                                      NULL));
}

Gls2Handle *
gls2_handle_new_with_app_id (const gchar *service_name,
                             const gchar *app_id)
{
    return GLS2_HANDLE (g_object_new (GLS2_TYPE_HANDLE,
                                      "service-name", service_name,
                                      "app-id", app_id,
                                      NULL));
}

/*!
 * @brief Get LSHandle
 * 
 * Use it only for customizing your service.
 * 
 * DO NOT unregister the returned data.
 * It should be unregistered at finalize of itself.
 * 
 * @param  self: Gls2Handle instance
 * @return Pointer to LSHandle on success, or NULL on failure
 */
const LSHandle *
gls2_handle_get_lshandle (Gls2Handle *self)
{
    Gls2HandlePrivate *priv;

    gls2_ret_null_if_fail_autodef (self, priv);

    return priv->handler;
}

/*!
 * @brief Get service name
 * 
 * DO NOT free the returned data.
 * It does not work as deep-copy.
 * 
 * Use gls2_handle_dup_service_name for the deep-copied data.
 * 
 * @param  self: Gls2Handle instance
 * @return Pointer to const service name on success, or NULL on failure
 */
const gchar *
gls2_handle_get_service_name (Gls2Handle *self)
{
    Gls2HandlePrivate *priv;

    gls2_ret_null_if_fail (GLS2_IS_HANDLE (self));

    priv = self->priv;
    gls2_ret_null_if_fail (priv->service_name != NULL);

    return priv->service_name;
}

/*!
 * @brief Deep-copied service name
 * 
 * Must be g_free'd after use it.
 * 
 * @param  self: Gls2Handle instance
 * @return Pointer to deep-copied service name on success, or NULL on failure
 */
gchar *
gls2_handle_dup_service_name (Gls2Handle *self)
{
    Gls2HandlePrivate *priv;

    gls2_ret_null_if_fail (GLS2_IS_HANDLE (self));

    priv = self->priv;
    gls2_ret_null_if_fail (priv->service_name != NULL);

    return g_strdup (priv->service_name);
}

static inline gboolean
gls2_handle_app_id_is_set (Gls2Handle *self)
{
    return ( self->priv->app_id ? TRUE : FALSE );
}

const gchar *
gls2_handle_get_app_id (Gls2Handle *self)
{
    Gls2HandlePrivate *priv;

    gls2_ret_null_if_fail (GLS2_IS_HANDLE (self));

    if ( !gls2_handle_app_id_is_set (self) )
        return NULL;

    priv = self->priv;

    return priv->app_id;
}

gchar *
gls2_handle_dup_app_id (Gls2Handle *self)
{
    const gchar *app_id;

    app_id = gls2_handle_get_app_id (self);

    return app_id ? g_strdup (app_id) : NULL;
}
