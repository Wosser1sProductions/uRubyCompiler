#pragma once

#include <map>
#include <string_view>
#include <optional>

#include "../utils/utils_lib/utils_algorithm.hpp"
#include "../utils/utils_lib/utils_string.hpp"


namespace cmp {
    class SymbolTable {
        private:
            typedef std::map<std::string_view, int> _TableType;
            _TableType table;

        public:
            typedef typename _TableType::key_type       key_type;
            typedef typename _TableType::value_type     pair_type;
            typedef typename _TableType::mapped_type    value_type;
            typedef typename _TableType::size_type	    size_type;

            SymbolTable() {
                // Empty
            }

            ~SymbolTable() {}

            const size_type size() const {
                return this->table.size();
            }

            const bool empty() const {
                return this->table.empty();
            }

            void insert(key_type name, value_type value) {
                this->table[name] = value;
            }

            void erase(key_type name) {
                this->table.erase(name);
            }

            std::optional<value_type> get(key_type name) {
                if (utils::algorithm::contains(this->table, name)) {
                    return { this->table[name] };
                }
                return std::nullopt;
            }

            template<typename TChar, typename TCharTraits>
            friend auto& operator<<(std::basic_ostream<TChar, TCharTraits>& stream,
                                    const SymbolTable& t)
            {
                size_t max_key_len = 0;

                for (auto [key, val] : t.table) {
                    if (const size_t key_len = key.size(); key_len > max_key_len) {
                        max_key_len = key_len;
                    }
                }

                for (auto [key, val] : t.table) {
                    stream << utils::string::format("[%*s] : %d\n", max_key_len, key.data(), val);
                }

                return stream;
            }
    };
}
