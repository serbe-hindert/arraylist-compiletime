#ifndef NERDARRAYLIST_LIBRARY_H
#define NERDARRAYLIST_LIBRARY_H

#pragma region ARRAYLIST_DECLARATION
/**
 * @brief declare an arraylist type
 * @param type member type of the arraylist
 */
#define ARRAYLIST_DECLARE(type) \
    /** Define the typed arraylist itself */ \
    typedef struct { \
        size_t maximum; \
        size_t current; \
        type* elements; \
    } type##ArrayList;
#pragma endregion ARRAYLIST_DECLARATION

#pragma region ARRAYLIST_HEAP
/**
 * @brief create a function to allocate an arraylist on the heap properly
 * @param type member type of the arraylist
 */
#define ARRAYLIST_HEAP_CREATE_FUNCTION(type) \
    /** create a type## arraylist using the heap */ \
    type##ArrayList* type##ArrayList_heapCreate(size_t initialCapacity) { \
        type##ArrayList* list = malloc(sizeof(type##ArrayList)); \
        if (list == NULL) { \
            return NULL; \
        } \
        list->maximum = initialCapacity; \
        list->current = 0; \
        list->elements = malloc(list->maximum * sizeof(type)); \
        if (list->elements == NULL) { \
            free(list); \
            return NULL; \
        } \
        return list; \
    }
/**
 * @brief create a function to deallocate an arraylist that was allocated on the heap properly
 * @param type member type of the arraylist
 */
#define ARRAYLIST_HEAP_DESTROY_FUNCTION(type) \
    /** destroy a type## arraylist that was properly allocated on the heap */ \
    void type##ArrayList_heapDestroy(type##ArrayList* restrict list) { \
        free(list->elements); \
        free(list); \
    }
/**
 * @brief create both create and destroy functions for managing arraylists on the heap
 * @param type member type of the arraylist
 */
#define ARRAYLIST_HEAP_ALL_FUNCTIONS(type) \
ARRAYLIST_HEAP_CREATE_FUNCTION(type) \
ARRAYLIST_HEAP_DESTROY_FUNCTION(type)
#pragma endregion ARRAYLIST_HEAP

#pragma region ARRAYLIST_STACK
/**
 * @brief create a function to configure an arraylist allocated on the stack properly
 * @param type member type of the arraylist
 * @return true if allocation of elements was succesful
 */
#define ARRAYLIST_STACK_CREATE_FUNCTION(type) \
    /** configure a type## arraylist that has been created on the stack */ \
    bool type##ArrayList_stackCreate(type##ArrayList* restrict list, size_t initialCapacity) { \
        list->maximum = initialCapacity; \
        list->current = 0; \
        list->elements = malloc(list->maximum * sizeof(type)); \
        return (list->elements != NULL); \
    }
/**
 * @brief create a function to destroy an arraylist that was allocated on the stack properly
 * @param type member type of the arraylist
 */
#define ARRAYLIST_STACK_DESTROY_FUNCTION(type) \
    /** destroy a type## arraylist that has been allocated on the stack */ \
    void type##ArrayList_stackDestroy(type##ArrayList* restrict list) { \
        free(list->elements); \
    }
/**
 * @brief create both create and destroy functions for managing arraylists on the stack
 * @param type member type of the arraylist
 */
#define ARRAYLIST_STACK_ALL_FUNCTIONS(type) \
ARRAYLIST_STACK_CREATE_FUNCTION(type) \
ARRAYLIST_STACK_DESTROY_FUNCTION(type)
#pragma endregion ARRAYLIST_STACK

#pragma region ARRAYLIST_MISC
/**
 * @brief create a function to insert a value into an arraylist
 * @param type member type of the arraylist
 * @return true if insert was succesful
 */
#define ARRAYLIST_MISC_INSERT_FUNCTION(type) \
    /** insert a value into an type## arraylist */ \
    bool type##ArrayList_insert(type##ArrayList* restrict list, type value) { \
        if (list->current == list->maximum) { \
            list->maximum *= 2; \
            list->elements = realloc(list->elements, list->maximum * sizeof(type)); \
            if (list->elements == NULL) { \
                return false; \
            } \
        } \
        list->elements[list->current] = value; \
        list->current++; \
        return true; \
    }
/**
 * @brief create a function to set a value inside an arraylist
 * @param type member type of the arraylist
 * @return true if set was succesful
 */
#define ARRAYLIST_MISC_SET_FUNCTION(type) \
    /** set a value in a type## arraylist */ \
    bool type##ArrayList_set(type##ArrayList* restrict list, size_t index, type value) { \
        if (index < list->current) { \
            return false; \
        } \
        list->elements[index] = value; \
        return true; \
    }

/**
 * @brief create a function to get a value from an arraylist
 * @param type member type of the arraylist
 * @return the member with the correct index
 */
#define ARRAYLIST_MISC_GET_FUNCTION(type) \
    /** get a value from a type## arraylist */ \
    type type##ArrayList_get(type##ArrayList* restrict list, size_t index) { \
        if (index >= list->current) { \
            return NULL; \
        } \
        return list->elements[index]; \
    }

/**
 * @brief create a function to delete a value from an arraylist
 * @param type member type of the arraylist
 * @return true if the deletion was succesful
 */
#define ARRAYLIST_MISC_DELETE_FUNCTION(type) \
    /** delete a value from a type## arraylist */ \
    bool type##ArrayList_delete(type##ArrayList* restrict list, size_t index) { \
        if (index >= list->current) { \
            return false; \
        } \
        if (index != list->current - 1) { \
            /* destination: the index */ \
            /* source: the place after the index */ \
            /* length: the length of the index to the current count of elements */ \
            for (size_t i = index; i < list->current - 1; i++) { \
                list->elements[i] = list->elements[i + 1]; \
            } \
        } \
        list->current--; \
        return true; \
    }
/**
 * @brief create a function to delete a value from an arraylist by overwriting it with the last value
 * @param type member type of the arraylist
 * @return true if the deletion was succesful
 */
#define ARRAYLIST_MISC_FAST_DELETE_FUNCTION(type) \
    /** delete a value from a type## arraylist by overwriting it with the last value */ \
    bool type##ArrayList_fastDelete(type##ArrayList* restrict list, size_t index) { \
        if (index >= list->current) { \
            return false; \
        } \
        list->elements[index] = list->elements[list->current - 1]; \
        list->current--; \
        return true; \
    }

/**
 * @brief create a function to check if a value exists in an arraylist
 * @param type member type of the arraylist
 * @return true if the value exists in the arraylist
 */
#define ARRAYLIST_MISC_CONTAINS_FUNCTION(type) \
    /** check if a value exists inside a type## arraylist */ \
    bool type##ArrayList_contains(type##ArrayList* restrict list, type value) { \
        for (size_t i = 0; i < list->current; i++) { \
            if (value == list->elements[i]) { \
                return true; \
            } \
        } \
        return false; \
    }
/**
 * @brief creates all the misc functions for interacting with arraylists
 * @param type member type of the arraylist
 */
#define ARRAYLIST_MISC_ALL_FUNCTIONS(type) \
ARRAYLIST_MISC_INSERT_FUNCTION(type) \
ARRAYLIST_MISC_SET_FUNCTION(type) \
ARRAYLIST_MISC_GET_FUNCTION(type) \
ARRAYLIST_MISC_DELETE_FUNCTION(type) \
ARRAYLIST_MISC_FAST_DELETE_FUNCTION(type) \
ARRAYLIST_MISC_CONTAINS_FUNCTION(type)
#pragma endregion ARRAYLIST_MISC

/**
 * @brief creates all the functions for interacting with arraylists
 * @param type member type of the arraylist
 */
#define ARRAYLIST_GENERATE_COMPLETE(type) \
ARRAYLIST_DECLARE(type) \
ARRAYLIST_HEAP_ALL_FUNCTIONS(type) \
ARRAYLIST_STACK_ALL_FUNCTIONS(type) \
ARRAYLIST_MISC_ALL_FUNCTIONS(type)


#endif //NERDARRAYLIST_LIBRARY_H
