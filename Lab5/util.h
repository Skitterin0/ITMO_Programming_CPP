#ifndef LAB5_UTIL_H
#define LAB5_UTIL_H

class util {
public:
    static size_t calcPadding(const size_t baseAdress, const size_t alignment) {
        const size_t mult = baseAdress / alignment + 1;
        const size_t newAdress = mult * alignment;
        return newAdress - baseAdress;
    }

    static const size_t paddingWHeader(const size_t baseAdress, const size_t alignment, const size_t headerSize) {
        size_t padding = calcPadding(baseAdress, alignment);
        size_t neededSpace = headerSize;

        if (padding < neededSpace) {
            neededSpace -= padding;

            if (neededSpace % alignment > 0) {
                padding += alignment * (1 + neededSpace/alignment);
            }
            else {
                padding += alignment * (neededSpace/alignment);
            }
        }

        return padding;
    }
};

#endif
