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

#define     GLUS2_SMALL_PADDING     2
#define     GLUS2_PADDING           4

struct _Glus2Handle
{
    /* Private */
    GObject     parent;

    Glus2HandlePrivate *priv;
};

struct _Glus2HandleClass
{
    GObjectClass parent_class;

    /* Private */
    gpointer _reserved[GLUS2_PADDING];
};

struct _Glus2HandlePrivate
{
    LSHandle        *handler;
    LSError         *lserror;

    gchar       *service_name;
    gchar       *app_id;
};

G_DEFINE_TYPE_WITH_PRIVATE (Glus2Handle, glus2_handle, G_TYPE_OBJECT)

enum
{
    PROP_0,
    PROP_SERVICE_NAME;
    PROP_APP_ID;
    LAST_PROP
};


/* --- GObject --- */
static void
glus2_handle_dispose (GObject *parent)
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

    G_OBJECT_CLASS (glus2_handle_parent_class)->dispose (parent);
}

static void
glus2_handle_finalize (GObject *parent)
{
    Glus2HandlePrivate *priv = GLUS2_HANDLE (object)->priv;
    bool ret;

    /* Free if lserror was set somewhere */
    if (LSErrorIsSet (priv->lserror))
        LSErrorFree (priv->lserror);

    /* Unregister LSHandle */
    if ( !(ret = LSUnregister (priv->handler, priv->lserror)) ) {
        glus2_err_log_if_set (priv->lserror);
    }

    g_free (priv->lserror);
    priv->lserror = NULL;

    g_free (priv->service_name);
    g_free (priv->app_id);

    G_OBJECT_CLASS (glus2_handle_parent_class)->finalize (parent);
}

static void
glus2_handle_get_property (GObject      *object,
                           guint        prop_id,
                           GValue       *value,
                           GParamSpec   *pspec)
{
    Glus2HandlePrivate *priv = GLUS2_HANDLE (object)->priv;

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
glus2_handle_set_property (GObject      *object,
                           guint        prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
    Glus2HandlePrivate *priv = GLUS2_HANDLE (object)->priv;

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
glus2_handle_class_init (Glus2HandleClass *klass)
{
    GObjectClass *object_klass = G_OBJECT_CLASS (klass);

    object_klass->dispose = glus2_handle_dispose;
    object_klass->finalize = glus2_handle_finalize;
    object_klass->get_property = glus2_handle_get_property;
    object_klass->set_property = glus2_handle_set_property;

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
    )

    /* Install gobject signals */
}

static void
glus2_handle_init (Glus2Handle *self)
{
    Glus2HandlePrivate *priv = glus2_handle_get_instance_private (self);
    LSError *error;

    /* Initialize private fields */
    self->priv = priv;

    /* Initialize LSError */
    if ( (error = g_try_new (LSError, 1)) != NULL ) {
        LSErrorInit (error);
        priv->lserror = error;
    }

    /* Register LSHandle */
    if ( !LSRegister(priv->service_name, &priv->handler, error) ) {
        glus2_err_log_if_set (error);
    }
}

Glus2Handle *
glus2_handle_new (const gchar *service_name)
{
    return GLUS2_HANDLE (g_object_new (GLUS2_TYPE_HANDLE,
                                       "service-name", service_name,
                                       "app-id", NULL,
                                       NULL));
}

Glus2Handle *
glus2_handle_new_with_app_id (const gchar *service_name,
                              const gchar *app_id)
{
    return GLUS2_HANDLE (g_object_new (GLUS2_TYPE_HANDLE,
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
 * @param  self: Glus2Handle instance
 * @return Pointer to LSHandle on success, or NULL on failure
 */
const LSHandle *
glus2_handle_get_lshandle (Glus2Handle *self)
{
    Glus2HandlePrivate *priv;

    glus2_ret_null_if_fail_autodef (self, priv);

    return priv->handler;
}

/*!
 * @brief Get service name
 * 
 * DO NOT free the returned data.
 * It does not work as deep-copy.
 * 
 * Use glus2_handle_dup_service_name for the deep-copied data.
 * 
 * @param  self: Glus2Handle instance
 * @return Pointer to const service name on success, or NULL on failure
 */
const gchar *
glus2_handle_get_service_name (Glus2Handle *self)
{
    Glus2HandlePrivate *priv;

    glus2_ret_null_if_fail (GLUS2_IS_HANDLE (self));

    priv = self->priv;
    glus2_ret_null_if_fail (priv->service_name != NULL);

    return priv->service_name;
}

/*!
 * @brief Deep-copied service name
 * 
 * Must be g_free'd after use it.
 * 
 * @param  self: Glus2Handle instance
 * @return Pointer to deep-copied service name on success, or NULL on failure
 */
gchar *
glus2_handle_dup_service_name (Glus2Handle *self)
{
    Glus2HandlePrivate *priv;

    glus2_ret_null_if_fail (GLUS2_IS_HANDLE (self));

    priv = self->priv;
    glus2_ret_null_if_fail (priv->service_name != NULL);

    return g_strdup (priv->service_name);
}

static inline gboolean
glus2_handle_app_id_is_set (Glus2Handle *self)
{
    return ( self->priv->app_id ? TRUE : FALSE );
}

const gchar *
glus2_handle_get_app_id (Glus2Handle *self)
{
    Glus2HandlePrivate *priv;

    glus2_ret_null_if_fail (GLUS2_IS_HANDLE (self));

    if ( !glus2_handle_app_id_is_set (self) )
        return NULL;

    priv = self->priv;

    return priv->app_id;
}

gchar *
glus2_handle_dup_app_id (Glus2Handle *self)
{
    const gchar *app_id;

    app_id = glus2_handle_get_app_id (self);

    return app_id ? g_strdup (app_id) : NULL;
}
