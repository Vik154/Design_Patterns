/* Паттерн "Одиночка" (Singleton) */
// Одиночка – это порождающий паттерн, который гарантирует существование только одного объекта
// определённого класса, а также позволяет достучаться до этого объекта из любого места программы.

#pragma once
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

//-----------------------------------------------------------
// Концепция паттерна "Одиночка"
//-----------------------------------------------------------
namespace Сonception {
    // Singleton Мэйерса
    class MSingleton {
    private:
        MSingleton() {}
        MSingleton(const MSingleton&) {};
        MSingleton& operator=(MSingleton&) {};
    public:
        static MSingleton& getInstance() {
            static MSingleton  instance;
            return instance;
        }
    };
}

//-----------------------------------------------------------
// Реализация паттерна "Одиночка"
// За идею взят - https://leimao.github.io/blog/CPP-Singleton/
//-----------------------------------------------------------
namespace Creational {

    class Singleton {
    public:
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        ~Singleton() {}

        void set_value(const int& value) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_value = value;
        }
        inline const int& get_value() const { return m_value; }
        inline const std::thread::id& get_id() const { return m_id; }

        static Singleton* get_instance() {
            static Singleton instance{};
            return &instance;
        }
    private:
        explicit Singleton() : m_value(0), m_id(std::this_thread::get_id()) {
            std::cout << "Создан объект класса с id: " << m_id << '\n';
        }
        int m_value;
        std::mutex m_mutex;
        std::thread::id m_id;
    };

    // Тестирование паттерна
    void test_singleton() {
        Singleton* single = nullptr;
        std::vector<std::thread> threads(8);
        for (int i = 0; i < threads.size(); ++i) {
            threads[i] = std::thread([&]() { 
                single = Singleton::get_instance();
                std::cout << "id thread: " << std::this_thread::get_id();
                std::cout << "; class id: " << single->get_id();
                std::cout << "; value = " << single->get_value() << '\n';
                single->set_value(i * 2);
                });
            threads[i].join();
        }
    }
}
//-----------------------------------------------------------