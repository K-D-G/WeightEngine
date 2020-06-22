#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <box2d/box2d.h>

int main(){
  GLFWwindow* window;

  /* Initialize the library */
  if(!glfwInit()){
    return -1;
  }

    /* Create a windowed mode window and its OpenGL context */
  window=glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if(!window){
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    return -1;
  }

  //For some reason OpenGL crashes on Apple without setting up a VAO at the start
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  b2Vec2 gravity(0.0f, -10.0f);
  b2World world(gravity);

  b2BodyDef ground_body_def;
  ground_body_def.position.Set(0.0f, -10.0f);
  b2Body* ground_body=world.CreateBody(&ground_body_def);
  b2PolygonShape ground_box;
  ground_box.SetAsBox(50.0f, 10.0f);
  ground_body->CreateFixture(&ground_box, 0.0f);


  /* Loop until the user closes the window */
  while(!glfwWindowShouldClose(window)){

    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
