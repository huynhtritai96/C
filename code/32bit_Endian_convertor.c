#include <iostream>
#include <cstdint>

uint32_t swapEndian(uint32_t value) {
    return ((value >> 24) & 0x000000FF) | // Move byte 0 to byte 3
           ((value >> 8)  & 0x0000FF00) | // Move byte 1 to byte 2
           ((value << 8)  & 0x00FF0000) | // Move byte 2 to byte 1
           ((value << 24) & 0xFF000000);  // Move byte 3 to byte 0
}

int main() {
    uint32_t bigEndianValue = 0x12345678; // Example big-endian value
    uint32_t littleEndianValue = swapEndian(bigEndianValue);

    std::cout << "Big-Endian Value: 0x" << std::hex << bigEndianValue << std::endl;
    std::cout << "Little-Endian Value: 0x" << std::hex << littleEndianValue << std::endl;

    return 0;
}
