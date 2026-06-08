# 0 "src/key_code.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3
# 0 "<command-line>" 2
# 1 "src/key_code.cpp"
# 1 "inc/key_code.hpp" 1
# 40 "inc/key_code.hpp"
class KeyCode
{
  public:
 enum class Value;

  public:
 consteval static auto size() -> std::size_t;
 auto toString() const -> std::string;

  public:
 KeyCode() = default;
 KeyCode(Value value);

  public:
 operator Value() const;

  private:
 Value value;

  public:
 enum class Value
 {

  KEY_A = GLFW_KEY_A, KEY_B = GLFW_KEY_B, KEY_C = GLFW_KEY_C, KEY_D = GLFW_KEY_D, KEY_E = GLFW_KEY_E, KEY_F = GLFW_KEY_F, KEY_G = GLFW_KEY_G, KEY_H = GLFW_KEY_H, KEY_I = GLFW_KEY_I, KEY_J = GLFW_KEY_J, KEY_K = GLFW_KEY_K, KEY_L = GLFW_KEY_L, KEY_M = GLFW_KEY_M, KEY_N = GLFW_KEY_N, KEY_O = GLFW_KEY_O, KEY_P = GLFW_KEY_P, KEY_R = GLFW_KEY_R, KEY_S = GLFW_KEY_S, KEY_T = GLFW_KEY_T, KEY_U = GLFW_KEY_U, KEY_V = GLFW_KEY_V, KEY_W = GLFW_KEY_W, KEY_Q = GLFW_KEY_Q, KEY_Y = GLFW_KEY_Y, KEY_Z = GLFW_KEY_Z, KEY_X = GLFW_KEY_X, KEY_1 = GLFW_KEY_1, KEY_2 = GLFW_KEY_2, KEY_3 = GLFW_KEY_3, KEY_4 = GLFW_KEY_4,

 };
};
# 2 "src/key_code.cpp" 2

consteval auto KeyCode::size() -> std::size_t
{
 constexpr std::size_t size = sizeof((int[]){

          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

         })
         / sizeof(int);
 return size;
}

auto KeyCode::toString() const -> std::string
{
 switch (value)
 {

  case A: return KEY_A; case B: return KEY_B; case C: return KEY_C; case D: return KEY_D; case E: return KEY_E; case F: return KEY_F; case G: return KEY_G; case H: return KEY_H; case I: return KEY_I; case J: return KEY_J; case K: return KEY_K; case L: return KEY_L; case M: return KEY_M; case N: return KEY_N; case O: return KEY_O; case P: return KEY_P; case R: return KEY_R; case S: return KEY_S; case T: return KEY_T; case U: return KEY_U; case V: return KEY_V; case W: return KEY_W; case Q: return KEY_Q; case Y: return KEY_Y; case Z: return KEY_Z; case X: return KEY_X; case 1: return KEY_1; case 2: return KEY_2; case 3: return KEY_3; case 4: return KEY_4;

 default:
  return "Unknown.";
 }
}
KeyCode::KeyCode(Value value) {}
KeyCode::operator Value() const {}
