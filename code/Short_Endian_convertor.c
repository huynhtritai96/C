#include <iostream>

short swapEndian(short value) {
    // Swap the bytes using bitwise operations
    return (value << 8) | ((value >> 8) & 0x00FF);
}

int main() {
    short bigEndianValue = 0x1234; // Example Big-Endian value
    short littleEndianValue = swapEndian(bigEndianValue);

    std::cout << "Big-Endian Value: 0x" << std::hex << bigEndianValue << std::endl;
    std::cout << "Little-Endian Value: 0x" << std::hex << littleEndianValue << std::endl;

    return 0;
}
