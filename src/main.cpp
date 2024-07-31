#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unistd.h>

// Callback function for handling key events
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

struct WindowColors
{
  float red;
  float green;
  float blue;
};

struct WindowHSL
{
  float hue;
  float saturation;
  float lightness;
};

float max(float a, float b, float c)
{
  return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

float min(float a, float b, float c)
{
  return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

float abs(float a)
{
  return a < 0 ? -a : a;
}


float fmod(float a, float b)
{
  return a - b * int(a / b);
}

WindowHSL rgb2hsl(WindowColors *wc)
{

  float r = wc->red;
  float g = wc->green;
  float b = wc->blue;

  float Cmax = max(r, g, b);
  float Cmin = min(r, g, b);

  float lum = (Cmax + Cmin) / 2;
  float hue;
  float sat;
  if (Cmax == Cmin)
  {
    hue = 0;
    sat = 0;
  }
  else
  {
    float c = Cmax - Cmin; // chroma

    sat = c / (1 - abs(2 * lum - 1));
    if (Cmax == r)
    {
      hue = (g - b) / c;
    }
    else if (Cmax == g)
    {
      hue = (b - r) / c + 2;
    }
    else
    {
      hue = (r - g) / c + 4;
    }
  }

  return {hue * 60, sat, lum};
}

WindowColors hsltorgb(WindowHSL *wh)
{
  float hue = wh->hue;
  float sat = wh->saturation;
  float lum = wh->lightness;

  float C = (1 - abs(2 * lum - 1)) * sat;
  float X = C * (1 - abs(fmod(hue / 60, 2) - 1));
  float m = lum - C / 2;

  float r, g, b;
  if (hue >= 0 && hue < 60)
  {
    r = C;
    g = X;
    b = 0;
  }
  else if (hue >= 60 && hue < 120)
  {
    r = X;
    g = C;
    b = 0;
  }
  else if (hue >= 120 && hue < 180)
  {
    r = 0;
    g = C;
    b = X;
  }
  else if (hue >= 180 && hue < 240)
  {
    r = 0;
    g = X;
    b = C;
  }
  else if (hue >= 240 && hue < 300)
  {
    r = X;
    g = 0;
    b = C;
  }
  else
  {
    r = C;
    g = 0;
    b = X;
  }

  return {r + m, g + m, b + m};
}

void updateColors(WindowColors *wc)
{
  WindowHSL wh = rgb2hsl(wc);
  wh.hue += 1.0f;
  if (wh.hue > 360.0f)
  {
    wh.hue = 0.0f;
  }
  *wc = hsltorgb(&wh);
}

int main()
{
  // Initialize the library
  if (!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Set GLFW window creation hints (optional)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a windowed mode window and its OpenGL context
  GLFWwindow *window = glfwCreateWindow(800, 600, "Hello OpenGL", nullptr, nullptr);
  if (!window)
  {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {
	glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}