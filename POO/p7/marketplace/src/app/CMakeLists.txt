# Declara el ejecutable para app-main
add_executable(app-main app-main.cc)

# Incluye los directorios necesarios
target_include_directories(app-main PRIVATE
    ${CMAKE_SOURCE_DIR}/src/market
    ${CMAKE_SOURCE_DIR}/src/client
    ${CMAKE_SOURCE_DIR}/src/seller
)

# Especifica las dependencias del proyecto
target_link_libraries(app-main PRIVATE
    market
    client
    seller
)