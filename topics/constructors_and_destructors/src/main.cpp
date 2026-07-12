#include <iostream>
#include <string>

class Person {
public:
    // Default constructor.
    Person()
        : name_{"Unknown"}
        , age_{0}
    {
    }

    // Parameterized constructor.
    Person(std::string name, int age)
        : name_{std::move(name)}
        , age_{age}
    {
    }

    // Copy constructor.
    Person(const Person& other)
        : name_{other.name_}
        , age_{other.age_}
    {
    }

    // Copy assignment operator.
    Person& operator=(const Person& other)
    {
        if (this != &other) {
            name_ = other.name_;
            age_ = other.age_;
        }

        return *this;
    }

    // Move constructor.
    Person(Person&& other) noexcept
        : name_{std::move(other.name_)}
        , age_{other.age_}
    {
    }

    // Move assignment operator.
    Person& operator=(Person&& other) noexcept
    {
        if (this != &other) {
            name_ = std::move(other.name_);
            age_ = other.age_;
        }

        return *this;
    }

    // Destructor.
    ~Person() = default;

    std::string get_name() const noexcept
    {
        return name_;
    }

    int get_age() const noexcept
    {
        return age_;
    }

private:
    std::string name_;
    int age_;
};

int main()
{
    const auto print_person_data = [](const Person& person) {
        std::cout << "Person: " << person.get_name() << ", " << person.get_age() << "\n";
    };

    const auto print_section
        = [](const std::string& section) { std::cout << "==== " << section << " ====\n"; };

    {
        print_section("Default constructor");
        Person person;
        print_person_data(person);
    }

    {
        print_section("Parameterized constructor");
        Person person{"Harry", 42};
        print_person_data(person);
    }

    {
        print_section("Copy constructor");
        Person person1{"Harry", 42};
        print_person_data(person1);
        Person person2{person1};
        print_person_data(person2);
        Person person3 = person1;
        print_person_data(person3);
    }

    {
        print_section("Copy assignment operator");
        Person person1{"Harry", 42};
        print_person_data(person1);
        Person person2{"Alice", 21};
        print_person_data(person2);
        person2 = person1;
        print_person_data(person2);

        print_section("Copy assignment operator: self-assignment");
        Person person{"Harry", 42};
        print_person_data(person);
        person = person;
        print_person_data(person);
    }

    {
        print_section("Move constructor");
        Person person1{"Harry", 42};
        print_person_data(person1);
        Person person2{std::move(person1)};
        print_person_data(person2);
    }

    {
        print_section("Move assignment operator");
        Person person1{"Harry", 42};
        print_person_data(person1);
        Person person2{"Alice", 21};
        print_person_data(person2);
        person2 = std::move(person1);
        print_person_data(person2);
    }
}
