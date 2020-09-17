//
// Created by gust on 2017/8/8.
//

#ifndef MINI_JVM_UTIL_H
#define MINI_JVM_UTIL_H


#include "jvm.h"
#include "../utils/hashset.h"
#include "jdwp.h"


#ifdef __cplusplus
extern "C" {
#endif

#define NANO_2_SEC_SCALE 1000000000
#define NANO_2_MILLS_SCALE 1000000
#define MILL_2_SEC_SCALE 1000
static s64 NANO_START = 0;
typedef unsigned short uni_char;

//======================= utils =============================
typedef struct _OptimizeCache {
    FieldInfo *string_offset;
    FieldInfo *string_count;
    FieldInfo *string_value;
    //
    FieldInfo *stringbuilder_value;
    FieldInfo *stringbuilder_count;
    //
    FieldInfo *thread_name;
    FieldInfo *thread_stackFrame;
    //
    FieldInfo *class_classHandle;

    //
    FieldInfo *stacktrace_declaringClass;
    FieldInfo *stacktrace_methodName;
    FieldInfo *stacktrace_fileName;
    FieldInfo *stacktrace_lineNumber;
    FieldInfo *stacktrace_parent;

    //
    FieldInfo *dmo_memAddr;
    FieldInfo *dmo_length;
    FieldInfo *dmo_desc;

    //
    JClass *array_classes[DATATYPE_COUNT];
} OptimizeCache;
extern OptimizeCache jvm_runtime_cache;

s32 utf8_2_unicode(Utf8String *ustr, u16 *arr);

int unicode_2_utf8(u16 *jchar_arr, Utf8String *ustr, s32 totalSize);

void swap_endian_little_big(u8 *ptr, s32 size);

s32 getDataTypeIndex(c8 ch);

c8 *getDataTypeFullName(c8 ch);

u8 getDataTypeTagByName(Utf8String *name);

s32 isDataReferByTag(c8 c);

s32 isData8ByteByTag(c8 c);

s32 isDataReferByIndex(s32 index);

u8 getDataTypeTag(s32 index);

s64 currentTimeMillis(void);

s64 nanoTime(void);

s64 threadSleep(s64 ms);

s32 sys_properties_load(ClassLoader *loader);

void sys_properties_dispose(void);

void sys_properties_set_c(c8 *key, c8 *val);

void instance_release_from_thread(Instance *ref, Runtime *runtime);

void instance_hold_to_thread(Instance *ins, Runtime *runtime);

int jvm_printf(const char *, ...);

void invoke_deepth(Runtime *runtime);

void printDumpOfClasses(void);


Instance *exception_create(s32 exception_type, Runtime *runtime);

Instance *exception_create_str(s32 exception_type, Runtime *runtime, c8 *errmsg);

Instance *method_type_create(Runtime *runtime, Utf8String *desc);

Instance *method_handle_create(Runtime *runtime, MethodInfo *mi, s32 kind);

Instance *method_handles_lookup_create(Runtime *runtime, JClass *caller);


/**
 * get instance field value address
 * @param ins ins
 * @param fi fi
 * @return addr
 */
static inline c8 *getInstanceFieldPtr(Instance *ins, FieldInfo *fi) {
    return &(ins->obj_fields[fi->offset_instance]);
}

static inline c8 *getInstanceFieldPtrByOffset(Instance *ins, u16 offset) {
    return &(ins->obj_fields[offset]);
}

static inline c8 *getStaticFieldPtr(FieldInfo *fi) {
    return &(fi->_this_class->field_static[fi->offset]);
}


static inline void setFieldInt(c8 *ptr, s32 v) {
    *((s32 *) ptr) = v;
}

static inline void setFieldRefer(c8 *ptr, __refer v) {
    *((__refer *) ptr) = v;
}

static inline void setFieldLong(c8 *ptr, s64 v) {
    *((s64 *) ptr) = v;
}

static inline void setFieldShort(c8 *ptr, s16 v) {
    *((s16 *) ptr) = v;
}

static inline void setFieldByte(c8 *ptr, s8 v) {
    *((s8 *) ptr) = v;
}

static inline void setFieldDouble(c8 *ptr, f64 v) {
    *((f64 *) ptr) = v;
}

static inline void setFieldFloat(c8 *ptr, f32 v) {
    *((f32 *) ptr) = v;
}

static inline s32 getFieldInt(c8 *ptr) {
    return *((s32 *) ptr);
}

static inline __refer getFieldRefer(c8 *ptr) {
    return *((__refer *) ptr);
}

static inline s16 getFieldShort(c8 *ptr) {
    return *((s16 *) ptr);
}

static inline u16 getFieldChar(c8 *ptr) {
    return *((u16 *) ptr);
}

static inline s8 getFieldByte(c8 *ptr) {
    return *((s8 *) ptr);
}

static inline s64 getFieldLong(c8 *ptr) {
    return *((s64 *) ptr);
}

static inline f32 getFieldFloat(c8 *ptr) {
    return *((f32 *) ptr);
}


static inline f64 getFieldDouble(c8 *ptr) {
    return *((f64 *) ptr);
}

s32 getLineNumByIndex(CodeAttribute *ca, s32 offset);

s32 _loadFileContents(c8 *file, ByteBuf *buf);

ByteBuf *load_file_from_classpath(ClassLoader *loader, Utf8String *path);


//===============================    实例化 java.lang.Class  ==================================

Instance *insOfJavaLangClass_create_get(Runtime *runtime, JClass *clazz);

void insOfJavaLangClass_set_classHandle(Instance *insOfJavaLangClass, JClass *handle);

JClass *insOfJavaLangClass_get_classHandle(Instance *insOfJavaLangClass);

////======================= jstring =============================

Instance *jstring_create(Utf8String *src, Runtime *runtime);

Instance *jstring_create_cstr(c8 *cstr, Runtime *runtime);

void jstring_set_count(Instance *jstr, s32 count);

s32 jstring_get_count(Instance *jstr);

s32 jstring_get_offset(Instance *jstr);

c8 *jstring_get_value_ptr(Instance *jstr);

Instance *jstring_get_value_array(Instance *jstr);

u16 jstring_char_at(Instance *jstr, s32 index);

s32 jstring_index_of(Instance *jstr, uni_char ch, s32 startAt);

s32 jstring_equals(Instance *jstr1, Instance *jstr2);

s32 jstring_2_utf8(Instance *jstr, Utf8String *utf8);

CStringArr *cstringarr_create(Instance *jstr_arr);

void cstringarr_destory(CStringArr *);

void referarr_destory(CStringArr *ref_arr);

ReferArr *referarr_create(Instance *jobj_arr);

void referarr_2_jlongarr(ReferArr *ref_arr, Instance *jlong_arr);

////======================= thread =============================


void threadlist_add(Runtime *r);

void threadlist_remove(Runtime *r);

Runtime *threadlist_get(s32 i);

s32 threadlist_count_none_daemon();

void threadinfo_destory(JavaThreadInfo *threadInfo);

void thread_stop_all();

JavaThreadInfo *threadinfo_create(void);

struct _JavaThreadInfo {
    Instance *jthread;
    Runtime *top_runtime;
    MemoryBlock *tmp_holder;//for jni hold java object
    MemoryBlock *objs_header;//link to new instance, until garbage accept
    MemoryBlock *objs_tailer;//link to last instance, until garbage accept
    MemoryBlock *curThreadLock;//if thread is locked ,the filed save the lock

    ArrayList *stacktrack;  //save methodrawindex, the pos 0 is the throw point
    ArrayList *lineNo;  //save methodrawindex, the pos 0 is the throw point

    void (*block_break)(__refer para);//function for break io blocking

    __refer block_break_para; //thread blocking on io

    u16 volatile suspend_count;//for jdwp suspend ,>0 suspend, ==0 resume
    u16 volatile no_pause;  //can't pause when clinit
    u8 volatile thread_status;
    u8 volatile is_suspend;
    u8 volatile is_blocking;
    u8 is_interrupt;

    thrd_t pthread;
    //调试器相关字段
    JdwpStep jdwp_step;

};

struct _ThreadLock {
    cnd_t thread_cond;
    mtx_t mutex_lock; //互斥锁
};


s32 jthread_init(Instance *jthread, Runtime *runtime);

s32 jthread_dispose(Instance *jthread);

s32 jthread_run(void *para);

thrd_t jthread_start(Instance *ins);

__refer jthread_get_stackframe_value(Instance *ins);

s32 jthread_get_daemon_value(Instance *ins, Runtime *runtime);

void jthread_set_stackframe_value(Instance *ins, void *val);

__refer jthread_get_name_value(Instance *ins);

void jthreadlock_create(Runtime *runtime, MemoryBlock *mb);

void jthreadlock_destory(MemoryBlock *mb);

s32 jthread_lock(MemoryBlock *mb, Runtime *runtime);

s32 jthread_unlock(MemoryBlock *mb, Runtime *runtime);

s32 jthread_notify(MemoryBlock *mb, Runtime *runtime);

s32 jthread_notifyAll(MemoryBlock *mb, Runtime *runtime);

s32 jthread_waitTime(MemoryBlock *mb, Runtime *runtime, s64 waitms);

s32 jthread_sleep(Runtime *runtime, s64 ms);

s32 jthread_yield(Runtime *runtime);

s32 jthread_resume(Runtime *runtime);

s32 jthread_suspend(Runtime *runtime);

void jthread_block_exit(Runtime *runtime);

void jthread_block_enter(Runtime *runtime);

s32 check_suspend_and_pause(Runtime *runtime);

void thread_lock_dispose(ThreadLock *lock);

void thread_lock_init(ThreadLock *lock);


static inline Runtime *_runtime_alloc() {
    Runtime *runtime = jvm_calloc(sizeof(Runtime));
    runtime->jnienv = &jnienv;
    return runtime;
}

/**
 * runtime 的创建和销毁会极大影响性能，因此对其进行缓存
 * @param parent runtime of parent
 * @return runtime
 */
static inline Runtime *runtime_create_inl(Runtime *parent) {

    Runtime *runtime;

    if (!parent) {
        runtime = _runtime_alloc();
        runtime->stack = stack_create(STACK_LENGHT_INIT);
        runtime->threadInfo = threadinfo_create();
        runtime->threadInfo->top_runtime = runtime;
    } else {
        Runtime *top_runtime = parent->threadInfo->top_runtime;
        runtime = top_runtime->runtime_pool_header;
        if (runtime) {
            top_runtime->runtime_pool_header = runtime->next;
            //runtime->next = NULL;
        } else {
            runtime = _runtime_alloc();
            runtime->stack = parent->stack;
            runtime->threadInfo = parent->threadInfo;
        }
        runtime->parent = parent;
        parent->son = runtime;
    }
    return runtime;
}


static inline void runtime_destory_inl(Runtime *runtime) {
    Runtime *top_runtime = runtime->threadInfo->top_runtime;
    if (top_runtime != runtime) {
        runtime->next = top_runtime->runtime_pool_header;
        top_runtime->runtime_pool_header = runtime;
    } else {
        stack_destory(runtime->stack);
        threadinfo_destory(runtime->threadInfo);

        Runtime *next = top_runtime->runtime_pool_header;
        while (next) {
            Runtime *r = next;
            next = r->next;
            jvm_free(r);
        }
        runtime->runtime_pool_header = NULL;
        jvm_free(runtime);
    }
}

static inline void runtime_clear_stacktrack(Runtime *runtime) {
    arraylist_clear(runtime->threadInfo->stacktrack);
    arraylist_clear(runtime->threadInfo->lineNo);
}

////======================= array =============================

Instance *jarray_create_by_class(Runtime *runtime, s32 count, JClass *clazz);

Instance *jarray_create_by_type_name(Runtime *runtime, s32 count, Utf8String *name);

Instance *jarray_create_by_type_index(Runtime *runtime, s32 count, s32 typeIdx);

JClass *array_class_get_by_name(Runtime *runtime, Utf8String *name);

JClass *array_class_get_by_typetag(Runtime *runtime, Utf8String *tag);

JClass *array_class_create_get(Runtime *runtime, Utf8String *desc);

JClass *array_class_get_by_index(Runtime *runtime, s32 typeIdx);

s32 jarray_destory(Instance *arr);

Instance *jarray_multi_create(Runtime *runtime, s32 *dim, s32 dim_size, Utf8String *desc, s32 deep);

void jarray_set_field(Instance *arr, s32 index, s64 val);

s64 jarray_get_field(Instance *arr, s32 index);

c8 *getFieldPtr_byName_c(Instance *instance, c8 *pclassName, c8 *pfieldName, c8 *pfieldType, Runtime *runtime);

c8 *getFieldPtr_byName(Instance *instance, Utf8String *clsName, Utf8String *fieldName, Utf8String *fieldType, Runtime *runtime);

JClass *classes_get_c(c8 *clsName);

JClass *classes_get(Utf8String *clsName);

JClass *classes_load_get_without_clinit(Utf8String *ustr, Runtime *runtime);

JClass *classes_load_get_c(c8 *pclassName, Runtime *runtime);

s32 classes_put(JClass *clazz);

JClass *classes_load_get(Utf8String *pclassName, Runtime *runtime);

JClass *primitive_class_create_get(Runtime *runtime, Utf8String *ustr);


#ifdef __cplusplus
}
#endif

#endif //MINI_JVM_UTIL_H
