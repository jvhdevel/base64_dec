#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

const std::string input_str = "SGVsbG8sIFdvcmxkIQ==";
const std::string expected = "Hello, World!";
constexpr std::array<char, 65> charmap = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '\\', '='
};

struct chunk {
  std::bitset<24> data;
  std::size_t padding = 0;
};

chunk to_chunk(const uint8_t byte_1, const uint8_t byte_2, const uint8_t byte_3, const uint8_t byte_4);
std::vector<chunk> to_chunks(const std::string &s);
std::array<char, 3> decode(const chunk &c);

std::size_t get_index(const std::array<char, 65> &a, const char c) {
  return std::distance(a.begin(), std::find(a.begin(), a.end(), c));
}

int main(int argc, const char *argv[]) {
  std::vector<chunk> chunks;
  std::string output;

  if (argc < 2) {
    std::cout << "No input supplied! Running Test!\n";

    chunks = to_chunks(input_str);
    output = "";

    for (chunk c : chunks) {
      for (char e : decode(c)) {
        output += e;
      }
    }

    std::cout << "Input     : " << input_str << "\n";
    std::cout << "Expected  : " << expected << "\n\n";
    std::cout << "Output    : " << output << "\n\n";
    std::cout << "Matching? " << (output == expected ? "Yes" : "No") << "\n";
    return 0;
  }

  chunks = to_chunks(argv[1]);
  output = "";

  for (auto c : chunks) {
    for (char e : decode(c)) {
      if (e == '\0') { break; }
      output += e;
    }
  }

  std::cout << output << "\n";

  return 0;
}

chunk to_chunk(const uint8_t byte_1, const uint8_t byte_2, const uint8_t byte_3, const uint8_t byte_4) {
  chunk c;

  c.data |= get_index(charmap, byte_1);
  c.data <<= 6;
  c.data |= get_index(charmap, byte_2);
  c.data <<= 6;
  c.data |= get_index(charmap, byte_3);
  c.data <<= 6;
  c.data |= get_index(charmap, byte_4);

  c.padding = (
    (byte_1 == '=' ? 1 : 0) +
    (byte_2 == '=' ? 1 : 0) +
    (byte_3 == '=' ? 1 : 0) +
    (byte_4 == '=' ? 1 : 0)
  );

  return c;
}

std::vector<chunk> to_chunks(const std::string &s) {
  std::size_t char_count = 0;
  std::vector<chunk> chunks;

  std::array<char, 4> chars;

  for (char c : s) {
    chars[char_count] = c;
    ++char_count;

    if (char_count >= 4) {
      chunks.push_back(to_chunk(chars[0], chars[1], chars[2], chars[3]));
      char_count = 0;
    }
  }

  if (char_count != 0) {
    while (char_count < 4) {
      chars[char_count] = '\0';
      ++char_count;
    }
  }

  if (char_count >= 4) {
    chunks.push_back(to_chunk(chars[0], chars[1], chars[2], chars[3]));
    char_count = 0;
  }

  return chunks;
}

std::array<char, 3> decode(const chunk &c) {
  char c1 = (c.data.to_ulong() >> 16);
  char c2 = (c.data.to_ulong() >>  8) & 0b11111111;
  char c3 = (c.data.to_ulong()      ) & 0b11111111;

  switch (c.padding) {
    case 2: c2 = '\0';
    case 1: c3 = '\0';
  }
  return {c1, c2, c3};
}
