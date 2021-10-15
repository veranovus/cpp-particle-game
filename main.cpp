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
#include <array>


#define CURRENT_PARTICLE particles[y * MAX_P_WIDTH + x]
#define HOST_PARTICLE    particles[p->y * MAX_P_WIDTH + p->x]


struct Vertex {

    glm::vec2 pos;
    glm::vec4 color;
};

enum class ParticleType {
    NONE = -1,
    SAND
};

struct Particle {

    int x, y;
    glm::vec4 color;
    ParticleType type = ParticleType::NONE;
    int idleCounter = 0;
    int stablePoint = 0;
    bool idle = false;
    bool updated = false;

    Particle(int x, int y, glm::vec4 color, ParticleType type) : x(x), y(y), color(color), type(type) {}
    Particle() : x(0), y(0), color({0, 0, 0, 0}), idle(true) {}
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


bool setUniformMat4f(GLuint shader, const std::string& name, glm::mat4 matrix);
bool setUniform4f(GLuint shader, const std::string& name, glm::vec4 floats);

std::string parseShader(const std::string& shaderSource);
GLuint compileShader(unsigned int type, const std::string& source);
GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

void drawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color);

void placeParticle(std::array<Particle*, (SCREEN_WIDTH / 5) * (SCREEN_HEIGHT / 5)>& particles, int x, int y, ParticleType type);
void swapParticles(void** p1, void** p2);
void updateParticles(std::array<Particle*, (SCREEN_WIDTH / 5) * (SCREEN_HEIGHT / 5)>& particles);

void calculateFPS();
void calculateDeltaTime();
glm::vec2 getMousePos(GLFWwindow* window);

void initRenderer();
void resetBatchStats();
void beginBatch();
void endBatch();
void renderBatch();
void terminateRenderer();


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

    // Enable Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    glm::mat4 proj = glm::ortho(0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
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
    std::array<Particle*, (SCREEN_WIDTH / 5) * (SCREEN_HEIGHT / 5)> particles{};
    for (auto* p : particles)
        p = nullptr;

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

            for (auto* p : particles)
                if (p) p->updated = false;

            // Update Particles
            updateParticles(particles);
        }
        // Calculate delta time;
        calculateDeltaTime();

        if (glfwGetKey(window, GLFW_KEY_A))
            ppos.x -= (float)(100.0 * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D))
            ppos.x += (float)(100.0 * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_W))
            ppos.y -= (float)(100.0 * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S))
            ppos.y += (float)(100.0 * deltaTime);

        if (glfwGetMouseButton(window, 0)) {

            auto pos = getMousePos(window);
            placeParticle(particles, (int)pos.x, (int)pos.y, ParticleType::SAND);
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

        // Render all the particles
        for (int x = 0; x < SCREEN_WIDTH / PIXEL_SIZE; ++x) {
            for (int y = 0; y < SCREEN_HEIGHT / PIXEL_SIZE; ++y) {

                Particle* p = particles[y * (SCREEN_WIDTH / 5) + x];
                if (p != nullptr)
                    drawQuad({p->x * PIXEL_SIZE, p->y * PIXEL_SIZE}, {PIXEL_SIZE, PIXEL_SIZE}, p->color);
            }
        }

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

    for (auto* part : particles)
        delete part;

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

void placeParticle(std::array<Particle*, (SCREEN_WIDTH / 5) * (SCREEN_HEIGHT / 5)>& particles, int x, int y, ParticleType type) {

    x = floor(x / PIXEL_SIZE);
    y = floor(y / PIXEL_SIZE);

    if ((x < 0 || x >= SCREEN_WIDTH / PIXEL_SIZE) || (y < 0 || y >= SCREEN_HEIGHT / PIXEL_SIZE))
        return;
    if (particles[y * (SCREEN_WIDTH / PIXEL_SIZE) + x])
        return;

    if (type == ParticleType::SAND) {
        particles[y * (SCREEN_WIDTH / PIXEL_SIZE) + x] = new Particle(x, y, {0.5f, 0.5f, 0.0f, 1.0f}, type);
        particles[y * (SCREEN_WIDTH / PIXEL_SIZE) + x]->stablePoint = 5;
    }
}

void updateParticles(std::array<Particle*, (SCREEN_WIDTH / 5) * (SCREEN_HEIGHT / 5)>& particles) {

    const int MAX_P_WIDTH  = SCREEN_WIDTH / 5;
    const int MAX_P_HEIGHT = SCREEN_HEIGHT / 5;

    for (int y = 0; y < MAX_P_HEIGHT; ++y) {

        for (int x = 0; x < MAX_P_WIDTH; ++x) {

            auto* p = CURRENT_PARTICLE;
            bool moved = false;

            if (p == nullptr || p->idle || p->updated) continue;

            if (p->type == ParticleType::SAND) {

                if (p->y + 1 >= MAX_P_HEIGHT) continue;

                bool right = (p->x + 1 < MAX_P_WIDTH);
                bool left  = (p->x - 1 >= 0);

                if (!particles[(p->y + 1) * MAX_P_WIDTH + p->x]) {

                    p->y++;
                    p->updated = true;
                    swapParticles((void**)&CURRENT_PARTICLE, (void**)&HOST_PARTICLE);

                    moved = true;
                }
                else if (right && !particles[(p->y + 1) * MAX_P_WIDTH + p->x + 1]) {

                    p->y++;
                    p->x++;
                    p->updated = true;
                    swapParticles((void**)&CURRENT_PARTICLE, (void**)&HOST_PARTICLE);

                    moved = true;
                }
                else if (left && !particles[(p->y + 1) * MAX_P_WIDTH + p->x - 1]) {

                    p->y++;
                    p->x--;
                    p->updated = true;
                    swapParticles((void**)&CURRENT_PARTICLE, (void**)&HOST_PARTICLE);

                    moved = true;
                }
            }

            if (!moved) {

                p->idleCounter++;

                if (p->idleCounter >= p->stablePoint) {
                    p->idle;
                    p->idleCounter = 0;
                }
            }
        }
    }
}

void swapParticles(void** p1, void** p2) {

    void* t = *p1;

    *p1 = *p2;
    *p2 = t;
}

void calculateDeltaTime() {

    crntFrameTime = glfwGetTime();
    deltaTime = crntFrameTime - lastFrameTime;
    if (deltaTime > deltaTimeHigh)
        deltaTime = deltaTimeHigh;
    lastFrameTime = crntFrameTime;
}

glm::vec2 getMousePos(GLFWwindow* window) {

    const bool reverse = false;

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    if (reverse)
        return { xPos, (SCREEN_HEIGHT - yPos) };
    else
        return { xPos, yPos };
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