#ifndef __ANY_CONTAINER__
#define __ANY_CONTAINER__

#include <any>
#include <iostream>
#include <optional>
#include <unordered_map>
#include <variant>

class AnyContainer {
    std::unordered_map<std::string, std::pair<std::any, std::any>> data_;

  public:
    void Clear() {
        data_.clear();
    }

    void Reset() {
        for (auto& item : data_) item.second.first = item.second.second;
    }

    void Add(const std::string& name, const std::any& data) {
        data_.insert_or_assign(name, std::make_pair(data, data));
    }

    void Add(const std::string& name, const std::any& data, const std::any& default_value) {
        data_.insert_or_assign(name, std::make_pair(data, default_value));
    }

    void Set(const std::string& name, const std::any& data) {
        data_.at(name).first = data;
    }

    template <typename _AnyType>
    auto Get(std::string name) -> std::optional<_AnyType> {
        try {
            return std::any_cast<_AnyType>(data_.at(name).first);
        } catch (const std::out_of_range&) {
            std::cout << "No such var named: " << name << std::endl;
            return std::nullopt;
        } catch (const std::bad_any_cast&) {
            std::cout << "Bad Any Cast!" << std::endl;
            return _AnyType{};
        }
    }

    template <typename _AnyType>
    auto GetDefault(std::string name) -> std::optional<_AnyType> {
        try {
            return std::any_cast<_AnyType>(data_.at(name).second);
        } catch (const std::out_of_range&) {
            std::cout << "No such var named: " << name << std::endl;
            return std::nullopt;
        } catch (const std::bad_any_cast&) {
            std::cout << "Bad Any Cast!" << std::endl;
            return _AnyType{};
        }
    }
};

class VariantContainer {
    std::unordered_map<std::string, std::pair<std::variant<bool, unsigned char, int, double, std::string>,
                                              std::variant<bool, unsigned char, int, double, std::string>>>
        data_;

  public:
    void Clear() {
        data_.clear();
    }

    void Reset() {
        for (auto& item : data_) item.second.first = item.second.second;
    }

    void Add(const std::string name, const std::variant<bool, unsigned char, int, double, std::string> data_value) {
        data_.insert_or_assign(name, std::make_pair(data_value, data_value));
    }

    void Add(const std::string name, const std::variant<bool, unsigned char, int, double, std::string> data_value,
             std::variant<bool, unsigned char, int, double, std::string> default_value) {
        data_.insert_or_assign(name, std::make_pair(data_value, default_value));
    }

    void Set(const std::string& name, const std::variant<bool, unsigned char, int, double, std::string> data_value) {
        data_.at(name).first = data_value;
    }

    template <typename _AnyType>
    auto Get(std::string name) -> std::optional<_AnyType> {
        try {
            return std::get<_AnyType>(data_.at(name).first);
        } catch (const std::out_of_range&) {
            std::cout << "No such var named: " << name << std::endl;
            return std::nullopt;
        } catch (const std::bad_variant_access&) {
            std::cout << "Bad Variant Access!" << std::endl;
            return _AnyType{};
        }
    }
    template <typename _AnyType>
    auto GetDefault(std::string name) -> std::optional<_AnyType> {
        try {
            return std::get<_AnyType>(data_.at(name).second);
        } catch (const std::out_of_range&) {
            std::cout << "No such var named: " << name << std::endl;
            return std::nullopt;
        } catch (const std::bad_variant_access&) {
            std::cout << "Bad Variant Access!" << std::endl;
            return _AnyType{};
        }
    };
};

#endif // __ANY_CONTAINER__