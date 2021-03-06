#ifndef ENACT_GC_H
#define ENACT_GC_H

#include <vector>

#include "../value/Object.h"

namespace enact {
    class CompileContext;

    constexpr size_t GC_HEAP_GROW_FACTOR = 2;

    class GC {
        CompileContext &m_context;

        size_t m_bytesAllocated = 0;
        size_t m_nextRun = 1024 * 1024;

        std::vector<Object *> m_objects{};
        std::vector<Object *> m_greyStack{};

        void markRoots();

        void markCompilerRoots();

        void markVMRoots();

        void markObject(Object *object);

        void markValue(Value value);

        void markValues(const std::vector<Value> &values);

        void traceReferences();

        void blackenObject(Object *object);

        void sweep();

    public:
        explicit GC(CompileContext &context);

        ~GC();

        template<typename T, typename... Args>
        T *allocateObject(Args &&... args);

        Object *cloneObject(Object *object);

        void collectGarbage();

        void freeObject(Object *object);

        void freeObjects();
    };
}

#endif //ENACT_GC_H
