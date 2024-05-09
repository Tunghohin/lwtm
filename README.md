## usage:
```c++
constexpr auto try_parse_string_with_escape(std::string_view const str)
-> std::optional<std::string> {
    ...
}

auto main() -> int {
    char bad[] = {'\"', 'f', 'f', '\\', '\"', '\\', '\\', 'f', 'f', '\"', '\"', 
    '\0'};
    EXPR_TEST_MACRO(auto str = try_parse_string_with_escape(bad); str.has_value(),
        [&str]() {
            std::cout << "good";
        },
        []() {
            std::cout << "bad";
        }
    );

    char good[] = {'\"', 'f', 'f', '\\', '\"', '\\', '\\', 'f', 'f', '\"', 
    '\0'};
    EXPR_TEST_MACRO_TIME(auto str = try_parse_string_with_escape(good); str.has_value(),
        [&str]() {
            std::cout << "good";
        },
        []() {
            std::cout << "bad";
        }
    );
}

//output:
//{ case: "auto str = try_parse_string_with_escape(bad); str.has_value()", output: "bad" }
//{ case: "auto str = try_parse_string_with_escape(good); str.has_value()", output: "good", time: "0.0023ms" }

```
