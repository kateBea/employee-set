#include <set>
#include <string_view>
#include <functional>
#include <string>
#include <iostream>

class employee {
public:
    employee(std::string_view str, double salary)
        :   m_name{ str }, m_salary{ salary }
    {   }

    friend bool operator<(const employee& lhs, const employee& rhs) {
        return (lhs.m_name == rhs.m_name) ?
            lhs.m_salary < rhs.m_salary : lhs.m_name < rhs.m_name;
    }

    friend std::ostream& operator<<(std::ostream& out, const employee& emp) {
        out << emp.m_name << " : " << emp.m_salary;
        return out;
    }

    employee(const employee& other)
        :   m_name{ other.m_name }, m_salary{ other.m_salary }
    {
        std::cout << "Making copy okayge :-)\n";
    }

    std::string m_name{};
    double m_salary{};
};

int main(int, char**) {
    using func_t = std::function<bool(const employee&, const employee&)>;
    using func_copy_t = std::function<bool(employee, employee)>;

    func_t first {
        [](const employee& lhs, const employee& rhs) -> bool {
            return (lhs.m_name == rhs.m_name) ?
                lhs.m_salary < rhs.m_salary : lhs.m_name < rhs.m_name;
        }
    };

    func_copy_t second {
        [](employee lhs, employee rhs) -> bool {
            return (lhs.m_name == rhs.m_name) ?
                lhs.m_salary < rhs.m_salary : lhs.m_name < rhs.m_name;
        }
    };


    std::set<employee, func_t> s1(first);

    s1.emplace("Jordan", 200);
    s1.emplace("Gerald", 100);
    s1.emplace("Kisbert", 300);
    s1.emplace("Old", 400);
    s1.emplace("Gisbert", 500);


    for (const auto& it : s1)
        std::cout << it << '\n';

    std::cout << "Crafting second set\n";

    std::set<employee, func_copy_t> s2(second);

    s2.emplace("Jordan", 200);
    s2.emplace("Gerald", 100);
    s2.emplace("Kisbert", 300);
    s2.emplace("Old", 400);
    s2.emplace("Gisbert", 500);

    for (const auto& it : s2)
        std::cout << it << '\n';

    return 0;
}
