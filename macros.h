#pragma once

#include "view_types.h"

#ifdef __GNUC__
#  define decltype __typeof__
#endif

#define EV_DECL_CLASS_BEGIN(name, layout) \
    namespace name { \
        class cview; \
        class view; \
        class value; \
    } \
    template <> \
    struct layout2view<layout> { \
        typedef name::view view; \
        typedef name::cview cview; \
    }; \
    namespace name { \
        typedef layout layout_type; \

#define EV_DECL_CONST_VIEWS_AND_VALUES_BEGIN \
    template <template<typename> class storage_type_t> \
    class _const_methods { \
    protected: \
        storage_type_t<layout_type> _storage; \
    private:

#define EV_DECL_CONST_VIEWS_AND_VALUES_END };
        
#define EV_DECL_VIEWS_AND_VALUES_BEGIN \
    template <template<typename> class storage_type_t> \
    class _mutable_methods : public _const_methods<storage_type_t> { \
        typedef _const_methods<storage_type_t> base; \
    private:

#define EV_DECL_VIEWS_AND_VALUES_END };

#define EV_DECL_CLASS_END \
    class cview : public _const_methods<const_pointer_storage_type> { \
    public: \
        cview(const char* base) { \
            _storage.bytes = base; \
        } \
    }; \
    class view : public _mutable_methods<pointer_storage_type> { \
    public: \
        view(char* base) { \
            _storage.bytes = base; \
        } \
        operator cview() { \
            return cview(_storage.bytes); \
        } \
    }; \
    class value : public _mutable_methods<array_storage_type> { \
    public: \
        value() { } \
        value(uint8_t x) { \
            std::memset(_storage.bytes, x, sizeof(_storage.bytes)); \
        } \
        class view view() { \
            return _storage.bytes; \
        } \
        operator class view() { \
            return _storage.bytes; \
        } \
        cview view() const { \
            return _storage.bytes; \
        } \
        operator cview() const { \
            return _storage.bytes; \
        } \
    }; \
};

#define EV_DECLTYPE_MEMBER(name) \
    decltype(((layout_type*)0)->name)

#define EV_OFFSETOF(name) \
    ((std::size_t) &(((layout_type*)0)->name))
    //offsetof(layout_type, name)

#define EV_DECL_ACCESSOR(name) \
    EV_DECLTYPE_MEMBER(name) name() const { \
        return this->_storage.template read<EV_DECLTYPE_MEMBER(name)>(EV_OFFSETOF(name)); \
    }

#define EV_DECL_ARRAY_ACCESSOR(name) \
    EV_DECLTYPE_MEMBER(name[0]) name(std::size_t n) const { \
        return this->_storage.template read<EV_DECLTYPE_MEMBER(name[n])>(EV_OFFSETOF(name[n])); \
    }

#define EV_DECL_RAW_ACCESSOR(name) \
    const char * name() const { \
        return this->_storage.view(EV_OFFSETOF(name)); \
    }

#define EV_DECL_VIEW_ACCESSOR(name) \
    layout2view<EV_DECLTYPE_MEMBER(name)>::cview name() const { \
        return this->_storage.view(EV_OFFSETOF(name)); \
    }

#define EV_DECL_MUTATOR(name) \
    using base::name; \
    void name(EV_DECLTYPE_MEMBER(name) value) { \
        return this->_storage.write(EV_OFFSETOF(name), value); \
    }

#define EV_DECL_ARRAY_MUTATOR(name) \
    void name(std::size_t n, EV_DECLTYPE_MEMBER(name[0]) value) { \
        return this->_storage.write(EV_OFFSETOF(name[n]), value); \
    }

#define EV_DECL_RAW_MUTATOR(name) \
    char * name() { \
        return this->_storage.view(EV_OFFSETOF(name)); \
    }

#define EV_DECL_VIEW_MUTATOR(name) \
    layout2view<EV_DECLTYPE_MEMBER(name)>::view name() { \
        return this->_storage.view(EV_OFFSETOF(name)); \
    }

#define EV_CONST_METHOD_IMPL(rtype, name) \
    template <template<typename> class storage_type_t> \
    rtype name::_const_methods<storage_type_t>

#define EV_METHOD_IMPL(rtype, name) \
    template <template<typename> class storage_type_t> \
    rtype name::_mutable_methods<storage_type_t>

#define EV_INSTANTIATE(name) \
    template class name::_const_methods<array_storage_type>; \
    template class name::_mutable_methods<array_storage_type>; \
    template class name::_const_methods<pointer_storage_type>; \
    template class name::_mutable_methods<pointer_storage_type>; \
    template class name::_const_methods<const_pointer_storage_type>;
