cmake_minimum_required(VERSION 3.5)

# Установить имя проекта и язык программирования
project(SectionPoint CXX)

# Добавить исполняемый файл main.cpp и файлы SectionPoint.cpp и SectionPoint.h в проект
add_executable(Sections main.cpp SectionPoint.cpp PointIO.cpp SectionPoint.h)