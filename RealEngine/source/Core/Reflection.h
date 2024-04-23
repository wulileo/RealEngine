#pragma once

#include <rttr/registration.h>

#define CLASS(Class) \
RTTR_REGISTRATION \
{ \
    rttr::registration::class_<Class>(#Class) \
    .constructor<>()

#define PROPERTY(Class, Property) \
    .property(#Property, &Class::Property)

#define FUNCTION(Class, Function) \
    .method(#Function, &Class::Function)

#define CLASS_END ;}

template<typename T>
static T *Create(const std::string &Name) {
    rttr::type type = rttr::type::get_by_name(Name);
    auto const var = type.create();
    return var.get_value<T *>();
}
