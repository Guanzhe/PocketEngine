//
//  Stringifier.h
//  GUIEditor
//
//  Created by Jeppe Nielsen on 06/09/15.
//  Copyright (c) 2015 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "minijson_reader.hpp"
#include "minijson_writer.hpp"
#include "Property.hpp"
#include <type_traits>
#include <sstream>
#include <map>
#include "ObjectConstructor.hpp"

namespace Pocket {

template<class T, typename S = void>
struct JsonSerializer {
    static void Serialize(std::string& key, const T& value, minijson::object_writer& writer) {
        std::stringstream s;
        s<<value;
        writer.write(key.c_str(), s.str());
    }
    
    static void Serialize(const T& value, minijson::array_writer& writer) {
        std::stringstream s;
        s<<value;
        writer.write(s.str());
    }
    
    static void Deserialize(minijson::value& value, T* field, minijson::istream_context& context) {
        if (value.type() != minijson::String) return;
        (*field) = T::Deserialize(value.as_string());
    }
};

template<>
struct JsonSerializer<int> {
    static void Serialize(std::string& key, const int& value, minijson::object_writer& writer) {
        writer.write(key.c_str(), value);
    }
    
    static void Serialize(const int& value, minijson::array_writer& writer) {
        writer.write(value);
    }
    
    static void Deserialize(minijson::value& value, int* field, minijson::istream_context& context) {
        if (value.type() != minijson::Number) return;
        (*field) = (int)value.as_long();
    }
};

template<>
struct JsonSerializer<short> {
    static void Serialize(std::string& key, const short& value, minijson::object_writer& writer) {
        writer.write(key.c_str(), value);
    }
    
    static void Serialize(const short& value, minijson::array_writer& writer) {
        writer.write(value);
    }
    
    static void Deserialize(minijson::value& value, short* field, minijson::istream_context& context) {
        if (value.type() != minijson::Number) return;
        (*field) = (short)value.as_long();
    }
};

template<>
struct JsonSerializer<float> {
    static void Serialize(std::string& key, const float value, minijson::object_writer& writer) {
        writer.write(key.c_str(), value);
    }
    
    static void Serialize(const float& value, minijson::array_writer& writer) {
        writer.write(value);
    }
    
    static void Deserialize(minijson::value& value, float* field, minijson::istream_context& context) {
        if (value.type() != minijson::Number) return;
        (*field) = (float)value.as_double();
    }
};

template<>
struct JsonSerializer<double> {
    static void Serialize(std::string& key, const double& value, minijson::object_writer& writer) {
        writer.write(key.c_str(), value);
    }
    
    static void Serialize(const double& value, minijson::array_writer& writer) {
        writer.write(value);
    }
    
    static void Deserialize(minijson::value& value, double* field, minijson::istream_context& context) {
        if (value.type() != minijson::Number) return;
        (*field) = value.as_double();
    }
};

template<>
struct JsonSerializer<std::string> {
    static void Serialize(std::string& key, const std::string& value, minijson::object_writer& writer) {
        writer.write(key.c_str(), value);
    }
    
    static void Serialize(const std::string& value, minijson::array_writer& writer) {
        writer.write(value);
    }
    
    static void Deserialize(minijson::value& value, std::string* field, minijson::istream_context& context) {
        if (value.type() != minijson::String) return;
        (*field) = std::string(value.as_string());
    }
};

template<>
struct JsonSerializer<bool> {
    static void Serialize(std::string& key, const bool& value, minijson::object_writer& writer) {
        writer.write(key.c_str(), value);
    }
    
    static void Serialize(const bool& value, minijson::array_writer& writer) {
        writer.write(value);
    }
    
    static void Deserialize(minijson::value& value, bool* field, minijson::istream_context& context) {
        if (value.type() != minijson::Boolean) return;
        (*field) = value.as_bool();
    }
};

template<>
struct JsonSerializer<uint64_t> {
    static void Serialize(std::string& key, const uint64_t& value, minijson::object_writer& writer) {
        writer.write(key.c_str(), value);
    }
    
    static void Serialize(const uint64_t& value, minijson::array_writer& writer) {
        writer.write(value);
    }
    
    static void Deserialize(minijson::value& value, uint64_t* field, minijson::istream_context& context) {
        if (value.type() != minijson::Number) return;
        (*field) = ((uint64_t)value.as_long());
    }
};

template<typename I>
struct JsonSerializer<std::vector<I>> {
    static void Serialize(std::string& key, const std::vector<I>& value, minijson::object_writer& writer) {
        minijson::array_writer array = writer.nested_array(key.c_str());
        for (size_t i=0; i<value.size(); ++i) {
            JsonSerializer<I>::Serialize(value[i], array);
        }
        array.close();
    }
    
    static void Serialize(const std::vector<I>& value, minijson::array_writer& writer) {
        minijson::array_writer array = writer.nested_array();
        for (int i=0; i<value.size(); ++i) {
            JsonSerializer<I>::Serialize(value[i], array);
        }
        array.close();
    }
    
    static void Deserialize(minijson::value& value, std::vector<I>* field, minijson::istream_context& context) {
        if (value.type() != minijson::Array) return;
        std::vector<I>& vector = *field;
        minijson::parse_array(context, [&] (minijson::value v) {
            vector.resize(vector.size() + 1);
            I& item = vector.back();
            JsonSerializer<I>::Deserialize(v, &item, context);
        });
    }
};

template<>
struct JsonSerializer<std::vector<bool>> {
    static void Serialize(std::string& key, const std::vector<bool>& value, minijson::object_writer& writer) {
        minijson::array_writer array = writer.nested_array(key.c_str());
        for (size_t i=0; i<value.size(); ++i) {
            JsonSerializer<bool>::Serialize(value[i], array);
        }
        array.close();
    }
    
    static void Serialize(const std::vector<bool>& value, minijson::array_writer& writer) {
        minijson::array_writer array = writer.nested_array();
        for (size_t i=0; i<value.size(); ++i) {
            JsonSerializer<bool>::Serialize(value[i], array);
        }
        array.close();
    }
    
    static void Deserialize(minijson::value& value, std::vector<bool>* field, minijson::istream_context& context) {
        if (value.type() != minijson::Array) return;
        std::vector<bool>& vector = *field;
        minijson::parse_array(context, [&] (minijson::value v) {
            bool item;
            JsonSerializer<bool>::Deserialize(v, &item, context);
            vector.push_back(item);
        });
    }
};

template<typename T>
struct JsonSerializer<Property<T>> {
    static void Serialize(std::string& key, const Property<T>& value, minijson::object_writer& writer) {
        JsonSerializer<T>::Serialize(key, value(), writer);
    }
    
    static void Serialize(const Property<T>& value, minijson::array_writer& writer) {
        JsonSerializer<T>::Serialize(value(), writer);
    }
    
    static void Deserialize(minijson::value& value, Property<T>* field, minijson::istream_context& context) {
       T data;
       JsonSerializer<T>::Deserialize(value, &data, context);
       field->operator=(data);
    }
};


template<typename Key, typename Value>
struct JsonSerializer<std::map<Key, Value>> {
    static void Serialize(std::string& key, const std::map<Key, Value>& value, minijson::object_writer& writer) {
        minijson::array_writer array = writer.nested_array(key.c_str());
        for (auto it = value.begin(); it!=value.end(); ++it) {
            minijson::array_writer keyValueArray = array.nested_array();
            const Key* keyPointer = (const Key*)(&it->first);
            JsonSerializer<Key>::Serialize(*keyPointer, keyValueArray);
            const Value* valuePointer = (const Value*)(&it->second);
            JsonSerializer<Value>::Serialize(*valuePointer, keyValueArray);
            keyValueArray.close();
        }
        array.close();
    }
    
    static void Serialize(const std::map<Key, Value>& value, minijson::array_writer& writer) {
        minijson::array_writer array = writer.nested_array();
        for (auto it = value.begin(); it!=value.end(); ++it) {
            minijson::array_writer keyValueArray = array.nested_array();
            const Key* keyPointer = (const Key*)(&it->first);
            JsonSerializer<Key>::Serialize(*keyPointer, keyValueArray);
            const Value* valuePointer = (const Value*)(&it->second);
            JsonSerializer<Value>::Serialize(*valuePointer, keyValueArray);
            keyValueArray.close();
        }
        array.close();
    }
    
    static void Deserialize(minijson::value& value, std::map<Key, Value>* field, minijson::istream_context& context) {
        if (value.type() != minijson::Array) return;
        std::map<Key, Value>& map = *field;
        minijson::parse_array(context, [&] (minijson::value v) {
            if (v.type() != minijson::Array) {
                minijson::ignore(context);
            } else {
                int counter = 0;
                Key key;
                minijson::parse_array(context, [&] (minijson::value v) {
                    if (counter == 0) {
                        JsonSerializer<Key>::Deserialize(v, &key, context);
                    } else if (counter == 1) {
                        Value& mapValue = map[key];
                        JsonSerializer<Value>::Deserialize(v, &mapValue, context);
                    }
                    counter++;
                });
            }
        });
        
    }
};

template<typename T>
struct JsonSerializer<T, typename std::enable_if< std::is_enum<T>::value >::type> {
    static void Serialize(std::string& key, const T& value, minijson::object_writer& writer) {
        writer.write(key.c_str(), (int)value);
    }
    
    static void Serialize(const T& value, minijson::array_writer& writer) {
        writer.write((int)value);
    }
    
    static void Deserialize(minijson::value& value, T* field, minijson::istream_context& context) {
        if (value.type()!=minijson::Number) return;
        T enumValue = (T)value.as_long();
        (*field) = enumValue;
    }
};

template<typename T>
struct JsonSerializer<T, typename std::enable_if< std::is_pointer<T>::value >::type> {
    static void Serialize(std::string& key, const T& value, minijson::object_writer& writer) {
        if (!value) return;
        
        auto type = value->GetType();
        minijson::object_writer object = writer.nested_object(key.c_str());
        object.write("typeId", value->Id());
        type.Serialize(object);
        object.close();
    }
    
    static void Serialize(const T& value, minijson::array_writer& writer) {
        if (!value) return;
        auto type = value->GetType();
        minijson::object_writer object = writer.nested_object();
        object.write("typeId", value->Id());
        type.Serialize(object);
        object.close();
    }
    
    static void Deserialize(minijson::value& value, T* field, minijson::istream_context& context) {
        using nonPointerType = typename std::remove_pointer_t<T>;
        try {
            T ptr = nullptr;
            minijson::parse_object(context, [&] (const char* name, minijson::value v) {
                if (strcmp(name, "typeId")==0) {
                    ptr = nonPointerType::ConstructObject(v.as_string());
                } else if (ptr!=nullptr) {
                    auto type =  ptr->GetType();
                    auto field = type.GetFieldInternal(name);
                    if (field) {
                        field->Deserialize(context, v);
                    } else {
                        minijson::ignore(context);
                    }
                }
            });
            
            *field = ptr;
        } catch (minijson::parse_error e) {
            std::cout<< e.what() << std::endl;
            *field = nullptr;
        }
    }
};

template<typename T>
struct JsonSerializer<Event<T>> {
    static void Serialize(std::string& key, const Event<T>& value, minijson::object_writer& writer) {
    
    }
    
    static void Deserialize(minijson::value& value, Event<T>* field, minijson::istream_context& context) {

    }
};



}
