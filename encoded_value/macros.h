#pragma once

#if __cplusplus >= 201103L
#  define EV_DECLTYPE decltype
#elif defined(__GNUC__)
#  define EV_DECLTYPE __typeof__
#elif defined(_MSC_VER) && _MSC_VER >= 1600
#  define EV_DECLTYPE decltype
#else
#  error "Need a compiler with some kind of decltype support"
#endif

#define EV_DECL_CLASS_BEGIN(name, layout) \
    namespace name { \
        class cview; \
        class view; \
        class value; \
    } \
    namespace encoded_value { \
    template <> \
    struct layout2view<layout> { \
        typedef name::view view; \
        typedef name::cview cview; \
    }; \
    } \
    namespace name { \
        typedef layout layout_type; \

#define EV_DECL_CONST_METHODS_BEGIN \
    template <class storage_type_t> \
    class const_methods { \
    protected: \
        storage_type_t _storage; \
    private:

#define EV_DECL_CONST_METHODS_END };
        
#define EV_DECL_MUTABLE_METHODS_BEGIN \
    template <class storage_type_t> \
    class mutable_methods : public const_methods<storage_type_t> { \
        typedef const_methods<storage_type_t> base; \
    private:

#define EV_DECL_MUTABLE_METHODS_END };

#define EV_DECL_CLASS_END \
    class cview : public const_methods<encoded_value::const_pointer_storage_type<layout_type> > { \
    public: \
        cview(const char* base) { \
            _storage.bytes = base; \
        } \
    }; \
    class view : public mutable_methods<encoded_value::pointer_storage_type<layout_type> > { \
    public: \
        view(char* base) { \
            _storage.bytes = base; \
        } \
        operator cview() { \
            return cview(_storage.bytes); \
        } \
    }; \
    class value : public mutable_methods<encoded_value::array_storage_type<layout_type> > { \
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
    EV_DECLTYPE(((layout_type*)0)->name)

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
    encoded_value::layout2view<EV_DECLTYPE_MEMBER(name)>::cview name() const { \
        return this->_storage.view(EV_OFFSETOF(name)); \
    }

#define EV_DECL_MUTATOR(name) \
    using base::name; \
    void name(EV_DECLTYPE_MEMBER(name) value) { \
        return this->_storage.write(EV_OFFSETOF(name), value); \
    }

#define EV_DECL_ARRAY_MUTATOR(name) \
    using base::name; \
    void name(std::size_t n, EV_DECLTYPE_MEMBER(name[0]) value) { \
        return this->_storage.write(EV_OFFSETOF(name[n]), value); \
    }

#define EV_DECL_RAW_MUTATOR(name) \
    using base::name; \
    char * name() { \
        return this->_storage.view(EV_OFFSETOF(name)); \
    }

#define EV_DECL_VIEW_MUTATOR(name) \
    using base::name; \
    encoded_value::layout2view<EV_DECLTYPE_MEMBER(name)>::view name() { \
        return this->_storage.view(EV_OFFSETOF(name)); \
    }

#define EV_INSTANTIATE(name) \
    template class name::const_methods<encoded_value::array_storage_type<name::layout_type> >; \
    template class name::mutable_methods<encoded_value::array_storage_type<name::layout_type> >; \
    template class name::const_methods<encoded_value::pointer_storage_type<name::layout_type> >; \
    template class name::mutable_methods<encoded_value::pointer_storage_type<name::layout_type> >; \
    template class name::const_methods<encoded_value::const_pointer_storage_type<name::layout_type> >;
