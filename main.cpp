#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <iostream>
#include <array>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <math.h>


struct Vertex {

    glm::vec2 pos;
    glm::vec4 color;
};

enum class ParticleType {
    NONE = -1,
    SAND
};

struct Particle {

    glm::vec2 pos;
    glm::vec4 color;
    bool idle = false;

    Particle(glm::vec2 pos, glm::vec4 color) : pos(pos), color(color) {}
};

struct RendererData {

    // Data
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    uint32_t indexCount = 0;

    Vertex* quadBuffer = nullptr;
    Vertex* quadBufferPtr = nullptr;

    // Stats
    uint32_t renderCount = 0;
    uint32_t quadCount = 0;
};

static RendererData rd = RendererData();

bool setUniformMat4f(GLuint shader, const std::string& name, glm::mat4 matrix);
bool setUniform4f(GLuint shader, const std::string& name, glm::vec4 floats);

std::string parseShader(const std::string& shaderSource);
GLuint compileShader(unsigned int type, const std::string& source);
GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

void drawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color);

void placeParticle(char* space, std::vector<Particle>& particles, int x, int y, ParticleType type);

void calculateFPS();
void calculateDeltaTime();
glm::vec2 getMousePos(GLFWwindow* window);

void initRenderer();
void resetBatchStats();
void beginBatch();
void endBatch();
void renderBatch();
void terminateRenderer();


static constexpr int SCREEN_WIDTH  = 960;
static constexpr int SCREEN_HEIGHT = 680;
static constexpr int PIXEL_SIZE  = 5;

static constexpr uint32_t MAX_QUAD = 5000;
static constexpr uint32_t MAX_VERTEX = MAX_QUAD * 4;
static constexpr uint32_t MAX_INDEX = MAX_QUAD * 6;

static constexpr double deltaTimeHigh = 0.1;
static double lastFrameTime = 0.0;
static double crntFrameTime;
static double deltaTime;


int main() {

    if(!glfwInit()) {
        std::cout << "[GLFW Error][GLFW could not be initialized!]\n";
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Game", NULL, NULL);
    if (!window) {
        std::cout << "[GLFW Error][Window could now be initialized!]\n";
        return -1;
    }

    glfwMakeContextCurrent(window);
    // Enable-Disable V-Sync
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK) {
        std::cout << "[GLEW Error][GLEW could not be initialized!]\n";
        glfwTerminate();
        return -1;
    }

    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Create shader program
    GLuint shader = createShaderProgram("../res/shader/particle/vertex.shader",
                                        "../res/shader/particle/fragment.shader");

    // Model View Projection Matrix
    glm::mat4 proj = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT, -1.0f, 1.0f);
    glm::mat4 mvp = proj;

    // Player position
    glm::vec2 ppos = {0.0f, 0.0f};

    // FPS Counter variables
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    uint32_t fpsCounter = 0;
    std::string fps;
    std::string frameTime;

    // Initialize batch renderer
    initRenderer();

    // Particles
    //std::vector<Particle> particles;
    std::vector<Particle> particles;
    auto* space = new char[(SCREEN_WIDTH / 5) * (SCREEN_HEIGHT / 5)];
    for (int x = 0; x < SCREEN_WIDTH / 5; ++x) {
        for (int y = 0; y < SCREEN_HEIGHT / 5; ++y) {

            space[y * (SCREEN_WIDTH / 5) + x] = -1;
        }
    }

    while (!glfwWindowShouldClose(window)) {

        // Calculate FPS
        crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        fpsCounter++;
        if (timeDiff >= 1 / 30.0) {
            fps = std::to_string((1.0 / timeDiff) * fpsCounter);
            frameTime = std::to_string((timeDiff / fpsCounter) * 1000);
            prevTime = crntTime;
            fpsCounter = 0;
        }
        // Calculate delta time;
        calculateDeltaTime();

        if (glfwGetKey(window, GLFW_KEY_A))
            ppos.x -= (float)(100.0 * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D))
            ppos.x += (float)(100.0 * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_W))
            ppos.y += (float)(100.0 * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S))
            ppos.y -= (float)(100.0 * deltaTime);

        if (glfwGetMouseButton(window, 0)) {

            auto pos = getMousePos(window);
            placeParticle(space, particles, (int)pos.x, (int)pos.y, ParticleType::SAND);
        }

        // Render Loop
        glClearColor(0.2f, 0.05f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        resetBatchStats();
        beginBatch();

        glUseProgram(shader);
        setUniformMat4f(shader, "u_mvp", mvp);

        for (auto& p : particles)
            drawQuad({p.pos.x, p.pos.y}, {PIXEL_SIZE, PIXEL_SIZE}, {p.color.r, p.color.g, p.color.b, p.color.a});

        drawQuad({ppos.x, ppos.y}, {PIXEL_SIZE, PIXEL_SIZE}, {0.0f, 1.0f, 0.0f, 1.0f});
        drawQuad({300.0f, 300.0f}, {PIXEL_SIZE, PIXEL_SIZE}, {1.0f, 0.0f, 0.0f, 1.0f});

        endBatch();
        renderBatch();

        // Draw GUI
        std::stringstream ss;
        ss << rd.renderCount;
        std::string drawCalls = "Render Call : " + ss.str();
        ss.str(std::string());
        ss << rd.quadCount;
        std::string quadCount = "Quad Count : " + ss.str();
        ImGui::Begin("ImGui Window");
        ImGui::Text("%s", drawCalls.c_str());
        ImGui::Text("%s", quadCount.c_str());
        ImGui::Text("%s", std::string("FPS : " + fps).c_str());
        ImGui::Text("%s", std::string("Frame Time : " + frameTime).c_str());
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    terminateRenderer();
    glfwTerminate();
    return 0;
}

bool setUniformMat4f(GLuint shader, const std::string& name, glm::mat4 matrix) {

    int location = glGetUniformLocation(shader, name.c_str());
    if (location == -1) {
        std::cout << "[OpenGL Warning][\"" << name << "\" is not a valid uniform location]\n";
        return false;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    return true;
}

bool setUniform4f(GLuint shader, const std::string& name, glm::vec4 floats) {

    int location = glGetUniformLocation(shader, name.c_str());
    if (location == -1) {
        std::cout << "[OpenGL Warning][\"" << name << "\" is not a valid uniform location]\n";
        return false;
    }

    glUniform4f(location, floats.x, floats.y, floats.z, floats.w);
    return true;
}

GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {

    GLuint program = glCreateProgram();
    GLuint vs = compileShader(GL_VERTEX_SHADER, parseShader(vertexShaderSource));
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, parseShader(fragmentShaderSource));

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "[OpenGL Error][Shader program failed to link : \n" << infoLog << "]\n";
        return 0;
    }

    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


GLuint compileShader(GLuint type, const std::string& source) {

    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, message);
        std::cout << "[OpenGL Error][Shader failed to compile : "
                  << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << "]\n";
        std::cout << "[LOG : " << message << "]\n";
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}


std::string parseShader(const std::string& shaderSource) {

    std::string line;
    std::fstream file(shaderSource);
    std::stringstream stream;

    while(getline(file, line)) {

        stream << line << '\n';
    }

    return stream.str();
}

void drawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color) {

    if (rd.indexCount >= MAX_INDEX) {
        endBatch();
        renderBatch();
        beginBatch();
    }

    rd.quadBufferPtr->pos = {pos.x, pos.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr++;

    rd.quadBufferPtr->pos = {pos.x + size.x, pos.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr++;

    rd.quadBufferPtr->pos = {pos.x, pos.y + size.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr++;

    rd.quadBufferPtr->pos = {pos.x + size.x, pos.y + size.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr++;

    rd.indexCount += 6;
    rd.quadCount++;
}

void placeParticle(char* space, std::vector<Particle>& particles, int x, int y, ParticleType type) {

    x = floor(x / PIXEL_SIZE);
    y = floor(y / PIXEL_SIZE);

    if (space[y * (SCREEN_WIDTH / PIXEL_SIZE) + x] != (int)ParticleType::NONE) return;

    particles.push_back(Particle({x * PIXEL_SIZE, y * PIXEL_SIZE}, {0.5f, 0.5f, 0.0f, 1.0f}));
    space[y * (SCREEN_WIDTH / 5) + x] = (char)type;
}

void calculateDeltaTime() {

    crntFrameTime = glfwGetTime();
    deltaTime = crntFrameTime - lastFrameTime;
    if (deltaTime > deltaTimeHigh)
        deltaTime = deltaTimeHigh;
    lastFrameTime = crntFrameTime;
}

glm::vec2 getMousePos(GLFWwindow* window) {

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    return { xPos, (SCREEN_HEIGHT - yPos) };
}

void initRenderer() {

    rd.quadBuffer = new Vertex[MAX_VERTEX];

    glGenVertexArrays(1, &rd.vao);
    glBindVertexArray(rd.vao);

    glGenBuffers(1, &rd.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, rd.vbo);
    glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    uint32_t indices[MAX_INDEX];
    uint32_t offset = 0;
    for (uint32_t i = 0; i < MAX_INDEX; i += 6) {

        indices[0 + i] = 0 + offset;
        indices[1 + i] = 1 + offset;
        indices[2 + i] = 2 + offset;
        indices[3 + i] = 2 + offset;
        indices[4 + i] = 3 + offset;
        indices[5 + i] = 1 + offset;

        offset += 4;
    }

    glGenBuffers(1, &rd.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rd.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void resetBatchStats() {

    rd.quadCount = 0;
    rd.renderCount = 0;
}

void beginBatch() {

    rd.quadBufferPtr = rd.quadBuffer;
    rd.indexCount = 0;
}

void endBatch() {

    GLsizeiptr size = (uint8_t*) rd.quadBufferPtr - (uint8_t*) rd.quadBuffer;
    //int size =  (rd.indexCount / 6) * 4 * sizeof(Vertex);
    glBindBuffer(GL_ARRAY_BUFFER, rd.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, rd.quadBuffer);
}

void renderBatch() {

    glBindVertexArray(rd.vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rd.ebo);
    glDrawElements(GL_TRIANGLES, (int)rd.indexCount, GL_UNSIGNED_INT, nullptr);
    rd.renderCount++;
}

void terminateRenderer() {

    glDeleteVertexArrays(1, &rd.vao);
    glDeleteBuffers(1, &rd.vbo);
    glDeleteBuffers(1, &rd.ebo);

    delete[] rd.quadBuffer;
}