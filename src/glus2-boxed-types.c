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
#include <string.h>

/* --- LSHandle --- */
/*
 * @param data: Pointer to LSHandle data
 * 
 * Be careful to handle the object of the returned pointer.
 * ls_handle_copy copies the object on shallow-copy.
 * 
 * @return A pointer to shallow-copied LSHandle or NULL on failure.
 */
static LSHandle *
glus2_lshandle_copy (gpointer data)
{
    LSHandle *lshandler;
    LSHandle *shallow_copy;

    g_return_val_if_fail (data != NULL, NULL);

    lshandler = (LSHandle *)data;

    shallow_copy = g_try_new (LSHandle, 1);
    if (shallow_copy != NULL) {
        /* TODO
         *
         * Design how developers deal with it.
         * Maybe it should be deep-copied.
         */
        memcpy (shallow_copy, lshandler, sizeof(LSHandle));
    }

    return shallow_copy;
}

static void
glus2_lshandle_free (gpointer data)
{
    LSErorr error;
    LSHandle *lshandler;

    g_return_if_fail (data != NULL);

    lshandler = (LSHandle *)data;

    LSErrorInit (&error);

    /* Free the data */
    if (!LSUnregister (lshandler, &error))
        g_critical ("Failed to unregister LSHandle");

    LSErrorFree (&error);
    g_free (lshandler);
}

G_DEFINE_BOXED_TYPE (LSHandle, glus2_lshandle, glus2_handle_copy, glus2_handle_free)


/* --- LSMethod --- */
/*
 * @param data: Pointer to LSMethod data
 * 
 * @return A pointer to deep-copied LSMethod or NULL on failure.
 */
static LSMethod *
glus2_lsmethod_copy (gpointer data)
{
    LSMethod *lsmethod;
    LSMethod *deep_copy;

    g_return_val_if_fail (data != NULL, NULL);
    
    lsmethod = (LSMethod *)data;

    deep_copy = g_try_new (LSMethod, 1);
    if (deep_copy != NULL) {
        deep_copy->name = g_strdup (lsmethod->name);
        deep_copy->function = lsmethod->function;
        deep_copy->flags = lsmethod->flags;
    }

    return deep_copy;
}

static void
glus2_lsmethod_free (gpointer data)
{
    LSMethod *lsmethod;

    g_return_if_fail (data != NULL);

    lsmethod = (LSMethod *)data;

    g_free (lsmethod->name);
    g_free (lsmethod);
}

G_DEFINE_BOXED_TYPE (LSMethod, glus2_lsmethod, glus2_lsmethod_copy, glus2_lsmethod_free)


/* --- LSSignal --- */
/*
 * @param data: Pointer to LSSignal data
 * 
 * @return A pointer to deep-copied LSSignal or NULL on failure.
 */
static LSSignal *
glus2_lssignal_copy (gpointer data)
{
    LSSignal *lssig;
    LSSignal *deep_copy;

    g_return_val_if_fail (data != NULL, NULL);

    lssig = (LSSignal *)data;

    deep_copy = g_try_new (LSSignal, 1);
    if (deep_copy != NULL) {
        deep_copy->name = g_strdup (lssig->name);
        deep_copy->flags = lssig->flags;
    }

    return deep_copy;
}

static void
glus2_lssignal_free (gpointer data)
{
    LSSignal *lssig;

    g_return_if_fail (data != NULL);

    lssig = (LSSignal *)data;

    g_free (lssig->name);
    g_free (lssig);
}

G_DEFINE_BOXED_TYPE (LSSignal, glus2_lssignal, glus2_lssignal_copy, glus2_lssignal_free)


/* --- LSProperty --- */
/*
 * @param data: Pointer to LSProperty data
 * 
 * @return A pointer to deep-copied LSProperty or NULL on failure.
 */
static LSProperty *
glus2_lsproperty_copy (gpointer data)
{
    LSProperty *lsprop;
    LSProperty *deep_copy;

    g_return_val_if_fail (data != NULL, NULL);

    lsprop = (LSProperty *)data;

    deep_copy = g_try_new (LSProperty, 1);
    if (deep_copy != NULL) {
        deep_copy->name = g_strdup (lsprop->name);
        deep_copy->type = g_strdup (lsprop->type);
        deep_copy->get = lsprop->get;
        deep_copy->set = lsprop->set;
        deep_copy->flags = lsprop->flags;
    }

    return deep_copy;
}

static void
glus2_lsproperty_free (gpointer data)
{
    LSProperty *lsprop;

    g_return_if_fail (data != NULL);

    lsprop = (LSProperty *)data;

    g_free (lsprop->name);
    g_free (lsprop->type);
    g_free (lsprop);
}

G_DEFINE_BOXED_TYPE (LSProperty, glus2_lsproperty, glus2_lsproperty_copy, glus2_lsproperty_free)
