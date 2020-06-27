#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class Box{
private:
  b2Body* body=nullptr;
  b2Fixture* fixture=nullptr;
public:
  Box();
  ~Box();

  void init(b2World* world, glm::vec2 position, glm::vec2 dimensions){
    b2BodyDef body_def;
    body_def.type=b2_dynamicBody;
    body_def.position.Set(positon.x, position.y);
    body=world->CreateBody(&body_def);

    b2PolygonShape box_shape;
    box_shape.SetAsBox(dimensions.x*0.5f, dimensions.y*0.5f);

    b2FixtureDef fixture_def;
    fixture_def.shape=&box_shape;
    fixture_def.density=1.0f;
    fixture_def.friction=0.3f;
    fixture=body->CreateFixture(&fixture_def);
  }

  b2Body* get_body(){return body;}
  b2Fixture* get_fixture(){return fixture;}
};

int main(){
  GLFWwindow* window;

  /* Initialize the library */
  if(!glfwInit()){
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

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

  std::unique_ptr<b2World> world;
  b2Vec2 gravity(0.0f, -9.81f);
  world=std::make_unique<b2World>(gravity);

  b2BodyDef ground_body_def;
  ground_body_def.postion.Set(0.0f, -10.0f);
  b2Body* ground_body=world->CreateBody(&ground_body_def);
  b2PolygonShape ground_box;
  ground_box.SetAsBox(50.0f, 10.0f);
  ground_body->CreateFixture(&ground_box, 0.0f);

  std::vector<Box> boxes;
  Box b;
  b.init(world.get(), glm::vec2(0.0f, 14.0f), glm::vec2(15.0f, 15.0f));
  boxes.push_back(b);

  /*
  b2Vec2 gravity(0.0f, -10.0f);
  b2World world(gravity);

  b2BodyDef ground_body_def;
  ground_body_def.position.Set(0.0f, -10.0f);
  b2Body* ground_body=world.CreateBody(&ground_body_def);
  b2PolygonShape ground_box;
  ground_box.SetAsBox(50.0f, 10.0f);
  ground_body->CreateFixture(&ground_box, 0.0f);*/


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
